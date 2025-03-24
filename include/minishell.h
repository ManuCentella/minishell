/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:32:26 by szaghdad          #+#    #+#             */
/*   Updated: 2025/03/24 19:39:03 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

/* -------------------- INCLUDES -------------------- */
# include "../libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* -------------------- TYPEDEFS Y ESTRUCTURAS -------------------- */
typedef struct sigaction	t_siga;

typedef struct s_redir
{
	int						type;
	char					*file;
	struct s_redir			*next;
}							t_redir;

typedef struct s_command
{
	char					*cmd;
	char					**args;
	int						builtin;
	char					*infile;
	char					*outfile;
	char					*appendfile;
	char					*errfile;
	char					*heredoc;
	char					*heredoc_content;
	int						heredoc_fd;
	int						is_piped;
	struct s_command		*next;
}							t_cmd;

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}							t_env;

typedef struct s_data
{
	t_env					*env;
	char					*cwd;
	int						exit_status;
}							t_data;

typedef struct s_tokenizer
{
	char					*input;
	int						i;
	int						len;
	char					**tokens;
	int						token_count;
	int						inside_double_quotes;
	bool					is_escaped_dollar;
}							t_tokenizer;

typedef struct s_pipe_data
{
	int						prev_fd;
	int						pipe_fd[2];
	pid_t					last_pid;
	t_data					*data;
}							t_pipe_data;

typedef struct s_export_context
{
	t_data					*data;
	t_cmd					*cmd;
	int						index;
}							t_export_content;

typedef struct s_expansion_context
{
	t_env					*env;
	int						exit_status;
}							t_expansion_context;

/* ==================== DECLARACIÓN DE FUNCIONES ==================== */

/* ---------- 1. EJECUTORES ---------- */
// Ejecutores principales
void						executor(t_cmd *cmd_list, t_data *data);
void						execute_piped_commands(t_cmd *cmd_list,
								t_data *data);

// Funciones auxiliares de executor
void						execute_builtin(t_cmd *cmd, t_data *data);
void						execute_external(t_cmd *cmd, t_data *data);
void						execute_command(t_cmd *cmd, t_data *data);

/* ---------- 2. BUILTINS ---------- */
int							execute_builtin_echo(t_cmd *cmd);
int							pwd_builtin(t_data *data);
int							cd_builtin(t_data *data, t_cmd *cmd);
void						upd_env(t_data *data);
int							export_builtin(t_data *data, t_cmd *cmd);
int							unset_builtin(t_data *data, t_cmd *cmd);
void						env_builtin(t_data *data);
void						exit_builtin(t_cmd *cmd);
int							is_builtin(char *cmd);

/* ---------- 3. UTILIDADES DEL ENTORNO Y MANEJO DE ERRORES ---------- */
void						print_msg(t_data *data, const char *msg, int fd);
t_env						*get_env_var(t_env *env, const char *name);
char						*ft_strjoin_free(char *s1, const char *s2,
								int to_free);
void						ft_free_split(char **split);
char						**convert_env_to_array(t_env *env);
void						set_env_var(t_env **env, const char *name,
								const char *value);
int							is_valid_var_name(const char *name);
int							is_numeric(const char *str);
char						*find_binary_path(char *cmd, t_env *env);
void						command_not_found(char *cmd);
void						child_process(t_cmd *cmd, char *binary_path,
								char **envp);
char						*ft_strndup(const char *s, size_t n);
t_env						*init_env(char **envp);
void						print_env_vars(t_env *env);
void						free_env_list(t_env *env);

/* ---------- 4. REDIRECCIONES Y HEREDOC ---------- */
int							handle_redirections(t_cmd *cmd);
void						restore_stdio(int stdin_backup, int stdout_backup,
								int stderr_backup);
int							handle_heredoc(t_cmd *cmd);
int							handle_all_heredocs(t_cmd *cmd_list);

/* ---------- 5. TOKENIZACIÓN ---------- */
// Funciones públicas
char						**tokenize_input(char *input);
void						process_next_token(t_tokenizer *t);
void						handle_quotes(t_tokenizer *t, char quote);
void						handle_escaped_chars(t_tokenizer *t, char *buffer,
								int *j);
void						handle_metacharacters(t_tokenizer *t);
void						add_token(t_tokenizer *t, char *start, int length);

// Funciones auxiliares
int							ft_isspace(char c);
int							ft_is_metachar(char c);
void						skip_whitespace(t_tokenizer *t);
char						**allocate_new_tokens(t_tokenizer *t);
void						copy_existing_tokens(char **new_tokens,
								char **old_tokens, int count);

/* ---------- 6. PARSING Y EXPANSIÓN DE VARIABLES ---------- */
t_cmd						*parse_tokens(char **tokens, t_env *env,
								int exit_status);
char						*expand_variable(char *arg, t_env *env,
								int exit_status);

/* ---------- 7. MANEJO DE STDIO Y EJECUCIÓN DE COMANDOS ---------- */
void						restore_and_close_stdio(int stdin_backup,
								int stdout_backup, int stderr_backup);
void						execute_commands(t_cmd *cmd_list, t_data *data);
void						wait_for_child(pid_t pid, t_data *data);
char						*get_binary_path(t_cmd *cmd, t_data *data);
void						backup_stdio(int *stdin_backup, int *stdout_backup,
								int *stderr_backup);
char						*extract_var_name(char *arg, int *i);

/* ---------- 8. EXPANSIÓN DE VARIABLES ---------- */
void						append_char(char **expanded, char c, int *i);
void						expand_dollar(char **expanded, char *arg, int *i,
								t_expansion_context *context);
char						*get_variable_value(const char *var_name,
								t_env *env, int exit_status);

/* ---------- 9. MANEJO DE RUTAS Y PATHS ---------- */
char						*get_path_variable(t_env *env);
char						*search_paths(char **paths, char *cmd);
char						*check_command_in_path(const char *base_path,
								const char *cmd);
char						**handle_empty_path(char *cmd, char *path_var);
char						*handle_absolute_or_relative_path(char *cmd);

/* ---------- 10. COMANDOS Y PIPES ---------- */
t_cmd						*init_cmd(void);
void						handle_pipe_or_separator(t_cmd **current,
								char **tokens, int i);
void						expand_cmd_list(t_cmd *cmd_list, t_env *env,
								int exit_status);
void						add_command_or_argument(t_cmd *current,
								char *token);
void						handle_redirection_tokens(t_cmd *current,
								char **tokens, int *i);
void						free_tokens(char **tokens);
void						process_command(t_cmd *cmd, t_pipe_data *pipe_data);

/* ---------- 11. SEÑALES Y PROCESAMIENTO DE INPUT ---------- */
void						disable_echoctl(void);
void						signal_handler(int sig);
void						process_input(t_data *data);

/* ---------- 12. MANEJO DE DIRECTORIO Y
ACTUALIZACIÓN DE VARIABLES ---------- */
int							handle_cwd_fail(t_data *data);
void						update_var(t_data *data);

#endif
