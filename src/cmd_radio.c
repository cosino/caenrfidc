#include "client.h"

/* FIXME: only one client at time for the moment! */
caenrfid_handle_t handle;

/*
 * Commands functions
 */

static int cmd_radio_open(struct command_s *cmd, int argc, char *argv[])
{
	caenrfid_port_t comm_proto;
	char *addr;
	int baud, port;
	int ret;
	
	/* Check the command line */
	if (argc < 2) {
		PERR("must specify <comm_proto>");
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

	if (!strcmp(argv[1], "rs232")) {
		comm_proto = RS232;

		if (argc < 3) {
			PERR("serial data missing! "
				"Usage: rs232 <device> [<baud>]");
			return -1;
		}
		addr = argv[2];
		if (argc == 4) {
			ret = sscanf(argv[3], "%d", &baud);
			if (ret < 1)
				PERR("invalid baud rate %s", argv[3]);
				return -1;
		}
	} else if (!strcmp(argv[1], "tcp")) {
		comm_proto = TCP;

		if (argc < 3) {
			PERR("tcp data missing! "
				"Usage: tcp <address> [<port>]");
                        return -1;
                }
                addr = argv[2];
		if (argc == 4) {
			ret = sscanf(argv[3], "%d", &port);
			if (ret < 1)
				PERR("invalid port %s", argv[3]);
				return -1;
		}
	} else {
		PERR("unknow <comm_proto> (%s)", argv[1]);
                return -1;
        }

        ret = CAENRFID_Init(comm_proto, addr, &handle);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot init lib (err=%d)", ret);
                exit(-1);
        }

#if 0 /* FIMXE: should compute unique ID */
	PDATA("id=%d", handle);
#endif
	PDATA("id=0");
	return 0;
}

static int cmd_radio_close(struct command_s *cmd, int argc, char *argv[])
{
        int i;
	int ret;

	/* Check the command line */
	if (argc < 2) {
		PERR("must specify radio <id>");
		return -1;
	}

	PDEBUG("%s: %s %s", __func__, argv[0], argv[1]);

	if (sscanf(argv[1], "%d", &i) != 1) {
		PERR("invalid <id>");
		return -1;
	}

        ret = CAENRFID_End(&handle);
        if (ret != CAENRFID_StatusOK) {
                PERR("improper caenrfidlib closure!\n");
                exit(-1);
        }

	PDATA("done");
	return 0;
}

int cmd_radio(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	/* Check command line */
	if (argc < 2) {
		PERR("%s %s", cmd->name, cmd->usage);
		return -1;
	}

	if (!strcmp(argv[1], "open"))
		return cmd_radio_open(cmd, argc - 1, argv + 1);
	if (!strcmp(argv[1], "close"))
		return cmd_radio_close(cmd, argc - 1, argv + 1);

	PERR("%s: unsupported options \"%s\"", argv[0], argv[1]);
	return -1;
}
