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
 
 
 /* ************************************************************************** */
 /*     expand_variable: función principal de expansión, ahora más pequeña     */
 /* ************************************************************************** */
 
 char *expand_variable(char *arg, t_env *env, int exit_status)
 {
     char *expanded = ft_strdup("");
     int   i = 0;
 
     /* 1) Si el token empieza con \x01 => comillas simples => devolver sin expandir */
     if (arg[0] == '\x01')
         return ft_strdup(arg + 1);
     
     /* 2) Bucle principal que recorre el string */
     while (arg[i])
     {
         if (arg[i] == '\x02')  // "$" literal (proviene de "\$")
             append_char(&expanded, '$', &i);
         else if (arg[i] == '$') // Expansión de variables
             expand_dollar(&expanded, arg, &i, env, exit_status);
         else
             append_char(&expanded, arg[i], &i); // Copiar carácter normal
     }
     return expanded;
 }
 