#include <stdlib.h>
#include <string.h>
#include "cmd/cli.h"

int cli_is_switch(int argc, char** argv, int index) {
	char* to_test = argv[index];
	if (to_test[0] == '-') {
		if (strcmp(to_test, "-c") == 0 || strcmp(to_test, "--config") == 0) {
			return 2;
		}
		return 1;
	}
	return 0;
}


int cli_get_verb_index(struct CliArguments* args) {
	for(int i = 1; i < args->argc; i++) {
		int advance_by_more_than_one = cli_is_switch(args->argc, args->argv, i);
		if (advance_by_more_than_one == 0) {
			// this is the verb
			return i;
		} else {
			if (advance_by_more_than_one == 2) {
				// skip the next one
				i++;
			}
		}
	}
	return 0;
}

char* cli_get_config_dir(struct CliArguments* args) {
	for (int i = 1; i < args->argc; i++) {
		if (args->argv[i][0] == '-') {
			char* param = args->argv[i];
			if ((strcmp(param, "-c") == 0 || strcmp(param, "--config") == 0) && args->argc > i + 1) {
				return args->argv[i+1];
			}
		}
	}
	return NULL;
}


struct CliArguments* cli_arguments_new(int argc, char** argv) {
	struct CliArguments* args = (struct CliArguments*) malloc(sizeof(struct CliArguments));
	if (args != NULL) {
		args->argc = argc;
		args->argv = argv;
		args->verb_index = cli_get_verb_index(args);
		args->config_dir = cli_get_config_dir(args);
	}
	return args;
}

void cli_arguments_free(struct CliArguments* args) {
	free(args);
}
