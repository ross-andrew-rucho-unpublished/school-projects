# Ross Rucho
# ratrucho@gmail.com
# text-client.py
# 05/16/19
#
# Socket programming example client for basic text.

from socket import *

host = '127.0.0.1'          # The server's hostname or IP address.
serverPort = 12000          # Arbitrarily chosen port (non-privileged ports are > 1023).
fixedReceptionSize = 2048

# Configure and open TCP/IP client socket.
with socket(AF_INET, SOCK_STREAM) as clientSocket:
    clientSocket.connect((host, serverPort))
    message = input('Input lowercase sentence: ')
    clientSocket.send(message.encode())
    recievedMessage = clientSocket.recv(fixedReceptionSize)

print('From server: ', recievedMessage.decode())

