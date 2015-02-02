#include "client.h"

/*
 * Commands functions
 */

int cmd_help(struct command_s *cmd, int argc, char *argv[])
{
	struct command_s *ptr;

	PDEBUG("%s", __func__);

	if (argc == 1) {
		PDATA("commands list:");
		for (ptr = commands_list; ptr->name; ptr++)
			PDATA("\t%s %s", ptr->name, ptr->usage ? ptr->usage : "");

		return 0;
	}

	/* Display specific command help */
	for (ptr = commands_list; ptr->name; ptr++)
		if (strcmp(ptr->name, argv[1]) == 0)
			break;
	if (!ptr->name) {
		PERR("unknow command %s", argv[1]);
		return -1;
	}
	PDATA("%s %s", ptr->name, ptr->usage ? ptr->usage : "");

	return 0;
}
