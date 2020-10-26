#ifndef BASE64_H
#define BASE64_H

int b64_encode(void *p, int length, char *buf);
int b64_decode(char *buf, int length, void *p);

#endif
