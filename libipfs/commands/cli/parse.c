#include <stdlib.h>

#include "libp2p/utils/logger.h"
#include "commands/cli/parse.h"


/***
 * Parse command line arguments, and place them in a Command struct
 * @param argc number of arguments
 * @param argv arguments
 * @param inStream an incoming stream (not implemented yet)
 * @param cmd the Command struct to allocate
 * @param request not sure what this is for yet
 * @returns true(1) on success, false(0) otherwise
 */
int cli_parse(int argc, char** argv, FILE* inStream, struct Command** cmd, struct Request* request) {
	*cmd = (struct Command*) malloc(sizeof(struct Command));
	if (*cmd == NULL) {
		libp2p_logger_error("parse", "Unable to allocate memory for the command structure.\n");
		return 0;
	}
	return 0;
}
