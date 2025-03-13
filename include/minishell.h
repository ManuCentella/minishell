/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:32:26 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/12 16:27:00 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>

// --- Definición de estructuras ---
typedef struct s_redir
{
	// Tipo de redirección (<, >, >>, <<)
	int				type;
	// Archivo asociado a la redirección
	char			*file;
	// Lista enlazada para múltiples redirecciones
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	// Nombre del comando
	char				*cmd;
	// Argumentos del comando
	char				**args;
	// Flag para builtins (1 si es interno, 0 si no)
	int					builtin;
	// Redirecciones
	// Archivo de entrada ("<")
	char				*infile;
	// Archivo de salida (">")
	char				*outfile;
	// Archivo de salida en modo append (">>")
	char				*appendfile;
	// Archivo de error ("2>")
	char				*errfile;
	// Heredoc
	// Indicador de si hay un heredoc ("<<")
	char				*heredoc;
	// Contenido del heredoc
	char				*heredoc_content;
	// 🔥 File descriptor del heredoc (para evitar redirecciones repetidas)
	int					heredoc_fd;
	int					is_piped;
	// Siguiente comando en la lista (para pipes)
	struct s_command	*next;
}	t_cmd;

// Nombre de la variable de entorno
// Valor de la variable de entorno
// Lista enlazada de variables de entorno
typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}	t_env;

// Lista de variables de entorno
// Directorio de trabajo actual
// Código de salida del último comando ejecutado
typedef struct s_data
{
	t_env	*env;
	char	*cwd;
	int		exit_status;
}	t_data;

// 🔹 Ya existe
// 🔹 Nuevo campo para marcar $ escapado
typedef struct s_tokenizer
{
	char	*input;
	int		i;
	int		len;
	char	**tokens;
	int		token_count;
	int		inside_double_quotes;
	bool	is_escaped_dollar;
}	t_tokenizer;

typedef struct s_pipe_data
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	last_pid;
	t_data	*data;
}	t_pipe_data;

typedef struct s_export_context
{
	t_data	*data;
	t_cmd	*cmd;
	int		index;
}	t_export_content;

typedef struct s_expansion_context
{
	t_env	*env;
	int		exit_status;
}	t_expansion_context;

// --- Ejecutores principales ---
void	executor(t_cmd *cmd_list, t_data *data);
void	execute_piped_commands(t_cmd *cmd_list, t_data *data);
//int		is_critical_builtin(t_cmd *cmd);

// --- Funciones auxiliares de executor ---
//void	restore_and_continue(t_cmd **cmd, int stdin_backup,
//		int stdout_backup, int stderr_backup);
void	execute_builtin(t_cmd *cmd, t_data *data);
void	execute_external(t_cmd *cmd, t_data *data);
void	execute_command(t_cmd *cmd, t_data *data);

// --- Builtins ---
int		execute_builtin_echo(t_cmd *cmd);
int		pwd_builtin(t_data *data);
int		cd_builtin(t_data *data, t_cmd *cmd);
void	upd_env(t_data *data);
int		export_builtin(t_data *data, t_cmd *cmd);
int		unset_builtin(t_data *data, t_cmd *cmd);
void	env_builtin(t_data *data);
void	exit_builtin(t_cmd *cmd);
int		is_builtin(char *cmd);

// --- Utilidades ---
void	print_msg(t_data *data, const char *msg, int fd);
t_env	*get_env_var(t_env *env, const char *name);
char	*ft_strjoin_free(char *s1, const char *s2, int to_free);
void	ft_free_split(char **split);
char	**convert_env_to_array(t_env *env);
void	set_env_var(t_env **env, const char *name, const char *value);
int		is_valid_var_name(const char *name);
int		is_numeric(const char *str);
char	*find_binary_path(char *cmd, t_env *env);
void	command_not_found(char *cmd);
void	child_process(t_cmd *cmd, char *binary_path, char **envp);

// --- Funciones de redirecciones ---
int		handle_redirections(t_cmd *cmd);
void	restore_stdio(int stdin_backup, int stdout_backup, int stderr_backup);
int		handle_heredoc(t_cmd *cmd);
int		handle_all_heredocs(t_cmd *cmd_list); // 🔥 Añadir esta línea
int		handle_all_heredocs(t_cmd *cmd_list);

// --- Funciones de tokenización (Públicas) ---
char	**tokenize_input(char *input);
void	process_next_token(t_tokenizer *t);
void	handle_quotes(t_tokenizer *t, char quote);
void	handle_escaped_chars(t_tokenizer *t, char *buffer, int *j);
void	handle_metacharacters(t_tokenizer *t);
void	add_token(t_tokenizer *t, char *start, int length);

// --- Funciones auxiliares que usa tokenizer.c ---
int		ft_isspace(char c);
int		ft_is_metachar(char c);
void	skip_whitespace(t_tokenizer *t);
char	**allocate_new_tokens(t_tokenizer *t);
void	copy_existing_tokens(char **new_tokens, char **old_tokens, int count);

t_cmd	*parse_tokens(char **tokens, t_env *env, int exit_status);
char	*expand_variable(char *arg, t_env *env, int exit_status);

char	*ft_strndup(const char *s, size_t n);
t_env	*init_env(char **envp);

void	print_env_vars(t_env *env);
void	free_env_list(t_env *env);

void	restore_and_close_stdio(int stdin_backup,
			int stdout_backup, int stderr_backup);
void	execute_commands(t_cmd *cmd_list, t_data *data);
// int	skip_quotes(char *input, int pos);

void	wait_for_child(pid_t pid, t_data *data);
char	*get_binary_path(t_cmd *cmd, t_data *data);
void	backup_stdio(int *stdin_backup, int *stdout_backup, int *stderr_backup);
char	*extract_var_name(char *arg, int *i);

void	append_char(char **expanded, char c, int *i);
void	expand_dollar(char **expanded, char *arg, int *i,
			t_expansion_context *context);

void	process_command(t_cmd *cmd, t_pipe_data *pipe_data);

void	disable_echoctl(void);
void	signal_handler(int sig);
void	process_input(t_data *data);

void	append_char(char **expanded, char c, int *i);
char	*get_variable_value(const char *var_name, t_env *env, int exit_status);
t_env	*init_env(char **envp);
t_env	*get_env_var(t_env *env, const char *name);

#endif
