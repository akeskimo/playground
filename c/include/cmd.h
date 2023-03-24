#ifndef _CMD_H
#define _CMD_H

#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char *opt_help;
	const struct option longopt;
} prog_optlong_t;

/**
 * @brief Create new command line parser.
 * 
 */
static inline void parse_opts(int argc, char **argv, prog_optlong_t *opt) {
	int c;
	int optidx = 0;

	const struct option longopts[] = {
		{"help", no_argument, 0, 0},
		{"duce", required_argument, 0, 0}
	};

	while ((c = getopt_long(argc, argv, "", longopts, &optidx)) != -1) {
		switch(c) {
		case 0:
			printf("option: %s\n", longopts[optidx].name);
			break;
		case '?':
			break;
		default:
			printf("unsupport option: 0%o\n", c);
		}
	}

	if (optind < argc) {
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

#endif  /* _CMD_H */
