#include "shell.h"

int _myhistory(info_t *info)
{
    list_t *node = info->history;
    int line_number = 0;

    while (node)
    {
        _printf("%d %s\n", line_number, node->str);
        node = node->next;
        line_number++;
    }

    return 0;
}

int unset_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');
    if (!p)
        return 1;

    *p = '\0';
    int ret = delete_node_at_index(&info->alias, get_node_index(info->alias, str));
    *p = '=';

    return ret;
}

int set_alias(info_t *info, char *str)
{
    char *p = _strchr(str, '=');
    if (!p)
        return 1;

    *p = '\0';
    unset_alias(info, str);
    *p = '=';

    return (add_node_end(&info->alias, str, 0) == NULL);
}

int print_alias(list_t *node)
{
    if (node)
    {
        char *p = _strchr(node->str, '=');
        if (p)
        {
            *p = '\0';
            _printf("%s'", node->str);
            _puts(p + 1);
            _puts("'\n");
            *p = '=';
            return 0;
        }
    }
    
    return 1;
}

int _myalias(info_t *info)
{
    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (int i = 1; info->argv[i]; i++)
    {
        char *p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}