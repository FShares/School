#include "ch09.h"
int set_termios(int desc)
{
    struct termios settings;
    int result;    
    result = tcgetattr(desc, &settings); /* 获取当前终端属性 */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    settings.c_iflag &= ~ISTRIP;    /* 清除ISTRIP */
    settings.c_lflag &= ~(ICANON | ECHO | ISIG);  /* 设置非加工输入 */
    settings.c_oflag |= OPOST ;                   /* 设置实现定义的输出处理 */
    result = tcsetattr(desc, TCSANOW, &settings); /* 使新设置立即生效 */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    return 1;
}
