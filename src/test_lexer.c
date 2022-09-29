#include "lexer/lexer.h"
#include "lexer/tokens.h"
#include <stdio.h>

int main()
{

  Token* tokens = get_tokens("3 + 2 + 4.2 * 221 / 2 21.24 0.22 \\");
  for(register short i =0; i < token_len(); i++)
  {
    if (tokens[i].Type == ILLIGALCHAR)
    {
        fprintf(stderr,"Error: Illigal Char\n");
    }

    printf("Token number: %d\nToken type: %d\nToken value: %Lg\n\n", i, tokens[i].Type, tokens[i].Value);
  }
  free(tokens);
  return 0;
}