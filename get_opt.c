#include "my_tar.h"

static void print_options(tar_options *options)
{
    printf("============TAR_OPTIONS============\n");
    printf("Creation mode: %s\n", options->create ? "true" : "false");
    printf("Extraction mode: %s\n", options->extract ? "true" : "false");
    printf("Archive name: %s\n", options->archive_name);

    t_argument *tmp = options->args;
    int i = 0;

    while (tmp && tmp->filename != NULL)
    {
        printf("Argument %d:  %s\n", i, tmp->filename);
        tmp = tmp->next;
        i++;
    }
    printf("===================================\n");

    return;
}

static tar_options *init_tar_options(void)
{
    tar_options *options = malloc(sizeof(tar_options));

    if (options != NULL)
    {
        options->create = false;
        options->extract = false;
        options->args = init_argument();
        options->archive_name = NULL;
    }
    return options;
}

static tar_options *handle_options(tar_options *options, char *argument,
                                   bool *is_archive_name)
{
    int index = 0;

    while (argument[index])
    {
        if (argument[index] == 'c')
            options->create = true;
        else if (argument[index] == 'x')
            options->extract = true;
        else if (argument[index] == 'f')
        {
            *is_archive_name = true;
        }
        index++;
    }
    return options;
}

static bool validate_options(tar_options *options)
{
    if (!options->create && !options->extract)
    {
        printf("tar: Must specify one of -c, -r, -t, -u, -x\n");
        return false;
    }
    if (options->create && options->extract)
    {
        printf("tar: Can't specify both modes\n");
        return false;
    }

    if (options->archive_name == NULL)
    {
        printf("tar: Must specify a filename\n");
        return false;
    }
    return true;
}

tar_options *get_opt(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "%s: No argument specified\n", av[0]);
        return NULL;
    }

    tar_options *options = init_tar_options();
    int runner = 1;
    bool is_archive_name = false;

    while (av[runner])
    {
        if (av[runner][0] == '-')
        {
            handle_options(options, av[runner], &is_archive_name);
        }

        else if (is_archive_name == true)
        {
            options->archive_name = strdup(av[runner]);
            is_archive_name = false;
        }
        else
        {
            add_to_list(&(options)->args, av[runner]);
        }
        runner++;
    }

    if (validate_options(options) != true)
    {
        delete_options(options);
        return NULL;
    }
    print_options(options);
    return options;
}

void delete_options(tar_options *options)
{
    if (options->archive_name != NULL)
    {
        free(options->archive_name);
    }

    delete_argument_list(&(options)->args);
    free(options);
    return;
}