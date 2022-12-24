#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "fifo_p1"
#define PATH2 "fifo_p2"

int err;

int chk_pipe()
{
    int fd = -1;
    do
    {
        fd = open(PATH, O_RDONLY);
    } while (fd < 0);
    return fd;
}

int make_pipe()
{
    err = mknod(PATH2, S_IFIFO | 0666, 0);
    if (err)
        perror("fifo creation");
    int fd = open(PATH2, O_WRONLY);
    if (fd < 0)
        perror("file descriptor");
    return fd;
}

int main(int argc, char const *argv[])
{
    int out = chk_pipe();
    int inp = make_pipe();
    char string_out[8];
    char idx_out[2];
    int strt = 0;
    while (strt <= 45)
    {
        for (int i = strt; i < (strt + 5); i++)
        {
            err = read(out, idx_out, 1);
            if (err < 0)
                perror("read error ");
            printf("%d ", idx_out[0] - 40);
            err = read(out, string_out, 7);
            if (err < 0)
                perror("read error ");
            printf("%s\n", string_out);
        }
        printf("highest index %d sent\n", idx_out[0] - 40);
        err = write(inp, idx_out, 1);
        if (err < 0)
            perror("write error ");
        strt = idx_out[0] - 39;
    }
    close(inp);
    close(out);
    err = unlink(PATH2);
    if (err)
        perror("fifo deletion");
    return 0;
    return 0;
}
