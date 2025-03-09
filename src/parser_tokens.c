/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:15:54 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/09 21:06:37 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 🔹 init_cmd - Crea e inicializa una nueva estructura t_cmd.
 * 🔹 Reserva memoria y establece valores por defecto.
 * 🔹 Retorna un puntero a la estructura creada.
 */
// Reservamos memoria para un nuevo comando
// Si malloc falla, imprimimos error
// Inicializamos todos los valores del comando en NULL o valores vacíos
static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		return (NULL);
	}
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->builtin = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->appendfile = NULL;
	cmd->errfile = NULL;
	cmd->heredoc = NULL;
	cmd->heredoc_content = NULL;
	cmd->heredoc_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

/**
 * 🔹 add_arg - Agrega un argumento a la lista de argumentos del comando.
 * 🔹 Amplía el array de argumentos (`cmd->args`) y añade un nuevo argumento.
 */
// ✅ Recorremos la lista de argumentos existentes
// ✅ Si malloc falla, imprimimos error
// ✅ Copiamos argumentos existentes
// ✅ Agregamos el nuevo argumento
// ✅ Terminamos la lista con NULL
// ✅ Liberamos la lista anterior
static void	add_arg(t_cmd *cmd, char *token)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
	{
		perror("malloc");
		return ;
	}
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = strdup(token);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

/**
 * 🔹 handle_redirection - Identifica redirecciones (<, >, >>, <<) en un comando.
 * 🔹 Guarda el archivo de entrada/salida en la estructura t_cmd.
 */
// Entrada (archivo)
// Salida (sobreescribe)
// Salida (append)
// Heredoc
static void	handle_redirection(t_cmd *cmd, char **tokens, int *i)
{
	if (strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		cmd->infile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
		cmd->outfile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
		cmd->appendfile = strdup(tokens[++(*i)]);
	else if (strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
		cmd->heredoc = strdup(tokens[++(*i)]);
}

/**
 * 🔹 handle_pipe_or_separator - Maneja la lógica de tuberías (|)
 * y punto y coma (;)
 */
// ✅ Marcamos que este comando es parte de una tubería
static void	handle_pipe_or_separator(t_cmd **current, char **tokens, int i)
{
	if (!(*current)->cmd || strlen((*current)->cmd) == 0)
	{
		fprintf(stderr, "minishell: error de sintaxis token `%s`\n", tokens[i]);
		return ;
	}
	if (strcmp(tokens[i], "|") == 0)
		(*current)->is_piped = 1;
	(*current)->next = init_cmd();
	*current = (*current)->next;
}

/**
 * 🔹 handle_redirection_tokens - Maneja redirecciones (<, >, >>, <<).
 */
static void	handle_redirection_tokens(t_cmd *current, char **tokens, int *i)
{
	if (!current->cmd || strlen(current->cmd) == 0)
	{
		fprintf(stderr, "minishell: error de sintaxis cerca del token `%s`\n",
			tokens[*i]);
		return ;
	}
	handle_redirection(current, tokens, i);
}

/**
 * 🔹 add_command_or_argument - Agrega un comando o argumento
 * a la estructura t_cmd.
 */
static void	add_command_or_argument(t_cmd *current, char *token)
{
	if (!current->cmd)
		current->cmd = strdup(token);
	add_arg(current, token);
}

/**
 * 🔹 parse_token_logic - Procesa un token y lo organiza en la lista de comandos.
 */
/* Ignorar tokens vacíos */
/* Si no hay un comando actual, lo creamos */
/* Si el token es un PIPE (`|`) o punto y coma (`;`), manejamos la separación */
/* Si el token es una redirección (<, >, >>, <<), lo manejamos */
/* Si es un comando o argumento normal, lo añadimos */
void	parse_token_logic(t_cmd **current, t_cmd **cmd_list,
	char **tokens, int *i)
{
	if (!tokens[*i] || tokens[*i][0] == '\0')
		return ;
	if (!*current)
	{
		*current = init_cmd();
		*cmd_list = *current;
	}
	if (strcmp(tokens[*i], "|") == 0 || strcmp(tokens[*i], ";") == 0)
		handle_pipe_or_separator(current, tokens, *i);
	else if (strcmp(tokens[*i], "<") == 0 || strcmp(tokens[*i], ">") == 0
		|| strcmp(tokens[*i], ">>") == 0 || strcmp(tokens[*i], "<<") == 0)
		handle_redirection_tokens(*current, tokens, i);
	else
		add_command_or_argument(*current, tokens[*i]);
}

/**
 * 🔹 expand_cmd - Expande variables en el nombre del comando.
 */
static void	expand_cmd(t_cmd *cmd, t_env *env, int exit_status)
{
	char	*expanded;

	if (cmd->cmd && strchr(cmd->cmd, '$'))
	{
		expanded = expand_variable(cmd->cmd, env, exit_status);
		free(cmd->cmd);
		cmd->cmd = expanded;
	}
}

/**
 * 🔹 expand_args - Expande variables en los argumentos de un comando.
 */
static void	expand_args(t_cmd *cmd, t_env *env, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (strchr(cmd->args[i], '$'))
		{
			expanded = expand_variable(cmd->args[i], env, exit_status);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

/**
 * 🔹 expand_cmd_list - Recorre la lista de comandos y
 * expande variables en cada nodo.
 */
static void	expand_cmd_list(t_cmd *cmd_list, t_env *env, int exit_status)
{
	while (cmd_list)
	{
		expand_cmd(cmd_list, env, exit_status);
		expand_args(cmd_list, env, exit_status);
		cmd_list = cmd_list->next;
	}
}

/**
 * 🔹 parse_tokens - Convierte tokens en una lista de `t_cmd` y expande variables.
 */
/**
 * 🔹 parse_tokens - Convierte tokens en una lista de t_cmd y expande variables.
 */
t_cmd	*parse_tokens(char **tokens, t_env *env, int exit_status)
{
	int		i;
	int		j;
	t_cmd	*cmd_list;
	t_cmd	*current;

	if (!tokens)
		return (NULL);
	if (tokens[0] && strcmp(tokens[0], "minishell") == 0)
	{
		j = 0;
		while (tokens[j])
		{
			tokens[j] = tokens[j + 1];
			j++;
		}
	}
	cmd_list = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		parse_token_logic(&current, &cmd_list, tokens, &i);
		i++;
	}
	expand_cmd_list(cmd_list, env, exit_status);
	return (cmd_list);
}
