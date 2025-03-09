#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "my_tar.h"


// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };



tar_header *init_tar_header()
{

    tar_header *header = malloc(BLOCKSIZE);
    if (header != NULL)
    {
        bzero(header, BLOCKSIZE);
    }
    return header;
}

char get_typeflag(int mode)
{
	switch (mode & S_IFMT)
	{
		case S_IFREG:
            return REGTYPE;
        case S_IFLNK:
            return SYMTYPE;
        case S_IFCHR:
            return CHRTYPE;
        case S_IFBLK:
            return BLKTYPE;
        case S_IFDIR:
            return DIRTYPE;
        case S_IFIFO:
            return FIFOTYPE;
		default:
			return REGTYPE;
	}
}

tar_header *get_metadata(char *filename)
{

    struct stat info;
    if (stat(filename, &info) < 0)
    {
        printf("Error opening file\n");
        return NULL;
    }

    tar_header *header = init_tar_header();


    strncpy(header->name, filename, 100);
    my_itoa_base(header->size, info.st_size, 12, OCTAL_BASE);
    my_itoa_base(header->mtime, info.st_mtime, 12, OCTAL_BASE);
    header->typeflag = get_typeflag(info.st_mode);

    return header;
}

int create_archive(int fd_archive, tar_options *options)
{
    int res = 0;
    t_argument *current_arg = options->args;
    tar_header *header;

    while (current_arg)
    {
        header = get_metadata(current_arg->filename);
        if (header != NULL)
        {
            write(fd_archive, header, BLOCKSIZE);
            write_file_content(fd_archive, current_arg->filename);
            free(header);
        }
        else {
            res++;
        }
        current_arg = current_arg->next;
    }

    end_of_archive(fd_archive);
    return res;
}