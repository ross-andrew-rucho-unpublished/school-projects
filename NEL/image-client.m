% Ross Rucho
% ratrucho@gmail.com
% 05/28/19
% image-client.m
%
% This script is a basic template for a tcp client in Matlab. Its purpose
% is to test transmission and reception of an image of known dimensions
% and resolution to and from a server.
% This is a specific solution. It must be modified to work in general.

%% Declarations & Definitions
host = '169.254.57.129'; % Windows OS host IP address
serverPort = 12000; % Arbitrarily chosen port number
imageResolution = 'uint16';
imageDimensions = [512, 512];

% Read image to transmit.
message = permute(rgb2gray(imread('test-image.jpg')), [2 1]);
data = whos('message');             % Workaround to compute the size of a variable in bytes.
messageSize = int2str(data.bytes);

% Create TCP/IP interface.
clientSocket = tcpip(host, serverPort);

%% Procedure
% Configure and open TCP/IP socket.
set(clientSocket, 'OutputBufferSize', data.bytes);
set(clientSocket, 'InputBufferSize', data.bytes);
fopen(clientSocket);

% Read/write image size to and from server
fwrite(clientSocket, messageSize);
receivedSize = char(fread(clientSocket, length(messageSize))');

% Wait for confirmation then write image to server
confirm = input('Please press enter');
fwrite(clientSocket, message(:), imageResolution);

% Read image from server
receivedMessage = fread(clientSocket, imageDimensions, imageResolution);

% Format image and display
receivedImage = reshape(receivedMessage, imageDimensions(1), imageDimensions(2));
imshow(receivedImage);
 
% Close connection
fclose(clientSocket);

