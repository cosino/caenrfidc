#include "client.h"

/*
 * Commands functions
 */

int cmd_help(struct command_s *cmd, int argc, char *argv[])
{
	struct command_s *ptr;

	PDEBUG("%s", __func__);

	PDATA("commands list:");
	for (ptr = commands_list; ptr->name; ptr++)
		PDATA("\t%s %s", ptr->name, ptr->usage ? ptr->usage : "");

	return 0;
}
