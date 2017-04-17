#include <stdio.h>
//#include <ctype.h>
void skip_whitespace (FILE *stream)
{
    int c;
    do
      c = getc (stream);  /* 无需检查EOF，因为它不是空白字符且ungetc忽略EOF. */
    while (isspace (c));
    ungetc (c, stream);
}
