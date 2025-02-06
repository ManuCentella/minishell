#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

// --- Definición de estructuras ---
typedef struct s_redir
{
    int type;             // Tipo de redirección (<, >, >>, <<)
    char *file;           // Archivo asociado a la redirección
    struct s_redir *next; // Lista enlazada para múltiples redirecciones
} t_redir;

typedef struct s_command
{
    char *cmd;            // Nombre del comando
    char **args;          // Argumentos del comando
    int builtin;          // Flag para builtins (1 si es interno, 0 si no)

    // Redirecciones
    char *infile;         // Archivo de entrada ("<")
    char *outfile;        // Archivo de salida (">")
    char *appendfile;     // Archivo de salida en modo append (">>")
    char *errfile;        // Archivo de error ("2>")

    // Heredoc
    char *heredoc;        // Indicador de si hay un heredoc ("<<")
    char *heredoc_content; // Contenido del heredoc

    struct s_command *next; // Siguiente comando en la lista (para pipes)
} t_cmd;

typedef struct s_environment
{
    char *variable;       // Nombre de la variable de entorno
    char *value;          // Valor de la variable de entorno
    struct s_environment *next; // Lista enlazada de variables de entorno
} t_env;

typedef struct s_data
{
    t_env *env;           // Lista de variables de entorno
    char *cwd;            // Directorio de trabajo actual
} t_data;

// --- Ejecutores principales ---
void executor(t_cmd *cmd_list, t_data *data);

// --- Funciones auxiliares de executor ---
void restore_and_continue(t_cmd **cmd, int stdin_backup, int stdout_backup, int stderr_backup);
void execute_builtin(t_cmd *cmd, t_data *data);
void execute_external(t_cmd *cmd, t_data *data);
void execute_command(t_cmd *cmd, t_data *data);

// --- Builtins ---
int execute_builtin_echo(t_cmd *cmd);
int pwd_builtin(t_data *data);
int cd_builtin(t_data *data, t_cmd *cmd);
void upd_env(t_data *data);
int export_builtin(t_data *data, t_cmd *cmd);
int unset_builtin(t_data *data, t_cmd *cmd);
void env_builtin(t_data *data);
void exit_builtin(t_cmd *cmd);


// --- Utilidades ---
void print_msg(t_data *data, const char *msg, int fd);
t_env *get_env_var(t_env *env, const char *name);
char *ft_strjoin_free(char *s1, const char *s2, int to_free);
void ft_free_split(char **split);
char **convert_env_to_array(t_env *env);
void set_env_var(t_data *data, const char *name, const char *value);
int is_valid_var_name(const char *name);
int is_numeric(const char *str);
char *find_binary_path(char *cmd, t_env *env);
void command_not_found(char *cmd);
void child_process(t_cmd *cmd, char *binary_path, char **envp);


// --- Funciones de redirecciones ---
int handle_redirections(t_cmd *cmd);
void restore_stdio(int stdin_backup, int stdout_backup, int stderr_backup);
int handle_redirections(t_cmd *cmd);
void restore_stdio(int stdin_backup, int stdout_backup, int stderr_backup);

#endif
