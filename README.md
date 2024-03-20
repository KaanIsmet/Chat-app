# Simple Chat Application using TCP Socket Programming
This is a simple chat application written in C using socket programming with TCP. The application allows the client to connect to a server and communicate with each other in real-time.

## Requirements
To run this application, you will need:

C compiler (e.g. gcc) \
TCP/IP networking capabilities
## Usage
Compile the source code using the following command:
```console
gcc chat_server.c -o chat_server
gcc chat_client.c -o chat_client
```

Start the server by running chat_server and the port number:
```console
./chat_server <port_number>
```
Start the client by running chat_client and specify the IP address of the server:
```console
./chat_client <server IP address> <port number>
```
Once the client is connected to the server, you can send messages to other connected clients by typing them in the console.

## Functionality
The application has the following functionality:

* Client can directly send messages to the server.
* Server can read the messages from the Client.
* Server can also send messages to the Client.
* Client can also read the messages from the server.
## Implementation Details
The applications uses TCP socket programming to establish connections between the server and the client. The server application listens for incoming messages from the client on a specified port and can message back to the client.

The client application connects to the server using the server's IP address and its port number. The client communicates with the server by using TCP that is a reliable, connection-oriented protocol that provides a guaranteed delivery of data packets between the client and server. The TCP protocol also ensures that data is delivered in the correct order and provides flow control mechanisms to prevent data loss due to congestion.
