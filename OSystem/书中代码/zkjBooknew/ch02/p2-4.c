#include <stdio.h>
//#include <ctype.h>
void skip_whitespace (FILE *stream)
{
    int c;
    do
      c = getc (stream);  /* ������EOF����Ϊ�����ǿհ��ַ���ungetc����EOF. */
    while (isspace (c));
    ungetc (c, stream);
}
