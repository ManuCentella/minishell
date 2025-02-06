#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	//----------------------------------------------------------------
	// 1. Inicializar la estructura t_data con las variables de entorno
	//----------------------------------------------------------------
	t_data data;
	data.env = NULL;
	data.cwd = getcwd(NULL, 0);

	for (int i = 0; envp[i]; i++)
	{
		t_env *new_env = malloc(sizeof(t_env));
		char *equal_sign = strchr(envp[i], '=');
		new_env->variable = strndup(envp[i], equal_sign - envp[i]);
		new_env->value = strdup(equal_sign + 1);
		new_env->next = data.env;
		data.env = new_env;
	}

	//----------------------------------------------------------------
	// 2. Pruebas de redirecciones
	//----------------------------------------------------------------

	//-----------------------------------------------------
	// TEST 1: echo "Hola minishell!" > output.txt
	//-----------------------------------------------------
	printf("\n--- TEST 1: echo \"Hola minishell!\" > output.txt ---\n");
	t_cmd test1 = {
		.cmd = "echo",
		.args = (char *[]){"echo", "Hola minishell!", NULL},
		.builtin = 0,            // 0: tratado como comando externo
		.infile = NULL,
		.outfile = "output.txt", // Redirige stdout a "output.txt"
		.appendfile = NULL,
		.errfile = NULL,
		.next = NULL
	};
	executor(&test1, &data);
	printf("Revisa el contenido de 'output.txt' (debería contener \"Hola minishell!\").\n");

	//-----------------------------------------------------
	// TEST 2: echo "Añadiendo línea..." >> append.txt
	//-----------------------------------------------------
	printf("\n--- TEST 2: echo \"Añadiendo línea...\" >> append.txt ---\n");
	t_cmd test2 = {
		.cmd = "echo",
		.args = (char *[]){"echo", "Añadiendo línea...", NULL},
		.builtin = 0,
		.infile = NULL,
		.outfile = NULL,
		.appendfile = "append.txt", // Modo append
		.errfile = NULL,
		.next = NULL
	};
	executor(&test2, &data);
	printf("Revisa 'append.txt' (se habrá añadido \"Añadiendo línea...\").\n");

	//-----------------------------------------------------
	// TEST 3: cat < input.txt
	//-----------------------------------------------------
	printf("\n--- TEST 3: cat < input.txt ---\n");
	t_cmd test3 = {
		.cmd = "cat",
		.args = (char *[]){"cat", NULL},
		.builtin = 0,
		.infile = "input.txt",   // Redirige entrada desde "input.txt"
		.outfile = NULL,
		.appendfile = NULL,
		.errfile = NULL,
		.next = NULL
	};
	executor(&test3, &data);
	printf("Se ha mostrado por pantalla el contenido de 'input.txt' (redirección <).\n");

	//-----------------------------------------------------
	// TEST 4: cat < input.txt > output_cat.txt
	//-----------------------------------------------------
	printf("\n--- TEST 4: cat < input.txt > output_cat.txt ---\n");
	t_cmd test4 = {
		.cmd = "cat",
		.args = (char *[]){"cat", NULL},
		.builtin = 0,
		.infile = "input.txt",
		.outfile = "output_cat.txt", // Guardo salida en "output_cat.txt"
		.appendfile = NULL,
		.errfile = NULL,
		.next = NULL
	};
	executor(&test4, &data);
	printf("Revisa 'output_cat.txt' para ver si contiene lo mismo que 'input.txt'.\n");

	//-----------------------------------------------------
	// TEST 5: ls -l > ls_output.txt 2> ls_error.txt
	//-----------------------------------------------------
	printf("\n--- TEST 5: ls -l > ls_output.txt 2> ls_error.txt ---\n");
	t_cmd test5 = {
		.cmd = "ls",
		.args = (char *[]){"ls", "-l", NULL},
		.builtin = 0,
		.infile = NULL,
		.outfile = "ls_output.txt", // Redirige stdout
		.appendfile = NULL,
		.errfile = "ls_error.txt",  // Redirige stderr
		.next = NULL
	};
	executor(&test5, &data);
	printf("Revisa 'ls_output.txt' y 'ls_error.txt' (si no hay errores, ls_error.txt estará vacío).\n");

	//-----------------------------------------------------
	// TEST 6 (ERROR): ls -l /no_such_dir > ls_output_err.txt 2> ls_error_err.txt
	// Este forzará un error, para verificar la redirección de stderr.
	//-----------------------------------------------------
	printf("\n--- TEST 6 (ERROR): ls -l /no_such_dir > ls_output_err.txt 2> ls_error_err.txt ---\n");
	t_cmd test6 = {
		.cmd = "ls",
		.args = (char *[]){"ls", "-l", "/no_such_dir", NULL},
		.builtin = 0,
		.infile = NULL,
		.outfile = "ls_output_err.txt",  // Redirige stdout
		.appendfile = NULL,
		.errfile = "ls_error_err.txt",   // Redirige stderr
		.next = NULL
	};
	executor(&test6, &data);
	printf("Revisa 'ls_output_err.txt' (debería estar vacío o no mostrar el error) y 'ls_error_err.txt' (debe contener el error).\n");

	//-----------------------------------------------------
	// TEST 7: cat < input.txt >> append.txt
	//-----------------------------------------------------
	printf("\n--- TEST 7: cat < input.txt >> append.txt ---\n");
	t_cmd test7 = {
		.cmd = "cat",
		.args = (char *[]){"cat", NULL},
		.builtin = 0,
		.infile = "input.txt",
		.outfile = NULL,
		.appendfile = "append.txt", // Añade al final de append.txt
		.errfile = NULL,
		.next = NULL
	};
	executor(&test7, &data);
	printf("Se ha añadido el contenido de 'input.txt' al final de 'append.txt'.\n");

	//----------------------------------------------------------------
	// 3. Liberar la memoria de data.env y data.cwd
	//----------------------------------------------------------------
	t_env *tmp;
	while (data.env)
	{
		tmp = data.env;
		data.env = data.env->next;
		free(tmp->variable);
		free(tmp->value);
		free(tmp);
	}
	free(data.cwd);

	return 0;
}
