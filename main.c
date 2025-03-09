#include "my_tar.h"

int error(char *err_message, int exit_code)
{
    fprintf(stderr, "%s\n", err_message);
    return exit_code;
}

int main(int ac, char **av)
{
    int res = 0;
    int fd_archive;
    tar_options *options = get_opt(ac, av);

    if (options ==  NULL)
    {
        return (error("Error parsing options", 1));
    }
    fd_archive = open_archive_file(options);
    if (fd_archive < 0)
    {
        delete_options(options);
        return (error("Error opening archive", 2));
    }

    if (options->create == true)
       res += create_archive(fd_archive, options);
    // else if (options->extract)
    //     res += extract_archive(fd_archive, options);

    close(fd_archive);
    delete_options(options);    
    return res;
}