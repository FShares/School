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
    /* д��¼���ļ� */
    for (i=0;i<NRECORDS;i++){
       record.integer = i;
       sprintf(record.string, "RECORD-%4d", i);
       fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);
    /* ���´򿪴��ļ��ô洢ӳ�䷽���޸ĵ�43����¼ */
    fd = open("records.dat",O_RDWR);
    /* ���ļ���ǰNRECORDS����¼ӳ�䵽�ڴ� */
    mapped = (RECORD *)mmap(0, NRECORDS*sizeof(record),
	              PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
    mapped[43].integer = 243;     /* �޸ĵ�43����¼�ļ�¼�� */
    sprintf(mapped[43].string, "RECORD-%d",mapped[43].integer);
    msync((void*)mapped, NRECORDS*sizeof(record), MS_ASYNC); /* ͬ������ */
    munmap((void*)mapped, NRECORDS*sizeof(record));	/* ɾ���洢ӳ�� */
	/*�鿴�ļ��з�ı� */ 
    lseek(fd, 43*sizeof(record), SEEK_SET);
    read(fd, &record, sizeof(record));
    printf("record[43].integer = %d\n",record.integer);
    close(fd);
    exit(0);
}
