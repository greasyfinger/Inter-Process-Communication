#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define TICK struct timespec
#define PATH "ipc_socket"
#define sckt struct sockaddr_un

int err;

int socket_init()
{
    sckt addr;
    int fd, sc;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        perror("socket error");
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, PATH);
    char *s = addr.sun_path;
    strcpy(s, PATH);
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect error");
        exit(-1);
    }
    return fd;
}

int main(int argc, char const *argv[])
{
    int fd = socket_init();
    char string_out[8];
    char idx_out[2];
    int strt = 0;
    while (strt <= 45)
    {
        for (int i = strt; i < (strt + 5); i++)
        {
            err = read(fd, idx_out, 1);
            if (err < 0)
                perror("read error ");
            printf("%d ", idx_out[0] - 40);
            err = read(fd, string_out, 7);
            if (err < 0)
                perror("read error ");
            printf("%s\n", string_out);
        }
        err = write(fd, idx_out, 1);
        if (err < 0)
            perror("write error ");
        printf("highest index %d sent\n", idx_out[0] - 40);
        strt = idx_out[0] - 39;
    }
    return 0;
}
