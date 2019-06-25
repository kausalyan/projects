
//client program
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define CPORT 8080
#define PORT 8000
void client_chat(int fd);

int main()
{
	int sock_fd = -1;
	struct sockaddr_in saddr, caddr;
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("client socket:");
		return -1;
	}
	memset(&saddr, 0, sizeof(saddr));
	memset(&caddr, 0, sizeof(caddr));
	caddr.sin_family = AF_INET;
	caddr.sin_addr.s_addr = htonl(INADDR_ANY);
	caddr.sin_port = htons(CPORT); 
	if(bind(sock_fd, (struct sockaddr*)&caddr , sizeof(caddr)) < 0)
	{
		perror("client bind:");
	}
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("172.28.3.150");
	saddr.sin_port = htons(PORT); 
	if ( connect(sock_fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
	{
		perror("client  connect:");
		return -1;
	}
	else
		printf("Connected to sevrer\n");
	client_chat(sock_fd);
	close(sock_fd);
}
#define MAX 512
void client_chat(int fd)
{
	int n ;
	char buf[MAX];
	while(1)
	{
		memset(buf, 0, MAX);
		n = 0;
		printf("client to server:");
		while((buf[n++] = getchar())!= '\n');
		write(fd, buf, MAX);
		memset(buf, 0, MAX);
		read(fd, buf, MAX);
		printf("server: %s\n",buf);
		if(strncmp("exit", buf, 4) == 0 )
		{
			printf("Chat ended\n");
			break;
		}
	}
}
