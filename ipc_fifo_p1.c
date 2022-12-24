#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define TICK struct timespec
#define NANO 1000000000
#define PATH "fifo_p1"
#define PATH2 "fifo_p2"

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
            perror("time");
        for (int j = 0; j < 50; j++)
        {
            fifty_strngs[j][i] = (rand() % 26) + 97;
        }
    }
    for (int j = 0; j < 50; j++)
        fifty_strngs[j][7] = '\0';
    return fifty_strngs;
}

int make_pipe()
{
    err = mknod(PATH, S_IFIFO | 0666, 0);
    if (err)
        perror("xcreation");
    int fd = open(PATH, O_WRONLY);
    if (fd < 0)
        perror("file descriptor");
    return fd;
}

int chk_pipe()
{
    int fd = -1;
    do
    {
        fd = open(PATH2, O_RDONLY);
    } while (fd < 0);
    return fd;
}

int main(int argc, char const *argv[])
{
    char *id = malloc(2 * sizeof(char));
    char **fifty = string_smith();
    int inp = make_pipe();
    int out = chk_pipe();
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
            err = write(inp, idx, 1);
            if (err < 0)
                perror("write error");
            err = write(inp, fifty[i], 7);
            if (err < 0)
                perror("write error");
        }

        err = read(out, id, 1);
        if (err < 0)
            perror("read error");
        printf("highest index %d received\n", id[0] - 40);
        idx_in = id[0] + 1;
    }
    clock_gettime(CLOCK_REALTIME, &fsh);
    close(out);
    close(inp);
    err = unlink(PATH);
    if (err)
        perror("fifo deletion");
    printf("time elapsed for fifo : %f\n", watcher(strt, fsh));
    return 0;
}