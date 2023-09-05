#include "../../inc/minishell.h"

char *hol_envp(t_node *envp_list, char *key)
{
    if (key[0] == '?')
        return ft_itoa(g_minishell.status_code);

    if (!key_istda(envp_list, key))
        return "";

    while (ft_strcmp(envp_list->key, key) != 0)
        envp_list = envp_list->next;

    return envp_list->value;
}

void andere_envp(t_node **envp_list, char *key, char *new_data)
{
    t_node *tmp = *envp_list;

    while (ft_strcmp(tmp->key, key) != 0)
        tmp = tmp->next;

    if (tmp->value)
        free(tmp->value);

    if (tmp->env_line)
        free(tmp->env_line);

    tmp->value = ft_strdup(new_data);
    tmp->env_line = ft_strjoin(tmp->key, "=");
    append(&tmp->env_line, ft_strdup(tmp->value));
}

int key_istda(t_node *envp_list, char *key)
{
    while (envp_list != NULL)
    {
        if (ft_strcmp(envp_list->key, key) == 0)
            return 1;

        envp_list = envp_list->next;
    }

    return 0;
}
