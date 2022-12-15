#pragma once

#include "core/ipfs_node.h"

/**
 * Resolve an IPNS name.
 * NOTE: if recursive is set to false, the result could be another ipns path
 * @param local_node the context
 * @param path the ipns path (i.e. "/ipns/Qm12345..")
 * @param recursive true to resolve until the result is not ipns, false to simply get the next step in the path
 * @param result the results (i.e. "/ipfs/QmAb12CD...")
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_namesys_resolver_resolve(struct IpfsNode* local_node, const char* path, int recursive, char** results);
