#include "minishell.h"

/**
 * 🔹 init_env - Inicializa la lista de variables de entorno a partir de `envp`.
 */
t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;
	char	*equal_sign;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			char *name = ft_strndup(envp[i], equal_sign - envp[i]);
			char *value = ft_strdup(equal_sign + 1);
            set_env_var(&env_list, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	return (env_list);
}

/**
 * 🔹 get_env_var - Busca y retorna una variable de entorno desde la lista.
 */
t_env	*get_env_var(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->variable, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/**
 * 🔹 set_env_var - Agrega o modifica una variable de entorno en `env`.
 */
void set_env_var(t_env **env, const char *name, const char *value)
{
    t_env *var = get_env_var(*env, name);
    t_env *new_var;


    if (var) // Si ya existe, modificar su valor
    {
        free(var->value);
        var->value = ft_strdup(value ? value : "");
    }
    else // Si no existe, la creamos y la añadimos a la lista
    {
        new_var = malloc(sizeof(t_env));
        if (!new_var)
            return;

        new_var->variable = ft_strdup(name);
        new_var->value = ft_strdup(value ? value : "");
        new_var->next = *env;
        *env = new_var;
    }
}



/**
 * 🔹 is_valid_var_name - Verifica si el nombre de una variable de entorno es válido.
 */
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

/**
 * 🔹 print_env_vars - Imprime todas las variables de entorno exportadas.
 */
void	print_env_vars(t_env *env)
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


/**
 * 🔹 free_env_list - Libera toda la lista de variables de entorno.
 * 🔹 Recorre la lista y libera cada nodo.
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->variable);
		free(env->value);
		free(env);
		env = tmp;
	}
}
