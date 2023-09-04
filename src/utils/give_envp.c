#include "../../inc/minishell.h"

char* ft_strncpy(char* destination, const char* source, size_t num)
{
    char* dest = destination;
    const char* src = source;
    size_t i;

    for (i = 0; i < num && *src != '\0'; ++i) {
        *dest++ = *src++;
    }

    for (; i < num; ++i) {
        *dest++ = '\0';
    }

    return destination;
}

/*
Extrahiert den Schlüssel und Wert aus einer Umgebungsvariablen-Zeichenkette.
Allokiert Speicher für eine Zeichenmatrix, in der der Schlüssel und Wert gespeichert werden.
Kopiert den Schlüssel und Wert in die allokierten Speicher und gibt sie zurück.
*/
char	**erstelle_Schlüssel_Wert_Matrix(char *env_variable)
{
    char **key_and_value = NULL;
    char *equal_occurrence = ft_strchr(env_variable, '=');

    if (equal_occurrence != NULL) {
        size_t key_length = equal_occurrence - env_variable;
        size_t value_length = ft_strlen(equal_occurrence + 1);

        key_and_value = (char **)ft_calloc(3, sizeof(char *));
        key_and_value[0] = (char *)ft_calloc(key_length + 1, sizeof(char));
        key_and_value[1] = (char *)ft_calloc(value_length + 1, sizeof(char));

        ft_strncpy(key_and_value[0], env_variable, key_length);
        ft_strncpy(key_and_value[1], equal_occurrence + 1, value_length);
    }

    return key_and_value;
}
/*
Erstellt eine Liste von Umgebungsvariablenknoten aus einer Liste von Umgebungsvariablen-Zeichenketten.
Ruft erstelle_Schlüssel_Wert_Matrix auf, um den Schlüssel und Wert für jede Zeichenkette zu erhalten.
Erstellt einen neuen Knoten mit Schlüssel, Wert und Umgebungsvariablenzeichenkette.
Fügt den Knoten der Umgebungsvariablenliste hinzu.
*/
t_node	*create_envp_list(char **envp)
{
	int		i;
	char	**key_and_value;
	t_node	*envp_list;
	t_node	*new_node;

	i = 0;
	envp_list = NULL;
	while (envp[i] != NULL)
	{
		key_and_value = erstelle_Schlüssel_Wert_Matrix(envp[i]);
		new_node = ft_lstnew(key_and_value[0], key_and_value[1], envp[i]);
		ft_free_matrix((void **)key_and_value);
		ft_lstadd_back(&envp_list, new_node);
		i++;
	}
	return (envp_list);
}
/*
Zählt die Anzahl der gültigen Schlüssel-Wert-Paare in einer Umgebungsvariablenliste.
Zählt die Knoten, bei denen sowohl Wert als auch Umgebungsvariablenzeichenkette vorhanden sind.
*/
static int	zähle_gültig_envp(t_node **envp)
{
    
	int		size;
	t_node	*tmp;

	size = 0;
	tmp = *envp;
	while (tmp)
	{
		if (tmp->value && tmp->env_line)
			size++;
		tmp = tmp->next;
	}
	return (size);
    
    
}

/*
Erstellt eine Zeichenkettenmatrix, die die Umgebungsvariablen repräsentiert.
Allokiert Speicher für die Matrix basierend auf der Anzahl der gültigen Schlüssel-Wert-Paare.
Extrahiert Schlüssel-Wert-Paare aus der Umgebungsvariablenliste und kopiert sie in die Matrix.
Gibt die erstellte Zeichenkettenmatrix mit den Umgebungsvariablen zurück.
*/
char	**create_envp_array(void)
{
	int		i;
	int		size;
	char	**envp;
	t_node	*tmp;

	i = 0;
	tmp = g_minishell.envp_list;
	size = zähle_gültig_envp(&g_minishell.envp_list);
	envp = ft_calloc(sizeof(char *), size + 1);
	while (tmp)
	{
		if (tmp->value && tmp->env_line)
		{
			envp[i] = ft_strdup(tmp->env_line);
			i++;
		}
		tmp = tmp->next;
	}
	return (envp);
}
