// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

void transfer(int sock){

      int *n,i,e=0,c=0,k=0;
      n=&i;
      printf("Expect\tFrame status\tACK status");
     while((read(sock,n,sizeof(i)))!=0){
     c++;
          if(c==7){
            continue;
          }
          printf("\n%d\t Frame no:%d\t",k,i);
          if(e==i){
          i=(i+1)%2;
          e=i;
          
          printf("ACK no:%d",i);
          write(sock,n,sizeof(i));
          k++;
          }
          else{
            printf("Wrong frame");
          }
      }
    
}

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd,n;
	struct sockaddr_in serv_addr;
	char str[5];
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	  
        transfer(sock);
	// closing the connected socket
	close(client_fd);
	return 0;
}

