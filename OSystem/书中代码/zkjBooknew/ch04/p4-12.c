#include "ch04.h"
#include "get_perms.c"  /* 程序4-4 */
#define BLKSIZE 1024
void list(char *);
void printout(char *, char *);

int main(int argc, char *argv[])
{ 
   struct stat sbuf;
  
   if (argc < 2){  /* 若无参数,列出当前目录 */
      list(".");
      exit(0);
   }

   /* 处理参数 */
   while(--argc){
     if (stat(*++argv,&sbuf) < 0) {  /* 查看文件类型 */
        perror(*argv);
        continue;
     }
     /* 如果是目录，将它列出，否则打印出文件的状态信息 */
     if ((sbuf.st_mode &S_IFMT) == S_IFDIR)
        list(*argv);
     else
        printout(".",*argv);
   }
   exit(0);
}

/* 读一个目录并列出其中的文件 */
void list(char *name)
{
   DIR *dp;
   struct dirent *dir;
   if ((dp = opendir(name)) == NULL) { /*  打开该目录  */
      fprintf(stderr, "%s: cannot open.\n",name);
      return;
   }

   while((dir = readdir(dp)) != NULL)  /*  处理每一个目录 */
      printout(name, dir->d_name);
   closedir(dp);
}

void printout(char *dir, char *name)  /* 打印出文件的有关信息 */
{
   int i,j;
   char perms[10];
   struct stat sbuf;
   char newname[BLKSIZE];

   sprintf(newname,"%s/%s",dir,name);   /* 形成路径名 */
   stat(newname,&sbuf);/* 此时可以肯定该文件存在，故不做失败检测 */
   /* 打印文件的块大小，每块为BLKSIZE字节 */
   printf("%5d",(sbuf.st_size+BLKSIZE-1)/BLKSIZE);
   /* 检测并打印文件类型 */
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
  
   get_perms(&sbuf, perms);  /* 获取三组访问权限（见程序4-4） */
   /* 打印访问权限、链接数、用户ID和组ID */
   printf("%s%3d %5d/%-5d ", perms, sbuf.st_nlink, sbuf.st_uid,
                   sbuf.st_gid);
   /* 打印文件大小和修改时间。ctime转换一个时间为ASCII字符 */
   printf("%7d %.20s ",sbuf.st_size, ctime(&sbuf.st_mtime));
   printf("%s\n", name); /* 最后，打印文件名 */
}
