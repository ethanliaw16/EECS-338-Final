//Client program for two-way socket communication

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<signal.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define MAX 80
#define PORT 43454
#define SA struct sockaddr

char buff[MAX];
char nameBuff[MAX];
char otherNameBuff[MAX];
bool closed;
//sem_t username_created;

void getNames(int sockfd)
{
	printf("Enter a username.  ");
	scanf("%s", nameBuff);
	write(sockfd,nameBuff,sizeof(nameBuff));
	bzero(otherNameBuff,sizeof(otherNameBuff));
	read(sockfd,otherNameBuff,sizeof(otherNameBuff));
	printf("You are connected with %s.", otherNameBuff);
}

void func(int sockfd)
{
	closed = false;
	int n;
	pid_t pid = fork();
	if(pid > 0) //output
	{
		//sem_wait(&username_created);
		time_t mytime;
		char* c_time_string;

		while(strncmp(buff,"#q",2)!=0)
		{
			//printf("\nClient output Loop");
			//sleep(.25);
			bzero(buff,sizeof(buff));

			read(sockfd,buff,sizeof(buff));
			mytime = time(NULL);
			c_time_string = ctime(&mytime);
			//if(strncmp(buff,"",MAX!=0))
				printf("%s\tfrom $%s @ %s\n",buff, otherNameBuff, c_time_string);
				//printf("%s",buff);
				//printf("the buffer is not empty.\n");
				sleep(1);

			if(strncmp(buff,"#q",2)==0)
				break;
		}
		close(sockfd);
		printf("The connection has been closed by the server.\n");
		kill(pid, SIGTERM);
	}
	else if(pid == 0) //input
	{
		time_t mytime;
		char* c_time_string;
		while(strncmp(buff,"#q",2)!=0)
		{
			//sleep(.25);
			//if(strncmp(buff,"#q",2)!=0)
				//printf("Didnt quit");
			bzero(buff,sizeof(buff));


			//printf("Your name is %s",nameBuff);
			printf("\n");

			n=0;
			while((buff[n++]=getchar())!='\n');
			write(sockfd,buff,sizeof(buff));
			mytime = time(NULL);
			c_time_string = ctime(&mytime);
			printf("\tfrom $%s @ %s", nameBuff, c_time_string);
		}
		close(sockfd);
		printf("The connection has been closed by the client.");
		kill(pid,SIGTERM);
	}
	close(sockfd);
}

int main()
{
	int sockfd,connfd;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);
	if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))!=0)
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	//printf("Instant Messaging Program\n\n");
	getNames(sockfd);
	//sem_init(&username_created,1,0);
	func(sockfd);
	close(sockfd);
	//printf("The connection has been closed.\n");
}
