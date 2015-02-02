#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <wordexp.h>

#include "client.h"

int fd = STDOUT_FILENO;
unsigned short session_id;
unsigned short replay_id;

/*
 * Parse and execute user comnmands
 */

struct command_s *find_command(char *str)
{
        struct command_s *ptr;

        if (str == NULL || str[0] == '\0')
                return NULL;

        for (ptr = commands_list; ptr->name; ptr++)
                if (strcmp(ptr->name, str) == 0)
                        return ptr;

        return NULL;
}

int execute_command(char *line)
{
        wordexp_t result;
        struct command_s *command;

        /* Expand the string for the program to run.  */
        switch (wordexp(line, &result, 0)) {
        case 0: /* success */
                break;

        case WRDE_NOSPACE:
                /* If the error was `WRDE_NOSPACE', then perhaps part of the
                 * result was allocated
                 */
                wordfree(&result);

                /* Fall through! */

        default:        /* Some other error */
                return -1;
        }

	if (!result.we_wordv[0])	/* no commands at all! */
		return 0;

        /* Try to find the command */
        command = find_command(result.we_wordv[0]);
        if (command == NULL) {
                PERR("no such command");
                return -1;
        }

        /* Execute the command */
        return command->func(command, result.we_wordc, result.we_wordv);
}


/*
 * Main
 */

static void usage(void)
{
        fprintf(stderr, "usage: %s [<options>]\n", NAME);
        fprintf(stderr, "   where <options> are:\n");
        fprintf(stderr, "      [-h | --help]          : show this help\n");

        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
        char c;
        struct option long_options[] = {
                { "help",       no_argument, 0, 'h' },
        };

        int n;
        size_t len = 0;
        char *p, *line = NULL;

        /* Check the command line */
        while (1) {
                /* `getopt_long' stores the option index here. */
                int option_index = 0;

                c = getopt_long(argc, argv, "h",
                                 long_options, &option_index);

                /* Detect the end of the options. */
                if (c == -1)
                        break;

                switch (c) {
                case 'h' :      /* --help */
                        usage();

                case ':' :
                        /* "getopt_long" already printed an error message */
                        exit(EXIT_FAILURE);

                case '?' :
                        /* "getopt_long" already printed an error message */
                        exit(EXIT_FAILURE);

                default :
                        exit(EXIT_FAILURE);
                }
        }

        /* Loop reading and executing lines until the user quits. */
        while (1) {
                        /* Read the command line */
                        n = getline(&line, &len, stdin);
                        if (n < 0) {
                                if (feof(stdin))
                                        break;  /* nothing to read */

                                PERR("cannot read commands!");
                                exit(EXIT_FAILURE);
                        }

                        /* Add string terminator */
                        p = index(line, '\n');
                        if (p)
                                *p = '\0';

                        /* Parse and execute the command */
                        execute_command(line);
        }

	return 0;
}
