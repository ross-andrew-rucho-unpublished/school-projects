# Ross Rucho
# ratrucho@gmail.com
# text-server.py
# 05/16/19
#
# Socket programming example server for basic text.

from socket import *

host = '127.0.0.1'          # Standard loopback interface address (localhost)
serverPort = 12000          # Port to listen on (non-privileged ports are > 1023)
fixedReceptionSize = 2048

# Configure and open TCP/IP server socket.
with socket(AF_INET, SOCK_STREAM) as serverSocket:
    serverSocket.bind((host, serverPort))
    serverSocket.listen()
    print('The server is ready to receive.')

    while True:
        # Configure and open TCP/IP connection socket.
        connectionSocket, address = serverSocket.accept()
        with connectionSocket:
            print('Connected by', address)
            receivedMessage = connectionSocket.recv(fixedReceptionSize).decode()
            print(receivedMessage)
            message = receivedMessage.upper()
            connectionSocket.send(message.encode())
            
            
