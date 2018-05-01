/*  Server Program for Two Way Socket Communication 
	Alan Kao [ask136]
	Ethan Liaw [exl___]
	EECS 338 Final Project  */


#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<signal.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#define MAX 80 //Max size of the buffers
#define PORT 43455 //Port number for connection within server and client
#define SA struct sockaddr //Server address struct

//Buffer to hold messages
char buff[MAX];
//Buffer to hold username of client
char nameBuff[MAX];
//Buffer to hold username of server
char otherNameBuff[MAX];
//Boolean to check if either user is trying to close the connection 
bool closed;

/*  These counters are used to stop two special cases
	from sending additional output. */
int counter = 0;
int counter2 = 0;

/*  Method to get usernames of users, send them to the other user,
    as well as show the current user the username of who they are talking to */
void getNames(int sockfd)
{

	printf("Welcome to the Instant Messaging Program!\n");
	printf("Enter '#q' to quit at any time.\n");
	printf("Please enter your username:  ");
	fflush(stdout);
	scanf("%s", nameBuff);

	write(sockfd,nameBuff,sizeof(nameBuff));
	bzero(otherNameBuff,sizeof(otherNameBuff));

	read(sockfd,otherNameBuff,sizeof(otherNameBuff));
	printf("You are connected with %s.\n", otherNameBuff);
	fflush(stdout);
}


/*  Method that contols input and output of server */
void func(int sockfd)
{
	closed = false;
	
	//used for iterating through the user input
	int n;

	//Call the fork
	pid_t pid = fork();

	//Code to send user input to client
	if(pid > 0)
	{
		//Variable to store timestamp
		time_t mytime;
		//String to store timestamp in correct format
		char* c_time_string;
		
		//This loop checks to see if the user on the serverwants to exit
		while(strncmp(buff,"#q",2)!=0 && closed == false)
		{

			bzero(buff,sizeof(buff));

			if(closed == true)
			{
				break;
			}

			//Checks for both special cases and writes user input to buffer
			if(counter != 1)
			{
				n=0;
				while((buff[n++]=getchar())!='\n');
				write(sockfd,buff,sizeof(buff));

				mytime = time(NULL);
				c_time_string = ctime(&mytime);

				//Special case 2
				if(counter2 != 0)
				{
					printf("\tfrom $%s @ %s", nameBuff, c_time_string);
					fflush(stdout);
				}

			}
			counter2++;
		}
		//Closes socket
		closed = true;
		close(sockfd);
		printf("The connection has been closed by the server.\n");
		fflush(stdout);
		kill(pid, SIGTERM);

	}
	//Code to receive message from client and print out into server
	else if(pid == 0)
	{

		//Variable to store timestamp
		time_t mytime;
		//String to store timestamp in correct format
		char* c_time_string;
		
		//This loop checks to see if the user on the client wants to exit
		while(strncmp(buff,"#q",2)!=0 && closed == false)
		{
			//Gets message from buffer
			bzero(buff,sizeof(buff));
			read(sockfd,buff,sizeof(buff));

			//Checks for case 1 and prints output
			counter++;
			if(counter != 1)
			{
				mytime = time(NULL);
				c_time_string = ctime(&mytime);
				//if(strncmp("",buff,MAX) != 0)
				printf("%s\tfrom $%s @ %s\n",buff, otherNameBuff, c_time_string);
				fflush(stdout);
			}

			//Exit call
			if(strncmp(buff,"#q",2)==0)
			{
				closed = true;
			}

		}
		//Closes socket
		close(sockfd);
		printf("The connection has been closed by the client.\n");
		fflush(stdout);
		kill(pid, SIGTERM);
	}
	//Closes socket outside of fork
	close(sockfd);
}


/* Code to take care of creating a server and connecting the client */
int main()
{
	int sockfd,connfd,len;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	//Checks for succesful socket creation
	if(sockfd==-1)
	{
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);

	//Checks for successful socket binding
	if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
	{
		printf("Socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	//Checks for successful open server lisetening for client
	if((listen(sockfd,5))!=0)
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len=sizeof(cli);
	connfd=accept(sockfd,(SA *)&cli,&len);

	//Checks for succesful acceptance of client by server
	if(connfd<0)
	{
		printf("Server acccept failed...\n");
		exit(0);
	}
	else
		printf("Server acccepted the client...\n");

	//Runs methods
	getNames(connfd);
	func(connfd);
	close(sockfd);
}
