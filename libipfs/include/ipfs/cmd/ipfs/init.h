/**
 * Initialize an IPFS repository
 */
#ifndef __CMD_IPFS_INIT_H__
#define __CMD_IPFS_INIT_H__

#include "commands/command.h"

/***
 * Returns a command structure customized for the init command
 * @param command the struct to fill
 * @returns 0 on failure, otherwise 1
 */
int ipfs_cmd_ipfs_init_command_new(struct Command* command);

/***
 * Uninitializes all the dynamic memory caused by get_init_command
 * @param command the struct
 * @returns 0 on failure, otherwise 1
 */
int ipfs_cmd_ipfs_init_command_free(struct Command* command);

/***
 * Parse the command line
 * @param argc the number of arguments
 * @param argv the actual arguments
 * @returns a command structure
 */
struct Command* ipfs_cmd_parse_command_line(int argc, char** argv);

#endif
