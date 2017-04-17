#include "ch05.h"

main()
{
   int mem_grp, num_grp, i, gidsetsize;
   gid_t *grouplist;
   struct group *groupinfo;
   char **ptr;

   /* ������Ա������Ϊ������ID�������ռ� */
   num_grp = getgroups(0,grouplist);  
   grouplist = (gid_t *)xmalloc((size_t)(sizeof(gid_t)*num_grp));

   /* ��ø�����ID */
   if ((mem_grp = getgroups(num_grp, grouplist))<0)
      err_exit("");
   printf("there are %d supplementary groups",mem_grp);

   /* �г�ÿ��������֡���ID�Լ����Ա�� */
   for (i=0; i<mem_grp; i++) {
      groupinfo = getgrgid(grouplist[i]);
      printf("\ngroup name is: %s \n", groupinfo->gr_name);
      printf("  group id is: %d\n", groupinfo->gr_gid); 
      ptr = groupinfo->gr_mem;
      if (*ptr == NULL)
         printf("No additional members in this group\n ");
      else {
         printf("the members in this group are: ");  
         while ( *ptr ) 
            printf("%s, ", *ptr++);
      }
   }
   printf("\nDone\n");
}
