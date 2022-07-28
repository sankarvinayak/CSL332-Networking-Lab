#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
void transfer(FILE *file, int sock)
{
    char buffer[1024];
    while ((read(sock, buffer, sizeof(buffer)) > 0))
    {
        fprintf(file,"%s",buffer);
        memset(buffer,0,sizeof(buffer));
    }
}
int main(int argc, char const *argv[])
{
    FILE *file;
    char name[20];
    int sock;
    struct sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    connect(sock, (struct sockaddr *)&server, sizeof(server));
    printf("Enter file name");
    scanf("%s", name);
    write(sock, name, strlen(name));
    file = fopen(name, "w");
    transfer(file, sock);

    return 0;
}
