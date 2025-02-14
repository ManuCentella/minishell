#include "minishell.h"

/**
 * 🛠️ free_cmd_list - Libera la memoria de la lista de comandos.
 */
void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free(cmd->cmd);
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        free(cmd->infile);
        free(cmd->outfile);
        free(cmd->appendfile);
        free(cmd->errfile);
        free(cmd->heredoc);
        free(cmd->heredoc_content);
        free(cmd);
        cmd = tmp;
    }
}

/**
 * 🔹 print_cmd_list - Función de depuración para imprimir la lista de comandos.
 */
void print_cmd_list(t_cmd *cmd_list)
{
    t_cmd *tmp = cmd_list;
    int index = 0;
    while (tmp)
    {
        printf("Comando [%d]: %s\n", index, tmp->cmd ? tmp->cmd : "NULL");
        if (tmp->args)
        {
            for (int i = 0; tmp->args[i]; i++)
                printf("  Arg[%d]: %s\n", i, tmp->args[i]);
        }
        tmp = tmp->next;
        index++;
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    char    **tokens;
    t_cmd   *cmd_list;
    t_data  data;

    (void)argc; // Evita warnings por argumento no usado
    (void)argv;
    
    data.env = init_env(envp); // Inicializar entorno
    data.cwd = getcwd(NULL, 0);
    data.exit_status = 0;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
        {
            add_history(input);  // Guarda en el historial
            tokens = tokenize_input(input);
            cmd_list = parse_tokens(tokens, data.env, data.exit_status);
            
            /* Función de depuración: imprime la lista de comandos */
            print_cmd_list(cmd_list);

            executor(cmd_list, &data); // Ejecuta los comandos
            free_cmd_list(cmd_list);
        }
        free(input);
    }
    free(data.cwd);
    free_env_list(data.env);
    return (0);
}
