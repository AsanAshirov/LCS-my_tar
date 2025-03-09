#include "my_tar.h"


int create_file()
{
    open()
    set_modification_time()
    write()


}


int extract_archive(int fd_archive, tar_options *options)
{

    int archive_size = get_archive_size();
    char *archive_content = get_archive_content();

    tar_header *header;
    int index = 0;

    while (index < archive_size)
    {
        header = (tar_header*)&archive_content[index];

        if (is_header(header))
        {
print_header()
        }

        index = get_to_next_block()
    }



    
}