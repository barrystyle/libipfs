#pragma once
#include <stdio.h>
#include <stdint.h>

#include "libp2p/conn/session.h"
#include "core/ipfs_node.h"
#include "libp2p/net/protocol.h"

/**
 * The journal protocol attempts to keep a journal in sync with other (approved) nodes
 */

/***
 * See if we can handle this message
 * @param incoming the incoming message
 * @param incoming_size the size of the incoming message
 * @returns true(1) if the protocol in incoming is something we can handle. False(0) otherwise.
 */
int ipfs_journal_can_handle(const struct StreamMessage* msg);

/**
 * Clean up resources used by this handler
 * @param context the context to clean up
 * @returns true(1)
 */
int ipfs_journal_shutdown_handler(void* context);

/***
 * Handles a message
 * @param incoming the message
 * @param incoming_size the size of the message
 * @param session_context details of the remote peer
 * @param protocol_context in this case, an IpfsNode
 * @returns 0 if the caller should not continue looping, <0 on error, >0 on success
 */
int ipfs_journal_handle_message(const struct StreamMessage* msg, struct Stream* stream, void* protocol_context) ;

/***
 * Build the protocol handler struct for the Journal protocol
 * @param local_node what to stuff in the context
 * @returns the protocol handler
 */
struct Libp2pProtocolHandler* ipfs_journal_build_protocol_handler(const struct IpfsNode* local_node);

/***
 * Send a journal message to a remote peer
 * @param replication_peer the peer to send it to
 * @returns true(1) on success, false(0) otherwise.
 */
int ipfs_journal_sync(struct IpfsNode* local_node, struct ReplicationPeer* replication_peer);
