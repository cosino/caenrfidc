#include "client.h"

/*
 * Commands functions
 */

int cmd_dump_regs(struct command_s *cmd, int argc, char *argv[])
{
	int i, s;
	char string[] = "Ant0";
	CAENRFIDTag *tag;
	int size;
	unsigned char *str;
	int ret;

	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 3) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	PDEBUG("%s: %s %s %s", __func__, argv[0], argv[1], argv[2]);

	if (sscanf(argv[1], "%d", &i) != 1) {
		PERR("invalid <id>");
		return -1;
	}
	if (sscanf(argv[2], "%d", &s) != 1 || (s < 0 || s > 3)) {
		PERR("invalid <src>");
		return -1;
	}

	string[3] = '0' + s;
	PDEBUG("%s: ant=%s", __func__, string);
        ret = CAENRFID_DumpRegs(&handle, string);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	return 0;
}
