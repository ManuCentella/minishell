/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:08:21 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/13 15:50:40 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_exit_status = 0;  // ✅ Definir la variable global

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = init_env(envp);
	data.cwd = getcwd(NULL, 0);
	data.exit_status = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	disable_echoctl();
	process_input(&data);
	free(data.cwd);
	free_env_list(data.env);
	return (0);
}
