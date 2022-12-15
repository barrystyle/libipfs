#pragma once
/**
 * Piggyback on the datastore to access the journal entries
 */

#include <stdint.h>
#include <stdlib.h>

#include "lmdb.h"
#include "libp2p/db/datastore.h"
#include "repo/fsrepo/lmdb_cursor.h"

struct JournalRecord {
	unsigned long long timestamp; // the timestamp of the file
	int pin; // true if it is to be stored, false if it is to be deleted
	int pending; // true if we do not have this file yet
	uint8_t *hash; // the hash of the block (file)
	size_t hash_size; // the size of the hash
};

struct JournalRecord* lmdb_journal_record_new();

int lmdb_journal_record_free(struct JournalRecord* rec);

/**
 * Open a cursor to the journalstore table
 * @param db_handle a handle to the database (an MDB_env pointer)
 * @param cursor where to place the results
 * @returns true(1) on success, false(0) otherwise
 */
int lmdb_journalstore_cursor_open(void* db_handle, struct lmdb_trans_cursor **cursor, struct MDB_txn *trans_to_use);

/**
 * Read a record from the cursor
 */
int lmdb_journalstore_cursor_get(struct lmdb_trans_cursor *cursor, enum DatastoreCursorOp op, struct JournalRecord** record);

/***
 * Write the record at the cursor
 * @param crsr the cursor
 * @param journal_record the record to write
 * @returns true(1) on success, false(0) otherwise
 */
int lmdb_journalstore_cursor_put(struct lmdb_trans_cursor *crsr, struct JournalRecord* journal_record);

/**
 * Close the cursor
 */
int lmdb_journalstore_cursor_close(struct lmdb_trans_cursor *cursor, int commitTransaction);

int journal_record_free(struct JournalRecord* rec);

int lmdb_journalstore_journal_add(struct lmdb_trans_cursor *journalstore_cursor, struct JournalRecord *journalstore_record);

/***
 * Attempt to get a specific record identified by its timestamp and bytes
 * @param handle a handle to the database engine
 * @param journalstore_cursor the cursor (will be returned as a cursor that points to the record found
 * @param journalstore_record where to put the results (can pass null). If data is within the struct, will use it as search criteria
 * @returns true(1) on success, false(0) otherwise
 */
int lmdb_journalstore_get_record(void* handle, struct lmdb_trans_cursor *journalstore_cursor, struct JournalRecord **journalstore_record);

/***
 * Convert the JournalRec struct into a lmdb key and lmdb value
 * @param journal_record the record to convert
 * @param db_key where to store the key information
 * @param db_value where to store the value information
 */
int lmdb_journalstore_build_key_value_pair(const struct JournalRecord* journal_record, struct MDB_val* db_key, struct MDB_val *db_value);

