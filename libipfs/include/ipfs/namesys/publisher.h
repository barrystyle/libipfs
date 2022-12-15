#pragma once

#include "cid/cid.h"
#include "core/ipfs_node.h"
#include "namesys/pb.h"

char* ipns_entry_data_for_sig (struct ipns_entry *entry);
int ipns_selector_func (int *idx, struct ipns_entry ***recs, char *k, char **vals);
int ipns_select_record (int *idx, struct ipns_entry **recs, char **vals);
// ipns_validate_ipns_record implements ValidatorFunc and verifies that the
// given 'val' is an IpnsEntry and that that entry is valid.
int ipns_validate_ipns_record (char *k, char *val);

/**
 * Store the hash locally, and notify the network
 *
 * @param local_node the context
 * @param path the "/ipfs/" or "/ipns" path
 * @returns true(1) on success, false(0) otherwise
*/
int ipfs_namesys_publisher_publish(struct IpfsNode* local_node, char* path);
