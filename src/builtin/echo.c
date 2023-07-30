#include "../../inc/minishell.h"
/*
Überprüft, ob der übergebene String (dash_n) den richtigen Aufbau für das Optionsschalter -n hat.
Überprüft, ob das erste Zeichen des Strings ein '-' ist. Andernfalls wird 0 zurückgegeben.
Überprüft, ob alle weiteren Zeichen des Strings 'n' sind. Wenn nicht, wird 0 zurückgegeben.
Gibt 1 zurück, wenn der String den richtigen Aufbau hat.
*/
int valid_dash_n(const char* dash_n)
{
    size_t length;
    size_t i;

    i = 1;
    if (dash_n[0] != '-')
        return 0;

    length = ft_strlen(dash_n);

    while (i < length)
    {
        if (dash_n[i] != 'n')
            return 0;
        i++;
    }

    return 1;
}
/*
Interpretiert Sonderzeichen in einem gegebenen String (str) und ersetzt sie durch die entsprechenden Steuerzeichen.
Durchläuft den String und sucht nach '\' (Backslash), das als Escape-Zeichen verwendet wird.
Wenn nach dem Backslash 'n' folgt, wird es durch ein Zeilenumbruchzeichen '\n' ersetzt.
Wenn nach dem Backslash 't' folgt, wird es durch ein Tabulatorzeichen '\t' ersetzt.
Andernfalls wird der Backslash und das nachfolgende Zeichen unverändert kopiert.
Das Ergebnis wird in derselben Zeichenkette (str) gespeichert.
*/
void interpret_special_characters(char* str)
{
    size_t len = ft_strlen(str);
    size_t i = 0;
    size_t j = 0;

    while (i < len) {
        if (str[i] == '\\') {
            i++;
            if (str[i] == 'n') {
                str[j] = '\n';
            } else if (str[i] == 't') {
                str[j] = '\t';
            } else {
                // Copy the backslash and the character literally
                str[j] = '\\';
                j++;
                str[j] = str[i];
            }
        } else {
            str[j] = str[i];
        }

        i++;
        j++;
    }

    str[j] = '\0';
}
/*
Druckt die Argumente eines Befehls auf den Ausgabestrom (out_fd).
Beginnt bei Index 1, es sei denn, das erste Argument hat den richtigen Aufbau für den Optionsschalter -n.
Interpretiert Sonderzeichen in den Argumenten mit Hilfe von interpret_special_characters.
Gibt die Argumente nacheinander aus, getrennt durch Leerzeichen.
Fügt einen Zeilenumbruch ('\n') am Ende hinzu.
*/
void print_args(int size, char** args, int out_fd)
{
    int i = 1;

    if (valid_dash_n(args[1]))
        i++;

    for (; i < size; i++) {
        interpret_special_characters(args[i]);
        ft_putstr_fd(args[i], out_fd);

        if (i != size - 1)
            ft_putstr_fd(" ", out_fd);
    }
}
/*
Implementiert den Befehl "echo" in einer Shell.
Behandelt die Ausgabe des Befehls basierend auf dem Umleitungsstatus (handle_output).
Überprüft, ob die Shell im Kindprozessmodus (g_minishell.on_fork) ist und ob die Ein- und Ausgabekanäle gültig sind.
Wenn keine Argumente vorhanden sind, gibt der Befehl einen Zeilenumbruch aus.
Ansonsten überprüft er das erste Argument auf den richtigen Aufbau des Optionsschalters -n.
Verwendet print_args, um die Argumente auszugeben und gegebenenfalls einen Zeilenumbruch hinzuzufügen.
Wenn die Shell im Kindprozessmodus ist, wird die_child aufgerufen, um den Kindprozess zu beenden.
Gibt den entsprechenden Status zurück.
*/
int ft_echo(t_command cmd) {
    int out = 1;
    handle_output(cmd, &out);

    if (g_minishell.on_fork && (cmd.input_fd == -1 || cmd.output_fd == -1))
        die_child(0, 1);

    if (!g_minishell.on_fork && (cmd.input_fd == -1 || cmd.output_fd == -1))
        return 1;

    if (cmd.number_of_args < 2) {
        ft_putstr_fd("\n", out);
    } else {
        int comparison = valid_dash_n(cmd.args[1]);
        print_args(cmd.number_of_args, cmd.args, out);

        if (comparison == 0) {
            ft_putstr_fd("\n", out);
        }
    }

    if (g_minishell.on_fork)
        die_child(0, 0);

    return 0;
}
