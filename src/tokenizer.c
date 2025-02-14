#include "minishell.h"
#include "minishell.h"

/**
 * 🔹 add_token - Añade un nuevo token a la lista de tokens.
 * Amplía el array de tokens (t->tokens) y agrega un nuevo token.
 */
void add_token(t_tokenizer *t, char *start, int length)
{
    char **new_tokens;

    /* Reservamos memoria para un nuevo array de tokens (+2: nuevo token + NULL) */
    new_tokens = allocate_new_tokens(t);
    if (!new_tokens)
        return;
    
    /* Copiamos los tokens antiguos al nuevo array */
    copy_existing_tokens(new_tokens, t->tokens, t->token_count);
    
    /* Copiamos el nuevo token en la última posición */
    new_tokens[t->token_count] = strndup(start, length);
    if (!new_tokens[t->token_count])
    {
        perror("strndup");
        free(new_tokens);
        return;
    }
    
    /* Terminamos la lista de tokens con NULL */
    new_tokens[t->token_count + 1] = NULL;
    
    /* Liberamos la memoria del array viejo y asignamos el nuevo */
    free(t->tokens);
    t->tokens = new_tokens;
    t->token_count++; /* Aumentamos el contador de tokens */
}

/**
 * 🔹 handle_quotes - Maneja las comillas simples ('') y dobles ("").
 * Extrae el contenido dentro de las comillas como un solo token, eliminando las comillas de apertura y cierre.
 * En comillas dobles, si se encuentra un escape (\") se trata como comilla literal.
 */
void handle_quotes(t_tokenizer *t, char quote)
{
    int start, j = 0;
    char *buffer;
    int max_len;

    /* Saltamos la comilla de apertura */
    t->i++;
    start = t->i;
    max_len = t->len - start;
    buffer = malloc(max_len + 1);
    if (!buffer)
        return;
    
    /* Procesamos el contenido dentro de las comillas */
    while (t->i < t->len && t->input[t->i] != quote)
    {
        /* En comillas dobles, si encontramos un escape de comilla, lo procesamos */
        if (quote == '\"' && t->input[t->i] == '\\' && t->i + 1 < t->len && t->input[t->i+1] == '\"')
        {
            t->i++; /* Saltamos la barra invertida */
            buffer[j++] = t->input[t->i++];
        }
        else
        {
            buffer[j++] = t->input[t->i++];
        }
    }
    
    if (t->i >= t->len)
    {
        fprintf(stderr, "Error: comillas sin cerrar en el token\n");
        free(buffer);
        return;
    }
    
    buffer[j] = '\0';
    t->i++; /* Saltamos la comilla de cierre */
    
    /* Si la comilla era simple, marcamos el token para evitar la expansión de variables */
    if (quote == '\'')
    {
        int new_len = j + 1; /* 1 para el marcador */
        char *marked = malloc(new_len + 1);
        if (!marked)
        {
            free(buffer);
            return;
        }
        marked[0] = '\x01';          /* Marcador especial para no expandir variables */  
        strcpy(marked + 1, buffer);  /* Copiamos el contenido sin comillas */
        add_token(t, marked, new_len);
        free(marked);
    }
    else
    {
        /* Para comillas dobles, agregamos el token sin comillas */
        add_token(t, buffer, j);
    }
    free(buffer);
}




/**
 * 🔹 handle_metacharacters - Detecta y maneja metacaracteres especiales.
 * Detecta '<', '>', '>>', '<<' y los guarda como tokens independientes.
 */
void handle_metacharacters(t_tokenizer *t)
{
    int start;

    start = t->i++; /* Guardamos la posición inicial del token y avanzamos */

    /* Si encontramos << o >>, avanzamos una posición extra */
    if ((t->input[start] == '<' && t->input[t->i] == '<')
        || (t->input[start] == '>' && t->input[t->i] == '>'))
        t->i++;
    
    /* Añadimos el metacaracter (o metacaracter doble) como un token separado */
    add_token(t, &t->input[start], t->i - start);
}

/**
 * 🔹 process_next_token - Identifica y clasifica el siguiente token de la entrada.
 * Dependiendo del tipo de caracter, llama a la función correspondiente.
 */
void process_next_token(t_tokenizer *t)
{
    int start;
    /* Si encontramos comillas, procesamos el texto entre ellas como un solo token */
    if (t->input[t->i] == '\"' || t->input[t->i] == '\'')
        handle_quotes(t, t->input[t->i]);
    /* Si encontramos un metacaracter especial (<, >, |) */
    else if (ft_is_metachar(t->input[t->i]))
        handle_metacharacters(t);
    else /* Si es un argumento normal (texto), lo procesamos como un token normal */
    {
        start = t->i; /* Guardamos la posición de inicio */
        while (t->i < t->len && !ft_isspace(t->input[t->i])
            && !ft_is_metachar(t->input[t->i]))
            t->i++; /* Avanzamos hasta encontrar un espacio o un metacaracter */
        add_token(t, &t->input[start], t->i - start);
    }
}

/**
 * 🔹 tokenize_input - Convierte la entrada del usuario en una lista de tokens.
 * Divide la cadena en tokens separados por espacios, comillas y metacaracteres.
 */
char **tokenize_input(char *input)
{
    t_tokenizer t;

    /* Inicializamos la estructura del tokenizador */
    t.input = input;
    t.i = 0;
    t.len = (int)strlen(input);
    t.tokens = NULL;
    t.token_count = 0;
    
    /* Recorremos toda la entrada */
    while (t.i < t.len)
    {
        skip_whitespace(&t); /* Saltamos espacios en blanco */
        if (t.i >= t.len)
            break;
        process_next_token(&t); /* Procesamos el siguiente token */
    }
    return (t.tokens); /* Retornamos la lista de tokens generada */
}
