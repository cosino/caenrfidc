#include "client.h"

/*
 * Commands functions
 */

int cmd_read(struct command_s *cmd, int argc, char *argv[])
{
	int i;
	char *source = "Source_0";
	char *antenna = "Ant0";
	CAENRFIDTag tag;
	char *tmp = NULL, *pwd=NULL;
	size_t size;
        unsigned char data[128];
        int bank, len, ret, offset, password=0;

	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 6) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	PDEBUG("%s: %s %s %s %s %s %s", __func__,
			argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);

	if (sscanf(argv[1], "%d", &i) != 1) {
		PERR("invalid <id>");
		return -1;
	}

	strcpy(tag.LogicalSource, source);
	strcpy(tag.ReadPoint, antenna);
	tag.Type = EPC_C1G2;
	PDEBUG("%s: src=%s ant=%s type=%d", __func__, source, antenna, type);

        tmp = hex2bin(argv[2], &size);
	EXIT_ON(!tmp);
        memcpy(tag.ID, tmp, size);
        free(tmp);
	tag.Length = size;

	if (!strcmp("RES", argv[3]))
		bank = 0;
	else if (!strcmp("EPC", argv[3]))
		bank = 1;
	else if (!strcmp("TID", argv[3]))
		bank = 2;
	else if (!strcmp("USR", argv[3]))
		bank = 3;
	else {
		PERR("unknow memory bank %s", argv[3]);
		return -1;
	}

	ret = sscanf(argv[4], "%d", &offset);
	if (ret != 1 || offset < 0) {
		PERR("invalid offset");
                return -1;
        }

	ret = sscanf(argv[5], "%d", &len);
	if (ret != 1 || len < 0) {
		PERR("invalid # bytes to read");
                return -1;
        }

	if (argc >= 7) {
		pwd = hex2bin(argv[6], &size);
        	if (size < 4) {
			PERR("must specify a valid password");
			return -1;
		}
		password = htonl(pwd[0] | (pwd[1] << 8) |
				(pwd[2] << 16) | (pwd[3] << 24));
		free(pwd);
	}

	ret = CAENRFID_Read_C1G2(&handle, &tag, bank, offset,
				len, data, password);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	tmp = bin2hex(data, len);
	EXIT_ON(!tmp);
	PDATA("data=%.*s", tag.Length * 2, tmp);
	free(tmp);

	return 0;
}
