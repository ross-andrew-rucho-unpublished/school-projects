% Ross Rucho
% ratrucho@gmail.com
% 3/1/2018
% assignment3.m

%% Declarations
clear
close all

%% Part 1
imSize = [128,128];

img = im2double(rgb2gray(imresize(imread('high_contrast.jpg'), imSize)));
% diag = zeros(128);
% 
% for j = 1:size(diag,1)
%     for k = 1:size(diag,2)
%         if j > k
%             diag(j,k) = 1000;
%         end
%         if j == k
%             diag(j,k) = 500;
%         end
%     end
% end
% 
% 
% IA = img(floor(size(img,1)/2):127 + floor(size(img,1)/2),...
%          floor(size(img,2)/2):127 + floor(size(img,2)/2));


%% Part 2
% I = zeros(65,128);
%    
%    for j = 1:128
%        for k = 1:65
%            I(j,k) = (((k - 1)/128)^2)*(((j - 1)/128)^2)*exp(-(1/2)*((4*pi)^2)*(((k - 1)/128)^2)*(((j - 1)/128)^2));
%        end
%        
%        for k = 66:128
%            I(j,k) = (((k - 129)/128)^2)*(((j - 1)/128)^2)*exp(-(1/2)*((4*pi)^2)*(((k - 129)/128)^2)*(((j - 1)/128)^2));
%        end
%        
%    end
%    
%    I = I(1:65,1:65);


%% Part 3
% Filter from Question 2
   I2 = zeros(65,128);
   I5 = zeros(65,128);
   
   for j = 1:128
       for k = 1:65
           I2(j,k) = ((((k - 1)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((4*pi)^2)*((((k - 1)/128)^2)+(((j - 1)/128)^2)));
           I5(j,k) = ((((k - 1)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((10*pi)^2)*((((k - 1)/128)^2)+(((j - 1)/128)^2)));
       end
       
       for k = 66:128
           I2(j,k) = ((((k - 129)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((4*pi)^2)*((((k - 129)/128)^2)+(((j - 1)/128)^2)));
           I5(j,k) = ((((k - 129)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((10*pi)^2)*((((k - 129)/128)^2)+(((j - 1)/128)^2)));
       end
       
   end
   
   I2 = I2(1:65,:);
   I5 = I5(1:65,:);
   
   % Apply filter to images
   [mag1, ~] = AmpPhaseDFT(img);
   %[mag2, ~] = AmpPhaseDFT(img2);
   
   mag1A = I2.*mag1;
   mag1B = I5.*mag1;
   %mag2A = I2.*mag2;
   %mag2B = I5.*mag2;
   
%% Output
%imshow(mag1);
%imshow(mag1A);
