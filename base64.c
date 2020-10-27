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

#define WRITE_ENCODE(byte, buf, bp) (*((buf) + (bp)++) = encode(byte))

int b64_encode(const void *p, int length, char *buf) {
    const BYTE *cp = p;
    BYTE a, b, c;
    int bp = 0;
    
    int i;
    
    for(i = 0; i < length - 2; i += 3) {
        //regular cases
        a = *(cp + i);
        b = *(cp + i + 1);
        c = *(cp + i + 2);
        
        WRITE_ENCODE((a>>2) & 0x3F, buf, bp);
        WRITE_ENCODE(((a<<4) & 0x30) |  ((b>>4) & 0x0F), buf, bp);
        WRITE_ENCODE(((b<<2) & 0x3C) | ((c>>6) & 0x03), buf, bp);
        WRITE_ENCODE(c & 0x3F, buf, bp);
    }
    
    //end
    switch(length - i) {
        case 0:
            return i*4;
        case 1:
            a = *(cp + i);
            WRITE_ENCODE((a>>2) & 0x3F, buf, bp);
            WRITE_ENCODE((a<<4) & 0x30, buf, bp);
            return i*4 + 2;
        case 2:
            a = *(cp + i);
            b = *(cp + i + 1);
            WRITE_ENCODE((a>>2) & 0x3F, buf, bp);
            WRITE_ENCODE(((a<<4) & 0x30) + ((b>>4) & 0x0F), buf, bp);
            WRITE_ENCODE((b<<2) & 0x3C, buf, bp);
            return i*4 + 3;
        default:
            return ERROR;
    }
}

int b64_decode(const char *buf, int length, void *p) {
    BYTE *cp = p;
    char a, b, c, d;
    int index = 0;
    int i;
    
    for(i = 0; i < length - 3; i += 4) {
        //regular cases
        a = *(buf + i);
        b = *(buf + i + 1);
        c = *(buf + i + 2);
        d = *(buf + i + 3);
        
        *(cp + index) = ((decode(a)<<2) & 0xFC) | ((decode(b)>>4) & 0x03);
        *(cp + index + 1) = ((decode(b)<<4) & 0xF0) | ((decode(c)>>2) & 0x0F);
        *(cp + index + 2) = ((decode(c)<<6) & 0xC0) | ((decode(d)) & 0x3F);
        
        index += 3;
    }
    
    //end
    switch(length - i) {
        case 0:
            return index;
        case 2:
            a = *(buf + i);
            b = *(buf + i + 1);
            *(cp + index) = ((decode(a)<<2) & 0xFC) | ((decode(b)>>4) & 0x03);
            return index + 1;
        case 3:
            a = *(buf + i);
            b = *(buf + i + 1);
            c = *(buf + i + 2);
            *(cp + index) = ((decode(a)<<2) & 0xFC) | ((decode(b)>>4) & 0x03);
            *(cp + index + 1) = ((decode(b)<<4) & 0xF0) | ((decode(c)>>2) & 0x0F);
            return index + 2;
        default:
            return ERROR;
    }
}

int main() {
    char s[] = {'a', 'w'};
    BYTE *p = malloc(100);
    
    int num_written = b64_decode(s, 2, p);
    for(int i = 0; i < num_written; i++) {
        printf("%d: %x\n", i, *(p + i));
    }
    
    free(p);
    return 0;
}
