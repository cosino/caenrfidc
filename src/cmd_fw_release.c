#include "client.h"

/*
 * Commands functions
 */

int cmd_fw_release(struct command_s *cmd, int argc, char *argv[])
{
	int i;
	char string[256];
	int ret;

	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 2) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

	if (sscanf(argv[1], "%d", &i) != 1) {
		PERR("invalid <id>");
		return -1;
	}

	string[127] = '\0';
        ret = CAENRFID_GetFWRelease(&handle, string);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	PDATA("rel=%s", string);
	return 0;
}
