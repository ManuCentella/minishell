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
 
 #include <stdio.h> // Para imprimir mensajes de depuración

 char *expand_variable(char *arg, t_env *env, int exit_status)
{
    char *expanded = ft_strdup("");
    int i = 0;

    printf("[DEBUG] expand_variable ejecutado con arg: %s\n", arg);

    // 🔹 Si el token contiene \x01, NO expandimos variables
    if (ft_strchr(arg, '\x01'))
    {
        printf("[DEBUG] Texto dentro de comillas simples, no expandimos: %s\n", arg);
        return ft_strdup(arg); // 🔥 Devolvemos el texto sin modificar
    }

    while (arg[i])
    {
        printf("[DEBUG] Iterando en expand_variable: arg[%d] = %c\n", i, arg[i]);

        if (arg[i] == '\x02')  // "$" literal (proviene de "\$")
        {
            printf("[DEBUG] Encontrado \\x02, agregando '$'\n");
            append_char(&expanded, '$', &i);
        }
        else if (arg[i] == '$') // Expansión de variables
        {
            printf("[DEBUG] Encontrado '$' en arg[%d], llamando a expand_dollar()\n", i);
            expand_dollar(&expanded, arg, &i, env, exit_status);
        }
        else
        {
            printf("[DEBUG] Copiando carácter normal: '%c' desde arg[%d]\n", arg[i], i);
            append_char(&expanded, arg[i], &i);
        }

        printf("[DEBUG] Estado actual de expanded: %s\n", expanded);
    }

    printf("[DEBUG] Resultado final expandido: %s\n", expanded);
    return expanded;
}

 