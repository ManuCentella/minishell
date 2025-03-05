/******************************************************************************
 * expansion_utils.c
 * 
 * Funciones auxiliares para la expansión de variables:
 *  - append_char: Agrega un solo carácter a una string.
 *  - get_variable_value: Obtiene el valor de una variable de entorno.
 *  - expand_dollar: Maneja la expansión de variables del entorno.
 *  - expand_question_mark: Maneja la expansión de $?.
 ******************************************************************************/

 #include "minishell.h"

 
 /* ************************************************************************** */
 /*        append_char: agrega un solo carácter a la cadena destino            */
 /* ************************************************************************** */
 
 void append_char(char **expanded, char c, int *i)
 {
     char tmp[2];
 
     tmp[0] = c;
     tmp[1] = '\0';
 
     printf("[DEBUG] append_char ejecutado. Copiando carácter: '%c' en posición %d\n", c, *i);
 
     *expanded = ft_strjoin_free(*expanded, tmp, 1);
     (*i)++;
 
     printf("[DEBUG] Estado actual de expanded: %s\n", *expanded);
 }
 
 
 /* ************************************************************************** */
 /*    get_variable_value: busca el valor de una variable en el entorno        */
 /* ************************************************************************** */
 
 char *get_variable_value(const char *var_name, t_env *env, int exit_status)
 {
     t_env *env_var;
     char  *value;
 
     if (ft_strcmp(var_name, "?") == 0)
         return ft_itoa(exit_status); 
     env_var = get_env_var(env, var_name);
     if (env_var)
         value = ft_strdup(env_var->value);
     else
         value = ft_strdup(""); 
     return value;
 }
 
 /* ************************************************************************** */
 /*      expand_question_mark: Maneja el caso especial $?                      */
 /* ************************************************************************** */
 
 void expand_question_mark(char **expanded, int *i, int exit_status)
 {
     char *value = get_variable_value("?", NULL, exit_status);
     *expanded = ft_strjoin_free(*expanded, value, 3);
     (*i)++;
 }
 
 /* ************************************************************************** */
 /*  expand_dollar: Maneja expansión de variables normales y $?                */
 /* ************************************************************************** */
 
 void expand_dollar(char **expanded, char *arg, int *i, t_env *env, int exit_status)
{
    (*i)++; // Saltamos el '$'

    printf("[DEBUG] expand_dollar ejecutado. Procesando arg[%d]: %s\n", *i, &arg[*i]);

    /* Caso especial: '$?' para código de salida */
    if (arg[*i] == '?')
    {
        expand_question_mark(expanded, i, exit_status);
        return;
    }

    /* Si `$` es seguido por un número, lo copiamos entero como texto */
    if (ft_isdigit(arg[*i]))
    {
        printf("[DEBUG] '$' seguido de número, copiando todo como texto\n");
        append_char(expanded, '$', i);  

        while (ft_isdigit(arg[*i]))  // Copiar TODOS los dígitos después del `$`
        {
            printf("[DEBUG] Intentando copiar número: %c en posición %d\n", arg[*i], *i);
            append_char(expanded, arg[*i], i);
        }

        printf("[DEBUG] Estado final de expanded después de copiar número: %s\n", *expanded);
        return;
    }

    /* Expansión de variables */
    int start = *i;
    while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
        (*i)++;

    if (*i > start) // Expandimos solo si hay un nombre de variable válido
    {
        char *var_name = ft_strndup(&arg[start], *i - start);
        printf("[DEBUG] Variable detectada: %s\n", var_name);

        char *value = get_variable_value(var_name, env, exit_status);
        printf("[DEBUG] Valor expandido: %s\n", value);

        free(var_name);

        // 🔥 **Corrección: evitar doble barra "//" al concatenar**
        if (ft_strlen(*expanded) > 0 && (*expanded)[ft_strlen(*expanded) - 1] == '/' && value[0] == '/')
        {
            printf("[DEBUG] Eliminando '/' extra en expansión de variable\n");
            *expanded = ft_strjoin_free(*expanded, value + 1, 3); // Saltar el primer '/'
        }
        else
            *expanded = ft_strjoin_free(*expanded, value, 3); // Concatenación normal
    }
    else
    {
        printf("[DEBUG] '$' sin variable. Agregando '$' literal.\n");
        append_char(expanded, '$', i);
    }
}


