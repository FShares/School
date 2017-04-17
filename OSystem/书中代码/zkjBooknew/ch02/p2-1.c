#include "ch02.h"
int main(void)
{
    FILE *stream;
    char buf[80];
    printf("open and creat test_file\n");
    if ((stream = fopen("test_file","w")) == NULL )
        err_exit("open() failed");
    printf("write string to test_file\n");
    fputs("Hello world",stream);   /* Êä³ö×Ö·û´®ÖÁÖÕ¶Ë */
    if ((stream = freopen("test_file","r",stream)) == NULL )
        err_exit("open() failed");
    printf("read string from test_file\n");
    fgets(buf, sizeof(buf), stream);  /* ´ÓÖÕ¶Ë¶ÁÈëÒ»ĞĞ×Ö·û´® */
    printf("the string is \"%s\"\n", buf);
    fclose(stream);
}
