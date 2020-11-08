#ifndef BASE64_H
#define BASE64_H

/* Encode arbitrary data to base64.
     * 
     * p is pointer to data.
     * length is the number of bytes to encode.
     * buf is the buffer to write to.
     *
     * returns number of characters written, -1 on error
     */
unsigned int b64_encode(const void *p, unsigned int length, char *buf);

/* Decode string to byte array.
     *
     * buf is input string.
     * length is the number of bytes to encode.
     * p is the buffer to write to.
     *
     * returns number of characters written, -1 on error
     */
unsigned int b64_decode(const char *buf, unsigned int length, void *p);

#endif
