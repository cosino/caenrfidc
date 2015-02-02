#include "client.h"
#include "utils.h"
#include "macros.h"

/*
 * Local functions
 */

static char nibble2hex(char c)
{
        switch (c) {
        case 0 ... 9:
                return '0' + c;

        case 0xa ... 0xf:
                return 'a' + (c - 10);
        }

        BUG();
        return '\0';
}

static char hex2nibble(char c)
{
        switch (c) {
        case '0' ... '9':
                return c - '0';

        case 'a' ... 'f':
                return c - 'a' + 10;

        case 'A' ... 'F':
                return c - 'A' + 10;
        }

        BUG();
        return 0;
}

/*
 * Exported functions
 */

char *bin2hex(uint8_t *data, size_t len)
{
        char *str;
        int i;

        str = malloc(len * 2 + 1);
        if (!str)
                return NULL;

        for (i = 0; i < len; i++) {
                str[i * 2] = nibble2hex(data[i] >> 4);
                str[i * 2 + 1] = nibble2hex(data[i] & 0x0f);
        }
        str[i * 2] = '\0';

        return str;
}

char *hex2bin(char *str, size_t *size)
{
        char *bin;
        int i;
        int len;

        if (!str || !size)
                return NULL;

        len = strlen(str);
        if (len == 0) {
                *size = 0;
                return NULL;
        }
        *size = len / 2 + ((len % 2 == 0) ? 0 : 1);

        bin = malloc(*size);
        if (!bin) {
                *size = 0;
                return NULL;
        }

        for (i = 0; i < len; i++) {
                if (i % 2 == 0)
                        bin[i / 2] = hex2nibble(str[i]) << 4;
                if (i % 2 == 1)
                        bin[i / 2] |= hex2nibble(str[i]);
        }

        return bin;
}
