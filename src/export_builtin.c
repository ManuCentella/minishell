#include "minishell.h"
static int	process_export_arg(t_data *data, char *arg)
{
	char	*equal;
	char	*arg_copy;
	int		has_error;

	has_error = 0;
	arg_copy = ft_strdup(arg);
	if (!arg_copy)
		return (print_msg(data, "export: malloc failed", -1), 1);
	equal = ft_strchr(arg_copy, '=');
	if (equal)
	{
		*equal = '\0';
		if (!is_valid_var_name(arg_copy))
			has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
		else
			set_env_var(&(data->env), arg_copy, equal + 1); // 🔥 Corrección aquí
	}
	else if (!is_valid_var_name(arg_copy))
		has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
	else
		set_env_var(&(data->env), arg_copy, NULL); // 🔥 Corrección aquí
	free(arg_copy);
	return (has_error);
}

int	export_builtin(t_data *data, t_cmd *cmd)
{
	int	i;
	int	has_error;

	i = 1;
	has_error = 0;
	if (!cmd->args[1])
		return (print_env_vars(data->env), 0);
	while (cmd->args[i])
		has_error |= process_export_arg(data, cmd->args[i++]);
	return (has_error);
}
