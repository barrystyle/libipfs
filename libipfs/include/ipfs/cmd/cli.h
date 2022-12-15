#pragma once

/**
 * Helps parse the command line.
 */

/**
 * A structure to hold the command line arguments
 */
struct CliArguments {
	int argc;
	char** argv;
	int verb_index;
	char* config_dir;
};

struct CliArguments* cli_arguments_new(int argc, char** argv);

void cli_arguments_free(struct CliArguments* args);
