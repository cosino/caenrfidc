#include "client.h"

/*
 * Commands functions
 */

int cmd_exit(struct command_s *cmd, int argc, char *argv[])
{
	PDEBUG("%s", __func__);

	exit(EXIT_SUCCESS);
}
