/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcentell <mcentell@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:08:21 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/24 16:16:00 by mcentell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = init_env(envp);
	data.cwd = getcwd(NULL, 0);
	data.exit_status = 0;
	setup_signals();
	process_input(&data);
	free(data.cwd);
	free_env_list(data.env);
	rl_clear_history();
	return (0);
}
