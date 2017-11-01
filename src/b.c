
#include "___h.h"

char *_bits(float s)
{
    static char v[12];
    if(s-(int)s>0.09) 
        sprintf(v, "%d Bit%s", (int)((s-(int)s)*10.0), (int)((s-(int)s)*10.0)>1?"s":"");
    else
        sprintf(v, "%d Byte%s", (int)s, (int)s>1?"s":"");
    return v;
}

int xlog(const int type, const char *fmt, ...)
{
    char buf[10240];
    va_list args;

    va_start(args, fmt);

    if (!fmt)
        return false;

    vsprintf(buf, fmt, args);

    va_end(args);

    fprintf(stdout, "%s\n", buf);
    return true;
}

int dump_mem(unsigned char *memory, int size, const int flg)
{
    int i;

    if(size<1)
        return false;

    if(flg)
    fprintf(stdout, "-1--2--3--4--5--6--7--8-Hex-0--1--2--3--4--5--6""\n");

    for(i=0; i<size; i++)
    {
        if(i && !(i%16))
            fprintf(stdout, "\n");
        else if(i)
            fprintf(stdout, " ");

        fprintf(stdout, "%02X", memory[i]);
    }
    fprintf(stdout, "\n");

    return true;
}

unsigned bcd2bin(unsigned char v)
{
    return (v&0xf) + (v>>4)*10;
}

unsigned char bin2bcd(unsigned int v)
{
    return ((v/10)<<4) + v%10;
}

int bcd2str(char *bcd, int len, unsigned char *str)
{
    int i=0;
    for(i=0; i<len; i++)
    {
        str[i*2] = ((bcd[i]&0xf0)>>4) + 0x30;
        str[i*2+1] = (bcd[i]&0x0f) + 0x30;
    }

    return true;
}

enum ecolor{
    BLK=0,
    RED,
    GRN,
    YEL,
    BLU,
    GRA,
    GBL,
    WHT,
    RST,
};

color _color[] = {
    { .idx = BLK, .color = "\e[1;30m" },
    { .idx = RED, .color = "\e[1;31m" },
    { .idx = GRN, .color = "\e[1;32m" },
    { .idx = YEL, .color = "\e[1;33m" },
    { .idx = BLU, .color = "\e[1;34m" },
    { .idx = GRA, .color = "\e[1;35m" },
    { .idx = GBL, .color = "\e[1;36m" },
    { .idx = WHT, .color = "\e[1;37m" },
    { .idx = RST, .color = "\e[0m" },
};

#define select_color(c) _color[c].color

void print_header(filed *f, int size, char *pmsg)
{
    int i, j;
    int len;

    int linesize=0;

    char buf[1204] = "";

    xlog(0, "%s %d", __func__, __LINE__);

    if(size<1 || ! pmsg)
    {
        return;
    }

    fprintf(stdout, "-1--2--3--4--5--6--7--8-Hex-0--1--2--3--4--5--6""\n");

    for(i=0, len=0; i<size; i++)
    {
        len += sprintf(buf+len, "%s", select_color(i==0?6:i%(array_size(_color))));

        for(j=0; j<f[i].len; j++)
        {
            if(linesize && linesize%16==0)
            {
                len += sprintf(buf+len, "%s\n%s", select_color(RST), select_color(i==0?6:i%(array_size(_color))));
                linesize=0;
            }
            else if(linesize)
            {
                len += sprintf(buf+len, " ");
            }

            linesize++;
            len += sprintf(buf+len, "%02X", f[i].value.string[j]);
        }

        len += sprintf(buf+len, "%s", select_color(RST));
    }
    fprintf(stdout, "%s\n", buf);

    return;
}
