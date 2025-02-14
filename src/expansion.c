#include "minishell.h"

/**
 * 🔹 get_variable_value - Obtiene el valor de una variable de entorno.
 * 🔹 Si la variable es `$?`, devuelve el código de salida convertido a string.
 */
static char	*get_variable_value(char *var_name, t_env *env, int exit_status)
{
	t_env	*env_var;
	char	*value;

	if (ft_strcmp(var_name, "?") == 0) // Manejo especial de `$?`
		return (ft_itoa(exit_status));
	env_var = get_env_var(env, var_name); // Buscar la variable en el entorno
	if (env_var)
		value = ft_strdup(env_var->value);
	else
		value = ft_strdup(""); // Si no existe, devuelve una cadena vacía
	return (value);
}

/**
 * 🔹 append_variable_value - Expande y concatena el valor de una variable.
 */
static void	append_variable_value(char **expanded, char *var_name, t_env *env, int exit_status)
{
	char	*var_value;

	var_value = get_variable_value(var_name, env, exit_status);
	*expanded = ft_strjoin_free(*expanded, var_value, 3); // Concatena y libera memoria
}

/**
 * 🔹 append_char - Agrega un solo carácter al string expandido.
 */
static void	append_char(char **expanded, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_free(*expanded, tmp, 1);
}

/**
 * 🔹 expand_variable - Expande `$VARIABLES` dentro de un string.
 * 🔹 Devuelve una nueva cadena con los valores reemplazados.
 */
char *expand_variable(char *arg, t_env *env, int exit_status)
{
    // Si el token empieza con '\x01', no se expanden variables y se retorna el token sin el marcador.
    if (arg[0] == '\x01')
        return (ft_strdup(arg + 1));

    char *expanded;
    char *var_name;
    int i, start;

    i = 0;
    expanded = ft_strdup("");
    if (!expanded)
        return (NULL);
    while (arg[i])
    {
        if (arg[i] == '$' && arg[i + 1]) // Si encontramos '$'
        {
            start = ++i;
            while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
                i++;
            var_name = ft_strndup(&arg[start], i - start);
            append_variable_value(&expanded, var_name, env, exit_status);
            free(var_name);
        }
        else
            append_char(&expanded, arg[i++]);
    }
    return (expanded);
}

