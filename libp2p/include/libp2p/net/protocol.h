#pragma once
#include "libp2p/conn/session.h"
#include "libp2p/utils/vector.h"
#include "libp2p/net/stream.h"

/***
 * An "interface" for different IPFS protocols
 */
struct Libp2pProtocolHandler {
	/**
	 * A protocol dependent context (often an IpfsNode pointer, but libp2p doesn't know about that)
	 */
	void* context;
	/**
	 * Determines if this protocol can handle the incoming message
	 * @param incoming the incoming data
	 * @param incoming_size the size of the incoming data buffer
	 * @returns true(1) if it can handle this message, false(0) if not
	 */
	int (*CanHandle)(const struct StreamMessage* msg);
	/***
	 * Handles the message
	 * @param incoming the incoming data buffer
	 * @param incoming_size the size of the incoming data buffer
	 * @param stream the incoming stream
	 * @param protocol_context the protocol-dependent context
	 * @returns 0 if the caller should not continue looping, <0 on error, >0 on success
	 */
	int (*HandleMessage)(const struct StreamMessage* msg, struct Stream* stream, void* protocol_context);

	/**
	 * Shutting down. Clean up any memory allocations
	 * @param protocol_context the context
	 * @returns true(1)
	 */
	int (*Shutdown)(void* protocol_context);
};

/**
 * Allocate resources for a new Libp2pProtocolHandler
 * @returns an allocated struct
 */
struct Libp2pProtocolHandler* libp2p_protocol_handler_new();

/***
 * Release resources of a protocol handler
 * @param handler the handler to free
 */
void libp2p_protocol_handler_free(struct Libp2pProtocolHandler* handler);

/***
 * Handle an incoming message
 * @param message the incoming message
 * @param stream the incoming connection
 * @param handlers a Vector of protocol handlers
 * @returns -1 on error, 0 on protocol upgrade, 1 on success
 */
int libp2p_protocol_marshal(struct StreamMessage* message, struct Stream* stream, struct Libp2pVector* protocol_handlers);

/***
 * Shut down all protocol handlers and free vector
 * @param handlers vector of Libp2pProtocolHandler
 * @returns true(1)
 */
int libp2p_protocol_handlers_shutdown(struct Libp2pVector* handlers);

/***
 * Check to see if this is a valid protocol
 * @param msg the message
 * @param handlers the vector of handlers
 */
int libp2p_protocol_is_valid_protocol(struct StreamMessage* msg, struct Libp2pVector* handlers);

/***
 * Retrieve the correct protocol handlder for a particular protocol id
 * @param protocol_handlers the collection of protocol handlers
 * @param id the protocol id
 * @returns a protocol handler that can handle id (or NULL if none found)
 */
const struct Libp2pProtocolHandler* libp2p_protocol_get_handler(struct Libp2pVector* protocol_handlers, const char* id);
