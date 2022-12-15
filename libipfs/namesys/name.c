/**
 * Handles the command line options for "ipfs name"
 */
#include <stdlib.h>
#include "libp2p/utils/logger.h"
#include "libp2p/utils/vector.h"
#include "core/ipfs_node.h"
#include "cmd/cli.h"
#include "core/http_request.h"

/***
 * Publish IPNS name
 */
int ipfs_name_publish(struct IpfsNode* local_node, char* name, char **response, size_t *response_size) {
	// call api.
	struct HttpRequest* request = ipfs_core_http_request_new();
	if (request == NULL)
		return 0;
	request->command = "name";
	request->sub_command = "publish";
	libp2p_utils_vector_add(request->arguments, name);
	int retVal = ipfs_core_http_request_post(local_node, request, response, response_size, "", 0);
	ipfs_core_http_request_free(request);
	return retVal;
}

/***
 * Resolve IPNS name
 */
int ipfs_name_resolve(struct IpfsNode* local_node, char* name, char **response, size_t *response_size) {
	// ask api
	const char prefix[] = "/ipns/";
	char *ipns = NULL;
	struct HttpRequest* request = ipfs_core_http_request_new();
	if (request == NULL)
		return 0;
	request->command = "name";
	request->sub_command = "resolve";
	if (memcmp(name, prefix, sizeof(prefix)-1)!=0) {
		ipns = malloc(sizeof(prefix) + strlen(name));
		if (ipns) {
			strcpy(ipns, prefix);
			strcat(ipns, name);
			name = ipns;
		}
	}
	libp2p_utils_vector_add(request->arguments, name);
	int retVal = ipfs_core_http_request_post(local_node, request, response, response_size, "", 0);
	if (ipns) {
		free(ipns);
	}
	ipfs_core_http_request_free(request);
	return retVal;
}

/**
 * We received a cli command "ipfs name". Do the right thing.
 * @param argc number of arguments on the command line
 * @param argv actual command line arguments
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_name(struct CliArguments* args) {
	int retVal = 0;
	struct IpfsNode* client_node = NULL;

	if (args->argc < (args->verb_index + 2)) {
		libp2p_logger_error("name", "Not enough command line arguments. Should be \"name resolve\" or \"name publish\".\n");
		goto exit;
	}

	char* which = args->argv[args->verb_index+1];
	char* path = args->argv[args->verb_index+2];

	// make sure API is running
	if (!ipfs_node_offline_new(args->config_dir, &client_node)) {
		libp2p_logger_error("name", "Unable to create offline node.\n");
		goto exit;
	}
	if (client_node->mode != MODE_API_AVAILABLE) {
		libp2p_logger_error("name", "API must be running.\n");
		goto exit;
	}

	char *response = NULL;
	size_t response_size;
	// determine what we're doing
	if (strcmp(which, "publish") == 0) {
		retVal = ipfs_name_publish(client_node, path, &response, &response_size);
	} else if (strcmp(which, "resolve") == 0) {
		retVal = ipfs_name_resolve(client_node, path, &response, &response_size);
	} else {
		libp2p_logger_error("name", "Nothing found on command line. Should be \"name resolve\" or \"name publish\".\n");
		goto exit;
	}
	if (response != NULL && response_size > 0) {
		fwrite(response, 1, response_size, stdout);
		free(response);
	}

	exit:
	// shut everything down
	ipfs_node_free(client_node);

	return retVal;
}
