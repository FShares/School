/* 若value非0，设置FD_CLOEXEC标志,若value为0,清除该标志。成功返回0，失败返回-1*/
#include "ch03.h"
int set_cloexec_flag (int desc, int value)
{
   int oldflags = fcntl (desc, F_GETFD, 0);
   if(oldflags < 0)    /* 若读标签失败，错误返回。*/
       return oldflags;
   /* 设置需要的标志. */
   if(value != 0)
       oldflags |= FD_CLOEXEC;
   else
      oldflags &= ~FD_CLOEXEC;
   return fcntl (desc, F_SETFD, oldflags); 
}
