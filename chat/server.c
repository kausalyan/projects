
/////server program for tcp p2p chat application//////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8000
#define MAX 512
void chat(int fd);
int main()
{
	int sock_fd =-1 ,connfd = -1, len;
	struct sockaddr_in saddr, caddr;

	sock_fd = socket(AF_INET, SOCK_STREAM ,0 );
	if(sock_fd == -1)
	{
		perror("Server socket:");
		return -1;
	}
	memset(&saddr , 0, sizeof(struct sockaddr_in));
	saddr.sin_family  = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(PORT);

	if( bind(sock_fd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("s bind:");
	}
	
	if(listen(sock_fd, 6) < 0)
	{
		perror("listen:");
	}
	
	memset(&caddr , 0, sizeof(struct sockaddr_in));
	if((connfd = accept(sock_fd, (struct sockaddr* )&caddr,(socklen_t* )&len )) < 0)
	{
		perror("accept:");
	}
	
	chat(connfd);
	
	close(sock_fd);
}
void chat(int fd)
{
	char buf[MAX];
	int n = 0;
	while(1)
	{
		memset(buf , 0, MAX);
		n = 0;
		read(fd, buf, sizeof(buf));
		printf("from client: %s\n To client: ", buf);
		memset(buf , 0, MAX);
		while((buf[n++] =  getchar()) != '\n')
			;
		write(fd , buf, MAX);
		//if message contains exit then caht exits
		if(strncmp("exit", buf, 4) == 0)
		{
			printf("~~~~~~~~~~~~~Ending Chat~~~~~~~~~~~~~\n");
			break;
		}
	}
}
