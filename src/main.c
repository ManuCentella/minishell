/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghdad <szaghdad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:08:21 by  mcentell         #+#    #+#             */
/*   Updated: 2025/03/10 22:30:01 by szaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = init_env(envp);
	data.cwd = getcwd(NULL, 0);
	data.exit_status = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();
	process_input(&data);
	free(data.cwd);
	free_env_list(data.env);
	return (0);
}
