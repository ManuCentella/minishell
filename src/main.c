#include "minishell.h"
#include <signal.h>
#include <termios.h>

void disable_echoctl(void)
{
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term); // Obtener configuración actual del terminal
    term.c_lflag &= ~ECHOCTL;       // 🔹 Deshabilitar impresión de caracteres de control (como ^C)
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Aplicar configuración inmediatamente
}



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
 * 🛠️ signal_handler - Maneja `Ctrl+C` y `Ctrl+\`
 */
void signal_handler(int sig)
{
    if (sig == SIGINT) // Ctrl+C
    {
        printf("\n");          // Nueva línea para evitar caracteres extra
        rl_on_new_line();       // Resetea readline()
        rl_replace_line("", 0); // Borra la línea actual
        rl_redisplay();         // Redibuja el prompt sin imprimir ^C
    }
}



int main(int argc, char **argv, char **envp)
{
    char    *input;
    char    **tokens;
    t_cmd   *cmd_list;
    t_data  data;

    (void)argc;
    (void)argv;
    
    data.env = init_env(envp);
    data.cwd = getcwd(NULL, 0);
    data.exit_status = 0;

    // ✅ Configurar señales
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);

    // ✅ Desactivar impresión de `^C`
    disable_echoctl();

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            add_history(input);
            tokens = tokenize_input(input);
            cmd_list = parse_tokens(tokens, data.env, data.exit_status);
            executor(cmd_list, &data);
            free_cmd_list(cmd_list);
        }
        free(input);
    }
    free(data.cwd);
    free_env_list(data.env);
    return (0);
}
