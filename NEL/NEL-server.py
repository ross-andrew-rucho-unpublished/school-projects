# Ross Rucho
# ratrucho@gmail.com
# NEL-server.py
# 07/08/19
#
# This is the first iteration server class for the Neural Engineering Lab (NEL).
# Its purpose is to receive images of known dimensions and resolution from a client.
# This is a specific solution. It must be modified to work in general.

import socket
from PIL import Image as PIL_Image
import numpy as np

#%%
class NelServer(object):
    # Object properties.
    __serverSocket = None
    __host = None
    __port = None
    __clientFacingSocket = None
    __clientAddress = None  
    __block = None
    __imageSize = None
    __imageDataType = None
    __imageDimensions = None
    __fixedReceptionSize = None
    
    # Constructor.
    # Initialize server and connect to the client.
    # host="" means that connections on all available IPv4 interfaces will be accepted.
    # 12000 is an arbitrary unreserved port number (non-privileged ports are > 1023).
    def __init__(self, host="", port=12000, fixedReceptionSize=2048):
        # Create socket with attributes IPv4 address family and TCP protocol.
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Bind socket to the given host and port number.
        serverSocket.bind((host, port))
        
        # Initiate server socket listen mode.
        serverSocket.listen()
        
        # Assign class properties.
        self.__serverSocket = serverSocket
        self.__host = host
        self.__port = port
        self.__fixedReceptionSize = fixedReceptionSize
        
        # Print acknowledgement to console.
        print('The server is listening.')
        
        # Accept an incoming connection.
        clientFacingSocket, clientAddress = serverSocket.accept()
    
        # Finish connection initialization.
        print('Connected by: ', clientAddress)
        imageSize = clientFacingSocket.recv(self.__fixedReceptionSize)
        clientFacingSocket.sendall(imageSize)
        
        # Assign class properties.
        self.__clientFacingSocket = clientFacingSocket
        self.__clientAddress = clientAddress
        self.__imageSize = int(imageSize.decode())
        self.__imageDataType = 'uint16'
        self.__imageDimensions = (512, 512)
        self.__block = bytearray(self.__imageSize)
    
    # Class functions.
    
    # Returns the server socket object.
    def getServer(self):
        return self.__serverSocket
    
    # Returns the client facing socket object.
    def getClientFacing(self):
        return self.__clientFacingSocket
    
    # Returns the address of the client socket.
    def getClientAddress(self):
        return self.__clientAddress
    
    # Returns the size of the images being transmitted.
    def getImageSize(self):
        return self.__imageSize
    
    # Returns the data type of the images being transmitted.
    def getImageDataType(self):
        return self.__imageDataType
    
    # Returns the dimensions of the images being transmitted.
    def getImageDimensions(self):
        return self.__imageDimensions
    
    # Returns the IP address of the server.
    def getHost(self):
        return self.__host
    
    # Returns the port number of the server.
    def getPort(self):
        return self.__port
    
    # This function allows for an entire image to be received.
    def recvall(self):
        # Receives data from the socket until the entire image has been received.
        bytesReceived = 0          
        while bytesReceived < self.__imageSize:
            chunk = self.__clientFacingSocket.recv(min(self.__imageSize - bytesReceived, self.__fixedReceptionSize))
            self.__block[bytesReceived:bytesReceived+len(chunk)] = chunk
            bytesReceived += len(chunk)

    # Close all open sockets.
    def closeAll(self):
        self.__clientFacingSocket.close()
        self.__serverSocket.close()
        
    # This function allows for a single image to be acquired.
    def startSingle(self):
        # Acquire one complete image as a byte stream.
        self.recvall()
        
        # Convert the byte stream to a numpy array.
        image = np.frombuffer(self.__block, dtype=self.__imageDataType).reshape(self.__imageDimensions)
        
        # Display the acquired image.
        PIL_Image.fromarray(image).show()
        
        # Return the image.
        return image
    
    # This function allows for the socket to operate in batch mode.
    def startBatch(self, batchSize=200):
        # Initialize a three dimensional array for images.
        batch = np.zeros((batchSize, self.__imageDimensions[0], self.__imageDimensions[1]), dtype=self.__imageDataType)
        
        # Receive images until all of the images in a batch have been received.
        count = 0
        while(count < batchSize):
            self.recvall()
            image = np.frombuffer(self.__block, dtype=self.__imageDataType).reshape(self.__imageDimensions)
            batch[count] = image
            count += 1
        
        # Return the image batch.
        return batch
    
    
