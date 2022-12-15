#include <stdlib.h>
#include <string.h>

#include "libp2p/utils/logger.h"
#include "namesys/resolver.h"

/**
 * The opposite of publisher.c
 *
 * These are the resources for resolving an IPNS name, turning it into an ipfs path
 */

/**
 * Determine if the incoming path is in ipns format
 * @param path the path to check
 * @returns true(1) if the path begins with "/ipns/"
 */
int is_ipns_string(char* path) {
	if (path == NULL)
		return 0;
	if (strstr(path, "/ipns/") == path)
		return 1;
	return 0;
}

/***
 * Resolve an IPNS name, only to its next step
 * @param local_node the context
 * @param path the ipns_path (i.e. "ipns/Qm12345...")
 * @param results where to store the results (i.e. "ipns/Qm5678...")
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_namesys_resolver_resolve_once(struct IpfsNode* local_node, const char* path, char** results) {
	struct Cid* cid = NULL;
	if (!ipfs_cid_decode_hash_from_ipfs_ipns_string(path, &cid)) {
		return 0;
	}

	// look locally
	struct DatastoreRecord* record;
	if (local_node->repo->config->datastore->datastore_get(cid->hash, cid->hash_length, &record, local_node->repo->config->datastore)) {
		// we are able to handle this locally... return the results
		*results = (char*) malloc(record->value_size + 1);
		if (*results == NULL) {
			ipfs_cid_free(cid);
			return 0;
		}
		memset(*results, 0, record->value_size + 1);
		memcpy(*results, record->value, record->value_size);
		ipfs_cid_free(cid);
		return 1;
	}

	//TODO: ask the network
	ipfs_cid_free(cid);
	return 0;
}

/**
 * Resolve an IPNS name.
 * NOTE: if recursive is set to false, the result could be another ipns path
 * @param local_node the context
 * @param path the ipns path (i.e. "/ipns/Qm12345..")
 * @param recursive true to resolve until the result is not ipns, false to simply get the next step in the path
 * @param result the results (i.e. "/ipfs/QmAb12CD...")
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_namesys_resolver_resolve(struct IpfsNode* local_node, const char* path, int recursive, char** results) {
	char* result = NULL;
	char* current_path = (char*) malloc(strlen(path) + 1);
	if (current_path == NULL) {
		return 0;
	}
	strcpy(current_path, path);

	// if we go more than 10 deep, bail
	int counter = 0;

	do {
		if (counter > 10) {
			libp2p_logger_error("resolver", "Resolver looped %d times. Infinite loop? Last result: %s.\n", counter, current_path);
			free(current_path);
			return 0;
		}
		// resolve the current path
		if (!ipfs_namesys_resolver_resolve_once(local_node, current_path, &result)) {
			libp2p_logger_error("resolver", "Resolver returned false searching for %s.\n", current_path);
			free(current_path);
			return 0;
		}
		// result will not be NULL
		free(current_path);
		current_path = (char*) malloc(strlen(result)+1);
		if (current_path != NULL)
			strcpy(current_path, result);
		free(result);
		counter++;
	} while(recursive && is_ipns_string(current_path));

	*results = current_path;
	return 1;
}
