/******************************************************************************
 * expansion_main.c
 * 
 * Función principal que expande variables en los tokens:
 *  - Maneja \x01 (comillas simples) para no expandir.
 *  - Maneja \x02 (para que "\$" se convierta en '$' literal).
 *  - Expande variables del entorno con $VAR.
 *  - Expande $? con el código de salida.
 ******************************************************************************/

 #include "minishell.h"

 /* Prototipos de funciones auxiliares */
 void append_char(char **expanded, char c, int *i);
 void expand_dollar(char **expanded, char *arg, int *i, t_env *env, int exit_status);

 char *expand_variable(char *arg, t_env *env, int exit_status)
{
    char *expanded = ft_strdup("");
    int i = 0;

    // 🔹 No expandimos variables dentro de comillas simples
    if (ft_strchr(arg, '\x01'))
    {
        return ft_strdup(arg);
    }

    while (arg[i])
    {

        if (arg[i] == '\\' && arg[i + 1] == '$')  // 🔹 Si hay `\$`, lo tratamos como texto
        {
            append_char(&expanded, '$', &i);  // Copia `$` literal
            i++;  // Salta `$`
        }
        else if (arg[i] == '$') // 🔥 Expansión normal de variables
        {
            expand_dollar(&expanded, arg, &i, env, exit_status);
        }
        else
        {
            append_char(&expanded, arg[i], &i);
        }

    }

    return expanded;
}

 