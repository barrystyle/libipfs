#pragma once

#include "libp2p/utils/vector.h"
#include "libp2p/peer/peer.h"

struct ReplicationPeer {
	struct Libp2pPeer* peer;
	unsigned long long lastConnect;
	unsigned long long lastJournalTime;
};

struct Replication {
	int announce;
	int announce_minutes;
	struct Libp2pVector* replication_peers;
};

/**
 * Allocate a new ReplicationPeer struct
 * @returns the new struct
 */
struct ReplicationPeer* repo_config_replication_peer_new();

/***
 * Free the resources of a ReplicationPeer
 * @param rp the ReplicationPeer to free
 * @returns true(1)
 */
int repo_config_replication_peer_free(struct ReplicationPeer* rp);

/***
 * allocate memory and initialize the replication struct
 * @param replication a pointer to the struct to be allocated
 * @returns true(1) on success, false(0) otherwise
 */
int repo_config_replication_new(struct Replication** replication);

/***
 * Frees memory of a replication struct
 * @param replication the replication struct
 * @returns true(1);
 */
int repo_config_replication_free(struct Replication* replication);

/***
 * Determines if this peer is one of our approved replication nodes
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns true(1) if this peer should be kept syncronized, false(0) otherwise
 */
int repo_config_replication_approved_node(struct Replication* replication, struct Libp2pPeer* peer);

/**
 * Determine the last time a replication was successful for this peer (at least we sent it something without error)
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns the time since the last replication, or the announce time if we have no record
 */
unsigned long long repo_config_replication_last_attempt(struct Replication* replication, struct Libp2pPeer* peer);

/***
 * Determine the last journal record time that was sent to this peer
 * @param replication the replication struct
 * @param peer the peer to examine
 * @returns the time of the last journal entry successfully sent
 */
unsigned long long repo_config_replication_last_journal_time(struct Replication* replication, struct Libp2pPeer* peer);

/***
 * Given a peer, return the ReplicationPeer record
 * @param replication the context
 * @param key the peer to look for
 * @returns the ReplicationPeer struct, or NULL if not found
 */
struct ReplicationPeer* repo_config_get_replication_peer(struct Replication* replication, struct Libp2pPeer* key);

