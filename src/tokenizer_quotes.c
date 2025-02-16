/******************************************************************************
 * tokenizer_quotes.c
 * - Maneja comillas simples y dobles
 * - handle_escaped_chars para \ dentro de comillas dobles
 ******************************************************************************/

 #include "minishell.h"
 
 /* (1) handle_escaped_chars: \" -> ", \\ -> \, \$ -> \x02 */
 void handle_escaped_chars(t_tokenizer *t, char *buffer, int *j)
 {
     char next = t->input[t->i + 1];
 
     if (next == '\"' || next == '\\')
     {
         buffer[(*j)++] = next;
         t->i += 2;
     }
     else if (next == '$')
     {
         buffer[(*j)++] = '\x02';
         t->i += 2;
     }
     else
     {
         buffer[(*j)++] = '\\';
         t->i++;
     }
 }
 
 /* (2) process_inner_single_quote: maneja ' dentro de comillas dobles */
 /*static char *process_inner_single_quote(t_tokenizer *t)
 {
     int start;
     int length;
     char *temp;
 
     t->i++;
     start = t->i;
     while (t->i < t->len && t->input[t->i] != '\'')
         t->i++;
     if (t->i >= t->len)
     {
         fprintf(stderr, "Error: comillas simples sin cerrar\n");
         return NULL;
     }
     length = t->i - start;
     temp = malloc(length + 2);
     if (!temp)
         return NULL;
     temp[0] = '\x01';
     memcpy(temp + 1, &t->input[start], length);
     temp[length + 1] = '\0';
     t->i++;
     return temp;
 }*/
 
 /* (3) handle_quotes: maneja comillas simples y dobles */
 void handle_quotes(t_tokenizer *t, char quote)
 {
     int j = 0;
     int size = t->len - t->i + 1;
     char *buffer = malloc(size);
 
     t->i++;
     if (!buffer)
         return;
     while (t->i < t->len && t->input[t->i] != quote)
     {
         if (quote == '\"' && t->input[t->i] == '\\')
             handle_escaped_chars(t, buffer, &j);
         else
             buffer[j++] = t->input[t->i++];
     }
     if (t->i >= t->len)
     {
         fprintf(stderr, "Error: comillas sin cerrar\n");
         free(buffer);
     }
     else
         t->i++;
     buffer[j] = '\0';
     if (quote == '\'')
         add_token(t, ft_strjoin("\x01", buffer), j + 1);
     else
         add_token(t, buffer, j);
     free(buffer);
 }

void add_token(t_tokenizer *t, char *start, int length)
{
    char **new_tokens;

    new_tokens = allocate_new_tokens(t);
    if (!new_tokens)
        return;
    copy_existing_tokens(new_tokens, t->tokens, t->token_count);

    new_tokens[t->token_count] = strndup(start, length);
    if (!new_tokens[t->token_count])
    {
        perror("strndup");
        free(new_tokens);
        return;
    }
    new_tokens[t->token_count + 1] = NULL;

    free(t->tokens);
    t->tokens = new_tokens;
    t->token_count++;
}
