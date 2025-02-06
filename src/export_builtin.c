#include "minishell.h"

// ✅ Agrega o modifica una variable en `data->env`
void	set_env_var(t_data *data, const char *name, const char *value)
{
	t_env	*var;
	t_env	*new_var;

	var = get_env_var(data->env, name);
	if (var) // Si ya existe, modificar su valor
	{
		free(var->value);
		var->value = (value) ? ft_strdup(value) : NULL;
			// Si es NULL,eliminar el valor
	}
	else // Si no existe, crearla
	{
		new_var = malloc(sizeof(t_env));
		new_var->variable = ft_strdup(name);
		new_var->value = (value) ? ft_strdup(value) : NULL;
		// Manejo de `export VAR`
		new_var->next = data->env;
		data->env = new_var;
	}
}

int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_env_vars(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->variable, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

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
			has_error = (print_msg(data, "export: not a valid identifier", -1),
					1);
		else
			set_env_var(data, arg_copy, equal + 1);
	}
	else if (!is_valid_var_name(arg_copy))
		has_error = (print_msg(data, "export: not a valid identifier", -1), 1);
	else
		set_env_var(data, arg_copy, NULL);
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
