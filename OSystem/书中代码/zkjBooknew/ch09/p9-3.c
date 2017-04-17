#include "ch09.h"
int set_termios(int desc)
{
    struct termios settings;
    int result;    
    result = tcgetattr(desc, &settings); /* ��ȡ��ǰ�ն����� */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    settings.c_iflag &= ~ISTRIP;    /* ���ISTRIP */
    settings.c_lflag &= ~(ICANON | ECHO | ISIG);  /* ���÷Ǽӹ����� */
    settings.c_oflag |= OPOST ;                   /* ����ʵ�ֶ����������� */
    result = tcsetattr(desc, TCSANOW, &settings); /* ʹ������������Ч */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    return 1;
}
