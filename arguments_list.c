#include "my_tar.h"

t_argument *init_argument()
{
    t_argument *new_arg = malloc(sizeof(t_argument));

    if (new_arg)
    {
        new_arg->filename = NULL;
        new_arg->next = NULL;
    }

    return new_arg;
}

void add_to_list(t_argument **head, char *argument)
{
    t_argument *tmp = *head;

    if (tmp->filename == NULL)
    {
        tmp->filename = strdup(argument);
        return;
    }

    t_argument *new_arg = init_argument();
    new_arg->filename = strdup(argument);

    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new_arg;

    return;
}

void delete_argument_list(t_argument **head)
{
    t_argument *tmp = *head;
    t_argument *current;
    while (tmp != NULL)
    {
        current = tmp;
        tmp = tmp->next;
        if (current->filename)
        {
            free(current->filename);
        }
        free(current);
    }

    *head = NULL;
    return;
}