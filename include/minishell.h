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
typedef struct s_command
{
    char *cmd;            // Nombre del comando
    char **args;          // Argumentos del comando
    int builtin;          // Flag para builtins (1 si es interno, 0 si no)
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

void executor(t_cmd *cmd_list, t_data *data);
char *find_binary_path(char *cmd, t_env *env); // Asegúrate de que esta línea esté correcta
int execute_builtin_echo(t_cmd *cmd);
int pwd_builtin(t_data *data);
int cd_builtin(t_data *data, t_cmd *cmd);
void upd_env(t_data *data);
void print_msg(t_data *data, const char *msg, int fd);
t_env *get_env_var(t_env *env, const char *name);
char *ft_strjoin_free(char *s1, const char *s2, int to_free);
void ft_free_split(char **split);
char **convert_env_to_array(t_env *env);

#endif