#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "libp2p/utils/vector.h"

struct JournalMessage {
	unsigned long long current_epoch;
	unsigned long long start_epoch;
	unsigned long long end_epoch;
	struct Libp2pVector* journal_entries;
};

struct JournalMessage* ipfs_journal_message_new();
int ipfs_journal_message_free(struct JournalMessage* message);

/**
 * Determine the maximum size of a protobuf'd JournalMessage
 * @param message the JournalMessage
 * @returns the maximum size of this message in bytes if it were protobuf'd
 */
int ipfs_journal_message_encode_size(struct JournalMessage* message);

/***
 * Protobuf the journal message
 * @param message the JournalMessage to protobuf
 * @param buffer where to place the results
 * @param max_buffer_size the amount of memory allocated for the buffer
 * @param bytes_used the amount of the buffer used
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_journal_message_encode(struct JournalMessage* entry, uint8_t *buffer, size_t max_buffer_size, size_t *bytes_used);

/***
 * Turn a protobuf'd JournalMessage and turn it into a real JournalMessage
 * @param incoming the incoming bytes
 * @param incoming_size the size of the incoming buffer
 * @param results where to put the new JournalMessage
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_journal_message_decode(const uint8_t *incoming, size_t incoming_size, struct JournalMessage **results);
