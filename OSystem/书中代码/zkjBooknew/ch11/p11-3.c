#include "ch11.h"
void write_data (FILE * stream)
{
    int i;
    for (i = 0; i<50; i++){        /* ���50������*/
       fprintf (stream, "line %2d\n", i);
       if (ferror (stream)) 
           err_exit("Output to stream failed.\n");
    }
}
int main (void)
{
    FILE *output;
    /* ����ִ��more�Ľ��̷�ҳ��ʾ����,������ͨ����������ܵ� */
    output = popen ("more -10", "w");
    if (!output) 
        err_exit("Could not run more.\n"); 
    write_data (output);
    /* �ȴ�popen�����Ľ�����ֹ���ر������������� */
    pclose (output);
    return EXIT_SUCCESS;
}
