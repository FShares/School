#include "ch11.h"
void write_data (FILE * stream)
{
    int i;
    for (i = 0; i<50; i++){        /* 输出50个整数*/
       fprintf (stream, "line %2d\n", i);
       if (ferror (stream)) 
           err_exit("Output to stream failed.\n");
    }
}
int main (void)
{
    FILE *output;
    /* 建立执行more的进程分页显示输入,并创建通向它的输入管道 */
    output = popen ("more -10", "w");
    if (!output) 
        err_exit("Could not run more.\n"); 
    write_data (output);
    /* 等待popen创建的进程终止并关闭与它相连的流 */
    pclose (output);
    return EXIT_SUCCESS;
}
