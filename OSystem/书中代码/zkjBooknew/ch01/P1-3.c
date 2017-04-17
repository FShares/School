#include "ch01.h"

char *get_current_dir()
{
    char *buffer;
    char *value;
    int size = 0;
    /*确定当前工作目录路径名的最大长度于size,当PATH_MAX 不确定时，size为-1*/
#ifdef PATH_MAX
    size = PATH_MAX;
#else
    errno = 0;
    if ((size = pathconf("./",_PC_PATH_MAX)) < 0)
    if (errno != 0){
        printf("pathconf error for _PC_PATH_MAX\n");
        exit(-1);
    }
#endif
    if (size > 0){ /* PATH_MAX有定义,可以保证分配的空间足以存放路径名*/
        buffer = (char *)malloc(size+1);
        value = getcwd(buffer, size);
    }else{  /* PATH_MAX没有定义,必须试探性地分配足够的空间来存放路径名*/
        size = _POSIX_PATH_MAX;
        buffer = (char *)malloc(size);
        while (1) {
            value = getcwd(buffer, size);
            if (value == 0 && errno ==ERANGE){ /* buffer太小，重新申请更大的空间 */
               size *= 2;
               free (buffer);
               buffer = (char *) malloc (size);
            }
        } 
    }
    return buffer;
}
