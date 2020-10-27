#ifndef BASE64_H
#define BASE64_H

int b64_encode(const void *p, int length, char *buf);
int b64_decode(const char *buf, int length, void *p);

#endif
