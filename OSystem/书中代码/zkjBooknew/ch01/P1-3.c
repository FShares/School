#include "ch01.h"

char *get_current_dir()
{
    char *buffer;
    char *value;
    int size = 0;
    /*ȷ����ǰ����Ŀ¼·��������󳤶���size,��PATH_MAX ��ȷ��ʱ��sizeΪ-1*/
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
    if (size > 0){ /* PATH_MAX�ж���,���Ա�֤����Ŀռ����Դ��·����*/
        buffer = (char *)malloc(size+1);
        value = getcwd(buffer, size);
    }else{  /* PATH_MAXû�ж���,������̽�Եط����㹻�Ŀռ������·����*/
        size = _POSIX_PATH_MAX;
        buffer = (char *)malloc(size);
        while (1) {
            value = getcwd(buffer, size);
            if (value == 0 && errno ==ERANGE){ /* buffer̫С�������������Ŀռ� */
               size *= 2;
               free (buffer);
               buffer = (char *) malloc (size);
            }
        } 
    }
    return buffer;
}
