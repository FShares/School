#include "ch10.h"
#define NRECORDS (100)

typedef struct {
    int integer;
	char string[16];
} RECORD;

int main(void)
{
    RECORD record, *mapped;
    int i,fd;
    FILE *fp;
    fp = fopen("records.dat","w+");
    if (fp==NULL)
       err_exit("fopen:");
    /* 写记录至文件 */
    for (i=0;i<NRECORDS;i++){
       record.integer = i;
       sprintf(record.string, "RECORD-%4d", i);
       fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);
    /* 重新打开此文件用存储映射方法修改第43个记录 */
    fd = open("records.dat",O_RDWR);
    /* 将文件的前NRECORDS个记录映射到内存 */
    mapped = (RECORD *)mmap(0, NRECORDS*sizeof(record),
	              PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
    mapped[43].integer = 243;     /* 修改第43个记录的记录号 */
    sprintf(mapped[43].string, "RECORD-%d",mapped[43].integer);
    msync((void*)mapped, NRECORDS*sizeof(record), MS_ASYNC); /* 同步磁盘 */
    munmap((void*)mapped, NRECORDS*sizeof(record));	/* 删除存储映射 */
	/*查看文件有否改变 */ 
    lseek(fd, 43*sizeof(record), SEEK_SET);
    read(fd, &record, sizeof(record));
    printf("record[43].integer = %d\n",record.integer);
    close(fd);
    exit(0);
}
