#include "client.h"

/*
 * Commands functions
 */

static int cmd_readpoint_add(struct command_s *cmd, int argc, char *argv[])
{
	int ret;

	PDEBUG("%s: %s %s", __func__, argv[1], argv[3]);

        ret = CAENRFID_AddReadPoint(&handle, argv[1], argv[3]);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot add readpoint (err=%d)", ret);
                exit(-1);
        }

	PDATA("done");
	return 0;
}

static int cmd_readpoint_rm(struct command_s *cmd, int argc, char *argv[])
{
	int ret;

	PDEBUG("%s: %s %s", __func__, argv[1], argv[3]);

        ret = CAENRFID_RemoveReadPoint(&handle, argv[1], argv[3]);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot rm readpoint (err=%d)", ret);
                exit(-1);
        }

	PDATA("done");
	return 0;
}

static int cmd_readpoint_chk(struct command_s *cmd, int argc, char *argv[])
{
	short val;
	int ret;

	PDEBUG("%s: %s %s", __func__, argv[1], argv[3]);

        ret = CAENRFID_isReadPointPresent(&handle, argv[1], argv[3], &val);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot check readpoint (err=%d)", ret);
                exit(-1);
        }

	PDATA("res=%d", val);
	return 0;
}

int cmd_readpoint(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 4) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	if (!strcmp(argv[3], "add"))
		return cmd_readpoint_add(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[3], "rm"))
		return cmd_readpoint_rm(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[3], "chk"))
		return cmd_readpoint_chk(cmd, argc - 1, argv + 1);

	PERR("%s: unsupported options \"%s\"", argv[0], argv[1]);
	return -1;
}
