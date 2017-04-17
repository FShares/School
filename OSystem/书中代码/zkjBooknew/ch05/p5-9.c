#include "ch05.h"
static void setup_core_dumping (void)
{
   struct rlimit rlim;
   if (getrlimit(RLIMIT_CORE, &rlim) != 0)   /* ��ȡ����ֵ  */
      err_exit("getting core file size maximum limit ");
   rlim.rlim_cur = rlim.rlim_max;              /* ��Ӳ�����滻������  */
   if (setrlimit(RLIMIT_CORE, &rlim) != 0)   /* ������������ֵ  */
      err_exit("setting core file size limit to maximum ");
}
