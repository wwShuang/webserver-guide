
//server	
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
 #include <unistd.h>
 
using namespace std;
#define BACKLOG 10
 
int main(int argc, char * argv[]){
	int connfd, sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in tempaddr;
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	char ip_str[INET_ADDRSTRLEN];
	int ret_val;
	
	socklen_t templen;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);    //1. int socket(int domain, int type, int protocol);
	if(sockfd == -1){
		perror("socket");
		exit(1);
	}
 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = 0;
	
	ret_val = bind(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr));   //2. int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
	if(ret_val == -1){
		perror("bind");
		exit(1);
	}
	cout<< "the sockfd is "<< sockfd << endl;
	ret_val = listen(sockfd,BACKLOG);  //3. int listen(int socket, int backlog);
	if(ret_val == -1){
		perror("listen");
		exit(1);
	}
 
	templen = sizeof(struct sockaddr);
	ret_val =  getsockname(sockfd, (struct sockaddr *)&tempaddr, &templen);
	if(ret_val == -1){
		perror("getsockname");
		exit(1);
	}
 
	cout<<"Server is listening on port "<< ntohs(tempaddr.sin_port)<<endl;
	for(;;){
		clilen = sizeof(cliaddr);
		connfd = accept(sockfd,(struct sockaddr *) &cliaddr,&clilen);  //4.  int accept(int s, struct sockaddr *addr, socklen_t *addrlen);
		if(connfd == -1){
			perror("accept");
			continue;
		}
		cout<< " Sever: client "<< inet_ntoa(cliaddr.sin_addr) << " connect"<<endl;
		close(connfd);
	}
	return 0;
}
