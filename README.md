# EECS-338-Final

# Instant Messaging Program

This program uses socket communication between a 
server and a client to create a messaging environment between two users.

## Beta Version

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

Version two consists of TwoWaySender and TwoWayGetter. They also have usernames and datetime implemented. In addition, either program can send the first message, and the option of sending consecutive messages is allowed. To implement these two features, we used a fork call in order to make writing and reading data independent processes. The disconnect with '#q' feature is also implemented in both programs. Currently, the implementation of this feature is highly inefficient, relying on break statements and the kill() function call for child process cleanup. 


## Final Version Design Document:

### Summary:
The project we created is an instant messaging program. Using socket communication between a server and client, we form a platform where both users can enter messages, as many as they want at a time. The program will timestamp both input and output for each user, with a user being able to see that they sent a certain message at a certain time and what time their chat partner sent a message to them. 

### Files:

TwoWaySender
-This file consists of the "server" side of this instant messaging program. It runs very simlar to the client, with the key difference being that the server creates the port and address for the client to connect to. Also, the server uses the "closed" boolean while the client does not.

TwoWayGetter
-This file consists of the "client" side of this instant messaging program. It runs very similarly to the server, except for the fact that it only needs to connect to the server, as well as a switched format for what the child and parent does in the fork. 


### Major Data Stcutures:

char buff[]
-This array buffer is used for holding the messages that users send to each other. It is written and read to via socket communication. Its size is controlled by the directive MAX, currently set at 80.

char nameBuff[]
-This array buffer is used for holding the username for the user within its file. If its in the TwoWayGetter, it is holding the client username, and if its in the TwoWaySender, it is holding the server username. Its size is also controlled by the directive MAX, currently set at 80.

char otherNameBuff[]
-This array buffer is used for holding the username for whoever the user within its file is talking to. If its in the TwoWayGetter, it is holding the server username, and if its in the TwoWaySender, it is holding the client username.

int counter 
int counter2
-These counters are used for preventing each program from printing redudant output in certain special cases. We found that the program would print twich who the user was connected with, as well as printing an additional timestamp before any user input. These counters take away those issues.

int n
-This counter is used for iterating through user input and writing it to the buffer.

### Sample Output:

```
~$ ./TwoWaySender
Socket successfully created..
Socket successfully binded..
Server listening..
Server acccepted the client...
Welcome to the Instant Messaging Program!
Enter '#q' to quit at any time.
Please enter your username:  user1
You are connected with user2.
Hey!
        from $user1 @ Mon Apr 20 22:12:51 2018

Hello!
        from $user2 @ Mon Apr 20 22:12:53 2018

Bye!
        from $user1 @ Mon Apr 20 22:13:00 2018

Cya!
        from $user2 @ Mon Apr 20 22:13:19 2018

#q
        from $user1 @ Mon Apr 20 22:13:40 2018
The connection has been closed by the server.
~$ 



~$ ./TwoWayGetter
Socket successfully created..
Connected to the server
Welcome to the Instant Messaging Program!
Enter '#q' to quit at any time.
Please enter your username:  user2
You are connected with user1.
Hey!
        from $user1 @ Mon Apr 20 22:12:51 2018

Hello!
        from $user2 @ Mon Apr 20 22:12:53 2018

Bye!
        from $user1 @ Mon Apr 20 22:13:00 2018

Cya!
        from $user2 @ Mon Apr 20 22:13:19 2018

#q
        from $user1 @ Mon Apr 20 22:13:40 2018
The connection has been closed by the server.
~$ 
```

### Distribution of Work
Ethan:
Worked on the primary format of the code, drafted the majority of the functions and methodology of project.
Alan:
Did most of the debugging, fixing up and commenting the code, as well as writing the design document. 



