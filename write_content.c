#include "my_tar.h"

int get_file_size(int fd)
{

    int res = 0;
    int reader = 0;
    char buf[BLOCKSIZE];
    
    while((reader = read(fd, buf, BLOCKSIZE)) > 0)
    {
        res += reader;
    }

    if (res % BLOCKSIZE != 0)
    {
        res += BLOCKSIZE - (res % BLOCKSIZE);
    }

    lseek(fd, 0, SEEK_SET);
    return res;
}



int write_file_content(int fd_archive, char *filename)
{
    int res = 0;

    int fd_file = open(filename, O_RDONLY);
    int file_size = get_file_size(fd_file);

    char content[file_size];
    bzero(content, file_size);

    read(fd_file, content, file_size);
    write(fd_archive, content, file_size);

    close(fd_file);
    return res;

}

void end_of_archive(int fd)
{
    char end[BLOCKSIZE * 2];

    bzero(end, BLOCKSIZE *2);
    write(fd, end, BLOCKSIZE * 2);
    return ;
}
