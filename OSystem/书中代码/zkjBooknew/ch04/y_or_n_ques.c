#include <stdio.h>

int y_or_n_ques(const char *question)
{
    fputs (question, stdout);
    while (1){
        int c, answer;
         /* дһ�ո�ֿ�������ش� */
        fputc (' ', stdout);
         /* �������еĵ�һ���ַ�.��Ӧ���ǻش��ַ�����Ҳ���ܲ���. */
        c = tolower (fgetc (stdin));
        answer = c;
         /* ���Դ��е������ַ�. */
        while (c != '\n' && c != EOF)
            c = fgetc (stdin);
         /* ����ǻش��ַ�����Ӧ�ش�. */
        if (answer == 'y')
            return 1;
        if (answer == 'n')
            return 0;
        /* �ǻش��ַ�������Ϸ��ش�. */
        fputs ("Please answer y or n:", stdout);
    }
}
