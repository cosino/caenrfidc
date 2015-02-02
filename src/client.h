/*
 * Misc defines
 */

#define NAME		program_invocation_short_name

#ifdef ENABLE_DEBUG
#define CDEBUG(code)	\
			do { code } while (0)
#define PDEBUG(fmt, args...)	\
			fprintf(stderr, "%s:%s[%d]: " fmt "\n", \
				NAME, __FILE__, __LINE__ , ## args)
#define PERR(fmt, args...)	\
			fprintf(stderr, "%s:%s[%d]: ko: " fmt "\n", \
				NAME, __FILE__, __LINE__ , ## args)
#define PDATA(fmt, args...)	\
			printf("%s:%s[%d]: ok: " fmt "\n", \
				NAME, __FILE__, __LINE__ , ## args)

#define PCODE(code)	\
			do {						\
				fprintf(stderr, "%s:%s[%d]: ",		\
					NAME, __FILE__, __LINE__);	\
				code					\
			} while (0)

#else /* ENABLE_DEBUG */

#define CDEBUG(code) /* do nothing! */
#define PDEBUG(fmt, args...)	\
			/* do nothing! */
#define PERR(fmt, args...)	\
			printf("ko: " fmt "\n" , ## args)
#define PDATA(fmt, args...)	\
			printf("ok: " fmt "\n" , ## args)

#define PCODE(code)		 /* do nothing! */
#endif /* ENABLE_DEBUG */

/*
 * Commands data struct
 */

struct command_s {
	char *name;
	int (*func)(struct command_s *cmd, int argc, char *argv[]);
	char *usage;
};

/*
 * Misc macros
 */

#define stringify(s)	tostring(s)
#define tostring(s)	#s
#define command(_name, _usage)				\
		{					\
			.name   = stringify(_name),	\
			.func   = cmd_##_name,		\
			.usage  = _usage,		\
		}

/*
 * Exported variables & functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "macros.h"
#include "utils.h"

#define _YES_I_KNOW_USING_OLD_CAENRFID_API_IS_EVIL
#include <caenrfid.h>
#include <caenrfid_old.h>

/* FIXME: only one client at time for the moment! */
caenrfid_handle_t handle;

extern struct command_s commands_list[];
extern int execute_command(char *line);
