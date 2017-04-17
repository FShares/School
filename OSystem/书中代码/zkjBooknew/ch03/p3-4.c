/* ��value��0������FD_CLOEXEC��־,��valueΪ0,����ñ�־���ɹ�����0��ʧ�ܷ���-1*/
#include "ch03.h"
int set_cloexec_flag (int desc, int value)
{
   int oldflags = fcntl (desc, F_GETFD, 0);
   if(oldflags < 0)    /* ������ǩʧ�ܣ����󷵻ء�*/
       return oldflags;
   /* ������Ҫ�ı�־. */
   if(value != 0)
       oldflags |= FD_CLOEXEC;
   else
      oldflags &= ~FD_CLOEXEC;
   return fcntl (desc, F_SETFD, oldflags); 
}
