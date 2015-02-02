#include "client.h"

/*
 * Commands functions
 */

static int cmd_channel_get(struct command_s *cmd, int argc, char *argv[])
{
	unsigned short channel;
	int ret;

	PDEBUG("%s", __func__);

	/* Check the command line */
	if (argc < 2) {
		PERR("must specify radio <id>");
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

        ret = CAENRFID_GetRFChannel(&handle, &channel);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	PDATA("chan=%d", channel);
	return 0;
}

static int cmd_channel_set(struct command_s *cmd, int argc, char *argv[])
{
        int channel;
	int ret;

	/* Check the command line */
	if (argc < 3) {
		PERR("must specify radio <id> and <chan>");
		return -1;
	}

	PDEBUG("%s: %s %s %s", __func__, argv[0], argv[1], argv[2]);

	if (sscanf(argv[2], "%d", &channel) != 1 || channel < 0) {
		PERR("invalid value <chan>");
		return -1;
	}

        ret = CAENRFID_SetRFChannel(&handle, channel);
        if (ret != CAENRFID_StatusOK) {
		PERR("cannot set data (err=%d)", ret);
                exit(-1);
        }

	PDATA("done");
	return 0;
}

int cmd_channel(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 3) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	if (!strcmp(argv[2], "get"))
		return cmd_channel_get(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[2], "set"))
		return cmd_channel_set(cmd, argc - 1, argv + 1);

	PERR("%s: unsupported options \"%s\"", argv[0], argv[1]);
	return -1;
}
