#pragma once

#include "cmd/cli.h"

/***
 * Publish IPNS name
 */
int ipfs_name_publish(struct IpfsNode* local_node, char* name, char **response, size_t *response_size);

/***
 * Resolve IPNS name
 */
int ipfs_name_resolve(struct IpfsNode* local_node, char* name, char **response, size_t *response_size);

/**
 * We received a cli command "ipfs name". Do the right thing.
 * @param argc number of arguments on the command line
 * @param argv actual command line arguments
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_name(struct CliArguments* args);
