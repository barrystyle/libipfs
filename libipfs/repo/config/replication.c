#include <stdlib.h>

#include "multiaddr/multiaddr.h"
#include "libp2p/utils/linked_list.h"
#include "libp2p/utils/logger.h"
#include "repo/config/replication.h"

/**
 * Allocate a new ReplicationPeer struct
 * @returns the new struct
 */
struct ReplicationPeer* repo_config_replication_peer_new() {
	struct ReplicationPeer* rp = (struct ReplicationPeer*) malloc(sizeof(struct ReplicationPeer));
	if (rp != NULL) {
		rp->lastConnect = 0;
		rp->lastJournalTime = 0;
		rp->peer = NULL;
	}
	return rp;
}

/***
 * Free the resources of a ReplicationPeer
 * @param rp the ReplicationPeer to free
 * @returns true(1)
 */
int repo_config_replication_peer_free(struct ReplicationPeer* rp) {
	if (rp != NULL) {
		// we allocated the peer structure, so we must remove it
		libp2p_peer_free(rp->peer);
		free(rp);
	}
	return 1;
}

/***
 * allocate memory and initialize the replication struct
 * @param replication a pointer to the struct to be allocated
 * @returns true(1) on success, false(0) otherwise
 */
int repo_config_replication_new(struct Replication** replication) {
	*replication = (struct Replication*)malloc(sizeof(struct Replication));
	if (*replication == NULL)
		return 0;
	struct Replication* out = *replication;
	out->announce_minutes = 0;
	out->replication_peers = NULL;
	return 1;
}

/***
 * Frees memory of a replication struct
 * @param replication the replication struct
 * @returns true(1);
 */
int repo_config_replication_free(struct Replication* replication) {
	if (replication != NULL) {
		// free the vector
		if (replication->replication_peers != NULL) {
			for(int i = 0; i < replication->replication_peers->total; i++) {
				struct ReplicationPeer* currAddr = (struct ReplicationPeer*)libp2p_utils_vector_get(replication->replication_peers, i);
				repo_config_replication_peer_free(currAddr);
			}
			libp2p_utils_vector_free(replication->replication_peers);
		}
		// free the struct
		free(replication);
	}
	return 1;
}

/***
 * Given a peer, return the ReplicationPeer record
 * @param replication the context
 * @param key the peer to look for
 * @returns the ReplicationPeer struct, or NULL if not found
 */
struct ReplicationPeer* repo_config_get_replication_peer(struct Replication* replication, struct Libp2pPeer* key) {
	if (replication != NULL) {
		if (replication->replication_peers != NULL) {
			for(int i = 0; i < replication->replication_peers->total; i++) {
				struct ReplicationPeer* confAddr = (struct ReplicationPeer*) libp2p_utils_vector_get(replication->replication_peers, i);
				if (libp2p_peer_matches_id(confAddr->peer, (unsigned char*)key->id, key->id_size)) {
					return confAddr;
				}
			}
		}
	}
	return NULL;
}

/***
 * Determines if this peer is one of our approved replication nodes
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns true(1) if this peer should be kept syncronized, false(0) otherwise
 */
int repo_config_replication_approved_node(struct Replication* replication, struct Libp2pPeer* peer) {
	if (replication != NULL) {
		if (repo_config_get_replication_peer(replication, peer) != NULL) {
			return 1;
		}
	}
	return 0;
}

/**
 * Determine the last time a replication was successful for this peer (at least we sent it something without error)
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns the time since the last replication, or the announce time if we have no record
 */
/*
unsigned long long repo_config_replication_last_attempt(struct Replication* replication, struct Libp2pPeer* peer) {
	struct ReplicationPeer* rp = repo_config_get_replication_peer(replication, peer);
	if (rp != NULL) {
		return rp->lastConnect;
	}
	return 0;
}
*/

/***
 * Determine the last journal record time that was sent to this peer
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns the time of the last journal entry successfully sent
 */
unsigned long long repo_config_replication_last_journal_time(struct Replication* replication, struct Libp2pPeer* peer) {
	struct ReplicationPeer* rp = repo_config_get_replication_peer(replication, peer);
	if (rp != NULL) {
		return rp->lastJournalTime;
	}
	return 0;
}
