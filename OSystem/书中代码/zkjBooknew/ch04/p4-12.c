#include "ch04.h"
#include "get_perms.c"  /* ����4-4 */
#define BLKSIZE 1024
void list(char *);
void printout(char *, char *);

int main(int argc, char *argv[])
{ 
   struct stat sbuf;
  
   if (argc < 2){  /* ���޲���,�г���ǰĿ¼ */
      list(".");
      exit(0);
   }

   /* ������� */
   while(--argc){
     if (stat(*++argv,&sbuf) < 0) {  /* �鿴�ļ����� */
        perror(*argv);
        continue;
     }
     /* �����Ŀ¼�������г��������ӡ���ļ���״̬��Ϣ */
     if ((sbuf.st_mode &S_IFMT) == S_IFDIR)
        list(*argv);
     else
        printout(".",*argv);
   }
   exit(0);
}

/* ��һ��Ŀ¼���г����е��ļ� */
void list(char *name)
{
   DIR *dp;
   struct dirent *dir;
   if ((dp = opendir(name)) == NULL) { /*  �򿪸�Ŀ¼  */
      fprintf(stderr, "%s: cannot open.\n",name);
      return;
   }

   while((dir = readdir(dp)) != NULL)  /*  ����ÿһ��Ŀ¼ */
      printout(name, dir->d_name);
   closedir(dp);
}

void printout(char *dir, char *name)  /* ��ӡ���ļ����й���Ϣ */
{
   int i,j;
   char perms[10];
   struct stat sbuf;
   char newname[BLKSIZE];

   sprintf(newname,"%s/%s",dir,name);   /* �γ�·���� */
   stat(newname,&sbuf);/* ��ʱ���Կ϶����ļ����ڣ��ʲ���ʧ�ܼ�� */
   /* ��ӡ�ļ��Ŀ��С��ÿ��ΪBLKSIZE�ֽ� */
   printf("%5d",(sbuf.st_size+BLKSIZE-1)/BLKSIZE);
   /* ��Ⲣ��ӡ�ļ����� */
   switch(sbuf.st_mode & S_IFMT){
     case S_IFREG:  putchar('-'); break;
     case S_IFDIR:  putchar('d'); break;
     case S_IFCHR:  putchar('c'); break;
     case S_IFBLK:  putchar('b'); break;
     case S_IFIFO:  putchar('l'); break;
#ifdef S_IFLNK
     case S_IFLNK:  putchar('l'); break;
#endif
#ifdef S_IFSOCK
     case S_IFSOCK: putchar('l'); break;
#endif
     default:       putchar('?'); break;
   }
  
   get_perms(&sbuf, perms);  /* ��ȡ�������Ȩ�ޣ�������4-4�� */
   /* ��ӡ����Ȩ�ޡ����������û�ID����ID */
   printf("%s%3d %5d/%-5d ", perms, sbuf.st_nlink, sbuf.st_uid,
                   sbuf.st_gid);
   /* ��ӡ�ļ���С���޸�ʱ�䡣ctimeת��һ��ʱ��ΪASCII�ַ� */
   printf("%7d %.20s ",sbuf.st_size, ctime(&sbuf.st_mtime));
   printf("%s\n", name); /* ��󣬴�ӡ�ļ��� */
}
