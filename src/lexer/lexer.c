#include "lexer.h"
#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

static void init_lexer(char * input);
static void next_char();
static void append_token(Token src);
static void append_char(char** dest, char source);
static Token get_num();

static char current_char;
static char * input_str;
static size_t current_char_location; // The array position that the current char can be found.
static Token* tokens; // Array of tokens to return
static size_t tokens_len = 0; // Length of token array
static const char *WHITESPACE = " \n\t"; // ignored chars
static const char *DIGITS = "0123456789"; // Accepted Digits


static void init_lexer(char * input)
{
    // Setup input_str
    input_str = calloc(strlen(input) + 1 , sizeof(char));
    if (input_str == NULL)
    {
        perror("calloc");
        exit(EXIT_FAILURE);        
    }
    strcpy(input_str, input);
  
  // Move to first char
    current_char_location = 0;
    current_char = input_str[current_char_location];

}

static void next_char()
{
    if (current_char == '\0')
    {
        return;
    }

  // Move to next char in input_str
    current_char_location++;

  // Store this in current_char
    current_char = input_str[current_char_location];
}

static void append_token(Token src)
{
    if (tokens_len == 0)
    {
        // Allocate tokens array and increment tokens_len. Add the new token to the array.
        tokens_len++;
        tokens = calloc(tokens_len,sizeof(Token));
        tokens[(tokens_len-1)] = src;
        return;
    }
      
    // Increment tokens_len, reallocate tokens array with new length. Add the new token to the array.
    tokens_len++;
    tokens = realloc(tokens, tokens_len * sizeof(Token));
    tokens[(tokens_len-1)] = src;
}

static void append_char(char** dest, char source)
{   char *buffer = malloc((strlen(*dest) +1) * sizeof(char));
    sprintf(buffer, "%s%c", *dest, source);
    free(*dest);
    *dest = buffer;
    return;
    /* size_t len = strlen(sdest);
    sdest = realloc(sdest, (len +1)* sizeof(char));
    if (sdest == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    printf("%c %c\t",*dest[len], source);
    *dest[len] = source;
    printf("%s\n",*dest);
    strcpy(dest, sdest) */
}  

static Token get_num()
{
    Token buffer;
    unsigned short decimal_count = 0;
    unsigned short iterations = 0;
    char *number_string = calloc(1, sizeof(char));

    // Loop while current_char isn't '\0' and current_char is a number or decimal point.
    // For every decimal, increment decimal_count. if decimal_count is over one, break from loop
    // Add every number/decimal to a string as the program loops, at the end convert this string to a float with atof()
    
    while(current_char != '\0' && (strstr(DIGITS,&current_char) != NULL || current_char == '.') && decimal_count < 2)
    {
        if( current_char == '.' )
        {
            decimal_count++;
        }

        if (iterations < 1)
        {
            number_string[0] = current_char;
        }
        else
        {
            append_char(&number_string, current_char);
        }

        next_char();
        iterations+=1;
    }
    
    /* if (number_string[0] == '.')
    {
        append_char(&number_string,'0');
    } */

    buffer = (Token) {
        .Type = NUM,
        .Value = atof(number_string),
    };

    free(number_string);
    return buffer;
}

Token * get_tokens(char* input)
{

    init_lexer(input);
    // TODO: Loop while current_char isn't '\0'
    //      Within this loop:
    //          check for whitespace, if found move to next char.
    //          check for digits, if found run get_num function, append the result to the tokens array, move to next char.
    //          check for for the operators (+ - * /) and append a token to the tokens array, move to next char.
    //          check for parenthesis and append tokens to token array, move to next char.

    while(current_char != '\0')
    {
        if (strstr(WHITESPACE,&current_char) != NULL)
        {
            next_char();
            continue;
        }
        if (current_char == '.' || strstr(DIGITS,&current_char) != NULL)
        {
            append_token(get_num());
            continue;
        }

        switch (current_char) {
            case '+':
                append_token((Token) {
                    .Type = ADD,
                    .Value = 0,
                });
                next_char();
                break;
            case '-':
                append_token((Token) {
                    .Type = SUB,
                    .Value = 0,
                });
                next_char();
                break;
            case '*':
                append_token((Token) {
                    .Type = MUL,
                    .Value = 0,
                });
                next_char();
                break;
            case '/':
                append_token((Token) {
                    .Type = DIV,
                    .Value = 0,
                });
                next_char();
                break;
            case '(':
                append_token((Token) {
                    .Type = LPAREN,
                    .Value = 0,
                });
                next_char();
                break;
            case ')':
                append_token((Token) {
                    .Type = RPAREN,
                    .Value = 0,
                });
                next_char();
                break;
            
            
            default:
                append_token((Token) {
                    .Type = ILLIGALCHAR,
                    .Value = 0,
                });
                next_char();
                break;
        }
    }
    free(input_str);
    return tokens;
}

size_t token_len()
{
    return tokens_len;
}