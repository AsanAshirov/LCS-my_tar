#include "my_tar.h"

int open_archive_file(tar_options *options)
{
    int fd_archive;
    int flags;
    const mode_t DEFAULT_CREAT_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (options->create)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else if (options->extract)
        flags = O_RDONLY;

    fd_archive = open(options->archive_name, flags, DEFAULT_CREAT_MODE);

    return fd_archive;
}
