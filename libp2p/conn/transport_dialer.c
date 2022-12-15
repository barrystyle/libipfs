#include <stdlib.h>

#include "libp2p/crypto/rsa.h"
#include "libp2p/conn/transport_dialer.h"

struct TransportDialer* libp2p_conn_transport_dialer_new(char* peer_id, struct RsaPrivateKey* private_key) {
	struct TransportDialer* out = (struct TransportDialer*)malloc(sizeof(struct TransportDialer));
	if (out != NULL) {
		out->peer_id = NULL;
		out->private_key = NULL;
		if (peer_id != NULL) {
			out->peer_id = malloc(strlen(peer_id) + 1);
			strcpy(out->peer_id, peer_id);
		}
		if (private_key != NULL) {
			out->private_key = private_key;
		}
	}
	return out;
}

/**
 * free resources from a TransportDialer struct
 * @param in the struct to be freed
 */
void libp2p_conn_transport_dialer_free(struct TransportDialer* in) {
	if (in != NULL) {
		if (in->peer_id != NULL)
			free(in->peer_id);
		//libp2p_crypto_private_key_free(in->private_key);
		free(in);
	}
}

/**
 * Given a list of dialers, find the appropriate dialer for this multiaddress
 * @param transport_dialers a list of dialers
 * @param multiaddr the address
 * @returns a connection, or NULL if no appropriate dialer was found
 */
struct Stream* libp2p_conn_transport_dialer_get(const struct Libp2pLinkedList* transport_dialers, const struct MultiAddress* multiaddr) {
	const struct Libp2pLinkedList* current = transport_dialers;
	struct TransportDialer* t_dialer = NULL;
	while (current != NULL) {
		t_dialer = (struct TransportDialer*)current->item;
		if (t_dialer->can_handle(multiaddr))
			break;
		current = current->next;
		t_dialer = NULL;
	}

	if (t_dialer != NULL) {
		return t_dialer->dial(t_dialer, multiaddr);
	}

	return NULL;
}
