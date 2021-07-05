# Ross Rucho
# ratrucho@gmail.com
# image-server.py
# 05/28/19
#
# This is a basic template for a tcp server in python. Its purpose
# is to test transmission and reception of an image of known dimensions
# and resolution to and from a client.
# This is a specific solution. It must be modified to work in general.

import sys
from socket import *
from PIL import Image as PIL_Image
import numpy as np

#%%
host = ''                       # Server will accept connections on all available IPv4 interfaces.
serverPort = 12000              # Arbitrarily chosen port (non-privileged ports are > 1023).
fixedReceptionSize = 2048
imageResolution = 'uint16'
imageDimensions = (512, 512)

# Iteratively read data until blockSize bytes have been read.
def recvall(currentSocket, blockSize):
    global block        # Workaround to declare an uninitialized bytearray.
    bytesReceived = 0

    while bytesReceived < blockSize:
        chunk = currentSocket.recv(min(blockSize - bytesReceived, fixedReceptionSize)) 
        if chunk == b'':
            raise RuntimeError("Socket connection broken.")

        block[bytesReceived:bytesReceived+len(chunk)] = chunk
        bytesReceived += len(chunk)

    return block

# Configure and open TCP/IP server socket.
with socket(AF_INET, SOCK_STREAM) as serverSocket:
    serverSocket.bind((host, serverPort))
    serverSocket.listen()
    print('The server is ready to receive.')

    # Configure and open TCP/IP connection socket.
    clientFacingSocket, address = serverSocket.accept()
    print('Connected by', address)
    with clientFacingSocket:
        # Read/write image size to and from client
        receivedSize = clientFacingSocket.recv(fixedReceptionSize)
        clientFacingSocket.sendall(receivedSize)
        
        # Configure parameters given the size of the image.
        imageSizeBytes = int(receivedSize.decode())
        block = bytearray(imageSizeBytes)   # Initialize the bytearray
        
        # Read image from client
        receivedMessage = recvall(clientFacingSocket, imageSizeBytes)
        
        # Format image and display
        receivedImage = np.frombuffer(receivedMessage, dtype = imageResolution).reshape(imageDimensions)
        PIL_Image.fromarray(receivedImage).show()
        
        # Write image to client
        message = receivedImage.tobytes()
        clientFacingSocket.sendall(message)
        
        
