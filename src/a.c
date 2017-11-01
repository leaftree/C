#include "___h.h"

#define _sizeof(type) filed_type_size[type]


int main(int argc, char **argv)
{
    int i = 0;

    filed f[100];
    filed ff[100];

    // HACK: is not good for define here, but have no choice.
#include "defs.h"

    for(i=0; i<array_size(CssHeaderInfo)+array_size(MsgTypeInfo)+array_size(MSG0604Info); i++)
    {
        f[i].ofs = i;

        if(i<7)
        {
            f[i].fa = &CssHeaderInfo[i];
            f[i].len = CssHeaderInfo[i].size;
        }
        else if(i==7)
        {
            f[i].fa = &MsgTypeInfo[i-7];
            f[i].len = MsgTypeInfo[i-7].size;
        }
        else if(i>7)
        {
            f[i].fa = &MSG0604Info[i-7-1];
            f[i].len = MSG0604Info[i-7-1].size;
        }
    }
    f[1].len = f[1].fa->size*10;
    f[2].len = f[2].fa->size*14;
    f[10].len = f[10].fa->size*4;
    f[11].len = f[11].fa->size*2;

    memcpy(ff, f, sizeof(ff));

    FILE *fp = fopen("text.txt", "r+");
    if(fp == NULL)
    {
        xlog(1, "open file %s failed.", "text.txt");
        return false;
    }

    int len=0;
    char ch;
    char flg;
    char tmp[4] = "";
    char buf[1000] = "";

    flg=0;
    int msglen=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(!isxdigit(ch))
            continue;

        if(!flg)
        {
            tmp[0] = ch;
            flg = 1;
            continue;
        }
        else
        {
            tmp[1] = ch;
            flg = 0;
            msglen++;
            buf[len++] = strtol(tmp, NULL, 16);
        }
    }
    fclose(fp);
    xlog(0, "[%s(%d-%s) ] Now here. msglen %d", __FILE__, __LINE__, __func__, msglen);

    xlog(1, "%s", "dump memory");
    dump_mem((unsigned char*)buf, len, 1);
    xlog(0, "------------------");

    int ofs=0;
    for(i=0; i<array_size(CssHeaderInfo)+array_size(MsgTypeInfo)+array_size(MSG0604Info); i++)
    {
        char tmp[120] = "";
        memcpy(tmp, buf+ofs, f[i].len);
        ofs += f[i].len;

        if(f[i].fa->type == TSTRING)
        {
            sprintf(f[i].value.string, "%s", tmp);
            sprintf(ff[i].value.string, "%s", tmp);
        }
        else if(f[i].fa->type == TBCD)
        {
            memcpy(ff[i].value.string, tmp, f[i].len);
            bcd2str(tmp, f[i].len, f[i].value.string);
        }
        else
        {
            memcpy(&f[i].value.integer, tmp, f[i].len);
            memcpy(&ff[i].value.integer, tmp, ff[i].len);
            if(f[i].len==2)
                f[i].value.integer = ntohs(f[i].value.integer);
            else
                f[i].value.integer = ntohl(f[i].value.integer);
        }
    }

    int loopflg=0;
    int loopcnt=0;
    for(i=0; i<array_size(CssHeaderInfo)+array_size(MsgTypeInfo)+array_size(MSG0604Info); i++)
    {
        if(f[i].fa->type==TSTRING || f[i].fa->type == TBCD)
            xlog(1, "%10s :  %-15s | %15s | %s", f[i].fa->penname, f[i].value.string, f[i].fa->pchname, f[i].fa->premark);
        else
        {
            /*
            if(TYPE_IS_NUMBER(f[i].fa->type) && f[i].fa->loopflg)
            {
                loopflg=1;
                loopcnt=f[i].value.integer;
            }
            loopcnt--;
            if(!loopcnt)
                loopflg=0;
                */
            xlog(1, "%10s :  %-15x | %15s | %s", f[i].fa->penname, f[i].value.integer, f[i].fa->pchname,f[i].fa->premark);
        }
    }

    xlog(0, "------------------");

    print_header(ff, 15, buf);

    return 0;
}

