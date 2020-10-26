/* 011010 11   1110 0101   00 100010
   --26-- ----62--- ----20--- --34--
        a         +         U      i
   a+Ui
   
   01101011
   aw
   
   01101011 11100101
   a+U
 */

#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char
#define ERROR -1

static char encode(BYTE byte) {
    if(byte < 26) return 'A' + byte;
    if(byte < 52) return 'a' + byte - 26;
    if(byte < 62) return '0' + byte - 52;
    if(byte == 62) return '+';
    return '/';
}

static BYTE decode(char c) {
    if(c == '+') return 0x3E;
    if(c == '/') return 0x3F;
    if(c <= '9') return 0x34 + c - '0';
    if(c <= 'Z') return c - 'A';
    return 0x1A + c - 'a';
}

#define WRITE(byte, buf, bp) (*((buf) + (bp)++) = encode(byte))

int b64_encode(void *p, int length, char *buf) {
    BYTE *cp = p;
    BYTE a, b, c;
    int bp = 0;
    
    int i;
    
    for(i = 0; i < length - 2; i += 3) {
        //regular cases
        a = *(cp + i);
        b = *(cp + i + 1);
        c = *(cp + i + 2);
        
        WRITE((a>>2) & 0x3F, buf, bp);
        WRITE(((a<<4) & 0x30) + ((b>>4) & 0x0F), buf, bp);
        WRITE(((b<<2) & 0x3C) + ((c>>6) & 0x03), buf, bp);
        WRITE(c & 0x3F, buf, bp);
    }
    
    switch(length - i) {
        case 0:
            return i*4;
        case 1:
            a = *(cp + i);
            WRITE((a>>2) & 0x3F, buf, bp);
            WRITE((a<<4) & 0x30, buf, bp);
            return i*4 + 2;
        case 2:
            a = *(cp + i);
            b = *(cp + i + 1);
            WRITE((a>>2) & 0x3F, buf, bp);
            WRITE(((a<<4) & 0x30) + ((b>>4) & 0x0F), buf, bp);
            WRITE((b<<2) & 0x3C, buf, bp);
            return i*4 + 3;
        default:
            return ERROR;
    }
}

int b64_decode(char *buf, int length, void *p) {
    /*TODO*/
    return 0;
    
    /*
    char a, b, c, d;
    int index = 0;
    
    for(int i = 0; i < length - 3; i += 4) {
        a = *(buf + i);
        b = *(buf + i + 1);
        c = *(buf + i + 2);
        d = *(buf + i + 3);
    }
    */
}

int main() {
    BYTE s[] = {0xFF, 0x00, 0xFF, 0x00, 0xAF, 0x70, 0xCC, 0x03};
    
    char *res = malloc(100);
    int nbytes = b64_encode(s, 8, res);
    if(nbytes >= 0) {
        *(res + nbytes) = '\0';
        printf("%s\n", res);
    } else {
        printf("encoding error\n");
    }
    
    
    free(res);
    return 0;
}
