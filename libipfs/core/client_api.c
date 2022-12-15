#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#include "core/client_api.h"
#include "multiaddr/multiaddr.h"

/**
 * Determine if the API is running (by attempting to connect to the port)
 * @param local_node the context
 * @returns true(1) on success, false(0) otherwise
 */
int api_running(struct IpfsNode* local_node) {
	struct MultiAddress* my_multiaddress = multiaddress_new_from_string(local_node->repo->config->addresses->api);
	char* ip = NULL;
	int portno = 0;

	if (my_multiaddress == NULL) {
		return 0;
	}

	portno = multiaddress_get_ip_port(my_multiaddress);
	multiaddress_get_ip_address(my_multiaddress, &ip);

	multiaddress_free(my_multiaddress);

	if (ip == NULL)
		return 0;

	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		free(ip);
		return 0;
	}

    server = gethostbyname(ip);
    free(ip);

	if (server == NULL) {
		return 0;
	}

	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	memmove(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
	serv_addr.sin_port = htons(portno);
	int retVal = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	close(sockfd);
	return retVal >= 0;
}
