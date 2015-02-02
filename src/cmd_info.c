#include "client.h"

/*
 * Commands functions
 */

int cmd_info(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	PDATA("%s - version %s", NAME, VERSION);
	return 0;
}
