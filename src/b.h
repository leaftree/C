
#ifndef __b_h__
#define __b_h__

#include "___h.h"

#define _Nulls(s) (!(*s)?"":s)
#define array_size(x)  (sizeof(x)/sizeof(x[0]))

typedef struct _filed_attr {
    int type:4;
		int padflg:2; /* reserve Not-pad:0 Right-pad:1 Left-pad:2 */
		int padsize:4;/* reserve */
		int loopflg:1;/* Not TINT-Type is invaliad, Not-loop:0 Not-loop:1 */
		int bos:1;    /* Big-size:0 Little-size:1 */
    float size;
    char penname[64];
    char pchname[64];
    char premark[64];
} filed_attr;

typedef struct _filed {
    int ofs;
    int len;
    union {
        long long int integer;
        char string[1024];
    }value;
    filed_attr *fa;
}filed;

enum filed_type {
    TINT = 1,
    TBCD,
    TSTRING,
};

typedef struct color {
    int idx;
    char color[12];
} color;

char *_bits(float s);
int xlog(const int type, const char *fmt, ...);
int dump_mem(unsigned char *memory, int size, const int flg);
int bcd2str(char *bcd, int len, unsigned char *str);

void print_header(filed *f, int size, char *pmsg);

/*
unsigned int bcd2bin(unsigned char v);
unsigned char bin2bcd(unsigned int v);
*/

#endif
