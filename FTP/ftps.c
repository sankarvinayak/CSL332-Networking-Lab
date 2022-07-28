#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
void transfer(FILE *file, int sock)
{
    char buffer[1024];
    while (fgets(buffer, 1024, file))
    {
        printf("In loop");
        write(sock, buffer, sizeof(buffer));
        memset(buffer, 0, sizeof(buffer));
    }
}
int main(int argc, char const *argv[])
{
    FILE *file;
    char name[20];
    int sock, cli, len;
    struct sockaddr_in server, client;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    bind(sock, (struct sockaddr *)&server, sizeof(server));
    listen(sock, 5);
    len = sizeof(client);
    cli = accept(sock, (struct sockaddr *)&cli, &len);
    read(cli, name, sizeof(name));
    printf("FIle name %s", name);

    file = fopen(name, "r");
    if (file == NULL)
    {
        printf("Error");
    }
    transfer(file, cli);
    return 0;
}
