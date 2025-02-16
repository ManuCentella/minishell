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
     *expanded = ft_strjoin_free(*expanded, tmp, 1);
     (*i)++;
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
     (*i)++; /* Saltamos el '$' */
 
     /* Caso especial: '$?' */
     if (arg[*i] == '?')
         expand_question_mark(expanded, i, exit_status);
     else
     {
         /* Leer nombre de variable (letras, dígitos, '_') */
         int start = *i;
         while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
             (*i)++;
 
         if (*i > start) /* Expandimos solo si hay un nombre de variable */
         {
             char *var_name = ft_strndup(&arg[start], *i - start);
             char *value = get_variable_value(var_name, env, exit_status);
             free(var_name);
             *expanded = ft_strjoin_free(*expanded, value, 3);
         }
         else
         {
             /* Si no hay variable válida después de $, tratamos $ como literal */
             append_char(expanded, '$', i);
         }
     }
 }
 