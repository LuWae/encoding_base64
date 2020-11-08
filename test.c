#include <stdio.h>
#include <stdlib.h>

#include "base64.h"

int main() {
    /* run example
     * 11110000 00110010 10110100 10101010
     * |----||- ---||--- -||----| |----||- ----
     *    8     D      K      0      q     g
     */
    unsigned char b[] = {0xF0, 0x32, 0xB4, 0xAA};
    char *s = malloc(10);
    
    int num_written = b64_encode(b, 4, s);
    *(s + num_written) = '\0';
    
    printf("--------ENCODE-TEST--------\nexpected: 8DK0qg\ngot:      %s\n", s);
    
    char *s2 = "8DK0qg";
    unsigned char *b2 = malloc(10);
    
    num_written = b64_decode(s2, 6, b2);
    printf("--------DECODE-TEST--------\nexpected: f0 32 b4 aa\ngot:      ");
    for(int i = 0; i < num_written; i++) {
        printf("%x ", *(b2 + i));
    }
    printf("\n");
    
    free(s);
    free(b2);
    return 0;
}
