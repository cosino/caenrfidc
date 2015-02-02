#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

extern char *bin2hex(uint8_t *data, size_t len);
extern char *hex2bin(char *str, size_t *size);

#endif /* _UTILS_H */
