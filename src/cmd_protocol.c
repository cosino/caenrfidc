#include "client.h"

/*
 * Commands functions
 */

static int cmd_protocol_get(struct command_s *cmd, int argc, char *argv[])
{
	caenrfid_protocol_t protocol;
	int ret;

	PDEBUG("%s", __func__);

	/* Check the command line */
	if (argc < 2) {
		PERR("must specify radio <id>");
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

        ret = CAENRFID_GetProtocol(&handle, &protocol);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	PDATA("proto=%d", protocol);
	return 0;
}

static int cmd_protocol_set(struct command_s *cmd, int argc, char *argv[])
{
	caenrfid_protocol_t protocol;
	int num, ret;

	/* Check the command line */
	if (argc < 3) {
		PERR("must specify radio <id> and <proto>");
		return -1;
	}

	PDEBUG("%s: %s %s %s", __func__, argv[0], argv[1], argv[2]);

	if (sscanf(argv[2], "%d", &num) != 1 || num < 0) {
		PERR("invalid value <proto>");
		return -1;
	}
	protocol = num;

        ret = CAENRFID_SetProtocol(&handle, protocol);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot set data (err=%d)", ret);
                exit(-1);
        }

	PDATA("done");
	return 0;
}

int cmd_protocol(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 3) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	if (!strcmp(argv[2], "get"))
		return cmd_protocol_get(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[2], "set"))
		return cmd_protocol_set(cmd, argc - 1, argv + 1);

	PERR("%s: unsupported options \"%s\"", argv[0], argv[1]);
	return -1;
}
