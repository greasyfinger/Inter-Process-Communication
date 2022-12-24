#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define TICK struct timespec
#define NANO 1000000000
#define PATH "ipc_socket"
#define sckt struct sockaddr_un

int err;
TICK strt;
TICK fsh;

double watcher(TICK rolly, TICK pasha)
{
    long good_mornin = (rolly.tv_sec * NANO + rolly.tv_nsec);
    long good_night = (pasha.tv_sec * NANO + pasha.tv_nsec);
    double reiss = (double)(good_night - good_mornin);
    return reiss / NANO;
}

char **string_smith()
{
    TICK time_stamp;
    char **fifty_strngs = malloc(50 * sizeof(char *));
    for (int i = 0; i < 50; i++)
    {
        fifty_strngs[i] = malloc(10 * sizeof(char));
    }

    srand(time_stamp.tv_nsec);
    for (int i = 0; i < 7; i++)
    {
        err = clock_gettime(CLOCK_MONOTONIC, &time_stamp);
        if (err)
        {
            perror("time");
            exit(-1);
        }
        for (int j = 0; j < 50; j++)
        {
            fifty_strngs[j][i] = (rand() % 26) + 97;
        }
    }
    for (int j = 0; j < 50; j++)
        fifty_strngs[j][7] = '\0';
    return fifty_strngs;
}

int socket_init()
{
    sckt addr;
    int fd, sc;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        perror("socket error");
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, PATH);
    unlink(PATH);
    char *s = addr.sun_path;
    strcpy(s, PATH);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind error");
        exit(-1);
    }
    if (listen(fd, 0) < 0)
    {
        perror("listen error");
        exit(-1);
    }
    sc = accept(fd, NULL, NULL);
    if (sc < 0)
    {
        perror("accept error");
        exit(-1);
    }
    return sc;
}

int main(int argc, char const *argv[])
{
    char *id = malloc(2 * sizeof(char));
    char **fifty = string_smith();
    char string_out[8];
    int fd = socket_init();
    int idx_in = 40;
    clock_gettime(CLOCK_REALTIME, &strt);
    while (idx_in < 90)
    {
        int stp = 5 + idx_in - 40;
        int strt = idx_in - 40;
        for (int i = strt; i < stp; i++)
        {
            char *idx = malloc(2 * sizeof(char));
            idx[0] = i + 40;
            idx[1] = '\0';
            err = write(fd, idx, 1);
            if (err < 0)
            {
                perror("write error");
                exit(-1);
            }
            err = write(fd, fifty[i], 7);
            if (err < 0)
            {
                perror("write error");
                exit(-1);
            }
        }

        err = read(fd, id, 1);
        if (err < 0)
        {
            perror("read error");
            exit(-1);
        }
        printf("highest index %d received\n", id[0] - 40);
        idx_in = id[0] + 1;
    }
    clock_gettime(CLOCK_REALTIME, &fsh);
    close(fd);
    err = unlink(PATH);
    if (err)
    {
        perror("fifo deletion");
        err = unlink(PATH);
        exit(-1);
    }
    printf("time elapsed for socket : %f\n", watcher(strt, fsh));
    return 0;
}