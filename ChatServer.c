//Ethan Liaw, Alan Kao 
//EECS 338 Final Project 
//Instant Messaging Program using Sockets
//Server Program

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#define MAX 80
#define PORT 43454
#define SA struct sockaddr

void func(int sockfd)
{
	time_t mytime;
	char* c_time_string;
	
	char buff[MAX];
	char nameBuff[MAX];
	char otherNameBuff[MAX];
	char otherBuff[MAX];
	int n;

	
	bzero(nameBuff,sizeof(nameBuff));
	printf("Enter a user name: ");
	scanf("%s", nameBuff);
	
	bzero(otherNameBuff,MAX);
	write(sockfd,nameBuff,sizeof(nameBuff));
	
	bzero(otherNameBuff,MAX);
	read(sockfd,otherNameBuff,sizeof(otherNameBuff));
	
	printf("You are connected with %s.", otherNameBuff);
	
	for(;strncmp("#q",buff,2)!=0 && strncmp("#q",otherBuff,2)!=0;)
	{
		bzero(buff,MAX);
		bzero(otherBuff, MAX);
		read(sockfd,buff,sizeof(buff));
	
		//This is to get the text sent by the client
		int i;
		for(i = 0; i < MAX; i++)
			otherBuff[i] = buff[i];
		mytime = time(NULL);
		c_time_string = ctime(&mytime);
		//printf("the string is \ n");
		printf("\n$%s: %s -sent %s \n$%s: ",otherNameBuff, buff, c_time_string, nameBuff);
		//printf("\n$%s: %s\n$%s: ",otherNameBuff, buff, nameBuff);
		bzero(buff,MAX);
			n=0;
			while((buff[n++]=getchar())!='\n');
		write(sockfd,buff,sizeof(buff));
		if(strncmp("#q",buff,2)==0)
		{
			
			//break;
		}	
		
	}
	printf("The connection has been closed.\n");
}

int main()
{
	int sockfd,connfd,len;
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
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);
	if((bind(sockfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");
	if((listen(sockfd,5))!=0)
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len=sizeof(cli);
	connfd=accept(sockfd,(SA *)&cli,&len);
	if(connfd<0)
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");
	
	printf("Instant Messaging Program\n");
	
	func(connfd);
	close(sockfd);
}
