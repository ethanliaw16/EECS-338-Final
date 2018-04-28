# EECS-338-Final

Instant Messaging Program

This program uses socket communication between a 
server and a client to create a messaging environment between two users.

The main data structure we are using is a buffer array that holds input from
each user and sends it to the other user via server-client communication.

server.c - this file creates a socket and a server for the client to connect to
client.c - this file connects to the previously created server and this connection
	is what allows the instant messaging to happen.

So far, both partners have worked on the code. Ethan worked on the sample 
output, and Alan worked on the design document. 

Our sample output that will theoretically happen is included in the ExampleOutput.txt
file. We are also considering adding the possibility of a three-way chat. 

ChatClient and Chatserver are our first version of this program. They have usernames and datetime implemented. In this version, the client program must initiate the communication (i.e. he must send the first message). In addition, the client and server must alternate in sending messages. The option of entering '#q' to disconnect is implemented in the server program, however, there are several bugs in the client program that cause the program to fail to disconnect.

Version two consists of TwoWaySender and TwoWayGetter. They also have usernames and datetime implemented. In addition, either program can send the first message, and the option of sending consecutive messages is allowed. To implement these two features, we used a fork call in order to make writing and reading data independent processes. The disconnect with '#q' feature is also implemented in both programs. currently, the implementation of this feature is highly inefficient, relying on break statements and the kill() function call for child process cleanup. 
