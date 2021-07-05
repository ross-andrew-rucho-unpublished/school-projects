# Ross Rucho
# ratrucho@gmail.com
# image-client.py
# 05/21/19
#
# This is a basic template for a tcp client in python. Its purpose
# is to test transmission and reception of an image of known dimensions
# and resolution to and from a server.
# This is a specific solution. It must be modified to work in general.

import sys
from socket import *
from PIL import Image as PIL_Image
import numpy as np
import matplotlib.image as mpimg

host = '127.0.0.1'              # The server's hostname or IP address.
serverPort = 12000              # Arbitrarily chosen port (non-privileged ports are > 1023).
fixedReceptionSize = 2048
imageResolution = 'uint16'
imageDimensions = (512, 512)

# Read image to transmit.
image = mpimg.imread('test-image.jpg')[:,:,0]
message = image.tobytes()
messageSize = image.nbytes

# Iteratively reads data until blockSize bytes have been read.
def recvall(currentSocket, blockSize):
    block = []
    bytesReceived = 0

    while bytesReceived < blockSize:
        chunk = currentSocket.recv(min(blockSize - bytesReceived, fixedReceptionSize))
        if chunk == b'':
            raise RuntimeError("Socket connection broken.")

        block.append(chunk)
        bytesReceived += len(chunk)

    return b''.join(block)

# Configure and open TCP/IP client socket.
with socket(AF_INET, SOCK_STREAM) as clientSocket:
    clientSocket.connect((host, serverPort))
    
    # Transmit/Receive image size to and from server.
    clientSocket.sendall(str(messageSize).encode())
    receivedSize = clientSocket.recv(fixedReceptionSize).decode()
    
    # Transmit image to server.
    clientSocket.sendall(message)

    # Receive image from server.
    receivedMessage = recvall(clientSocket, messageSize)
    
    # Format image and display.
    receivedImage = np.frombuffer(receivedMessage, dtype = imageResolution).reshape(imageDimensions)
    PIL_Image.fromarray(receivedImage).show()

    
