#include "client.h"

/*
 * Commands functions
 */

int cmd_inventory(struct command_s *cmd, int argc, char *argv[])
{
	int i;
	CAENRFIDTag *tag;
	int size;
	char *str;
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

        ret = CAENRFID_InventoryTag(&handle, argv[2], &tag, &size);
        if (ret != CAENRFID_StatusOK) {
                PERR("cannot get data (err=%d)", ret);
                exit(-1);
        }

	PDATA("size=%d", size);
	for (i = 0; i < size; i++) {
		str = bin2hex(tag[i].ID, tag[i].Length);
		if (!str) {
			PERR("cannot allocate memory");
			exit(-1);
		}

		PDATA("epc=%.*s src=%.*s rp=%.*s type=%d rssi=%d",
			tag[i].Length * 2, str,
			MAX_LOGICAL_SOURCE_NAME, tag[i].LogicalSource,
			MAX_READPOINT_NAME, tag[i].ReadPoint,
			tag[i].Type, tag[i].RSSI);

		free(str);
	}

	return 0;
}
