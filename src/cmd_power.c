#include "client.h"

/*
 * Commands functions
 */

static int cmd_power_get(struct command_s *cmd, int argc, char *argv[])
{
	unsigned int power;
	int ret;

	PDEBUG("%s", __func__);

	/* Check the command line */
	if (argc < 2) {
		PERR("must specify radio <id>");
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

        ret = CAENRFID_GetPower(&handle, &power);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	PDATA("pow=%d", power);
	return 0;
}

static int cmd_power_set(struct command_s *cmd, int argc, char *argv[])
{
        int power;
	int ret;

	/* Check the command line */
	if (argc < 3) {
		PERR("must specify radio <id> and <pow>");
		return -1;
	}

	PDEBUG("%s: %s %s %s", __func__, argv[0], argv[1], argv[2]);

	if (sscanf(argv[2], "%d", &power) != 1 || power < 0) {
		PERR("invalid value <pow>");
		return -1;
	}

        ret = CAENRFID_SetPower(&handle, power);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot set data (err=%d)", ret);
                exit(-1);
        }

	PDATA("done");
	return 0;
}

int cmd_power(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 3) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	if (!strcmp(argv[2], "get"))
		return cmd_power_get(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[2], "set"))
		return cmd_power_set(cmd, argc - 1, argv + 1);

	PERR("%s: unsupported options \"%s\"", argv[0], argv[1]);
	return -1;
}
