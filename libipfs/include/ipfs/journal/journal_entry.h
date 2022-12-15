#pragma once

/**
 * A journal entry protobuf
 */

#include <stdlib.h>
#include <stdint.h>

struct JournalEntry {
	unsigned long long timestamp;
	uint8_t pin;
	uint8_t *hash;
	size_t hash_size;
};

struct JournalEntry* ipfs_journal_entry_new();

int ipfs_journal_entry_free(struct JournalEntry* entry);

/**
 * Determine the maximum size of a protobuf'd JournalEntry
 */
int ipfs_journal_entry_encode_size(struct JournalEntry* entry);

/***
 * Protobuf the journal entry
 * @param entry the JournalEntry to protobuf
 * @param buffer where to place the results
 * @param max_buffer_size the amount of memory allocated for the buffer
 * @param bytes_used the amount of the buffer used
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_journal_entry_encode(struct JournalEntry* entry, uint8_t *buffer, size_t max_buffer_size, size_t *bytes_used);

/***
 * Turn a protobuf'd JournalEntry and turn it into a real JournalEntry
 * @param incoming the incoming bytes
 * @param incoming_size the size of the incoming buffer
 * @param results where to put the new JournalEntry
 * @returns true(1) on success, false(0) otherwise
 */
int ipfs_journal_entry_decode(uint8_t *incoming, size_t incoming_size, struct JournalEntry **results);
