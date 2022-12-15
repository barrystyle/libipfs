#pragma once

#include "lmdb.h"

struct lmdb_context {
	MDB_env *db_environment;
	MDB_txn *current_transaction;
	MDB_dbi *datastore_db;
	MDB_dbi *journal_db;
};

struct lmdb_trans_cursor {
	MDB_env* environment;
	MDB_txn* parent_transaction;
	MDB_txn* transaction;
	MDB_dbi* database;
	MDB_cursor* cursor;
};

/**
 * Create a new lmdb_trans_cursor struct
 * @returns a newly allocated trans_cursor struct
 */
struct lmdb_trans_cursor* lmdb_trans_cursor_new();

/***
 * Clean up resources from a lmdb_trans_cursor struct
 * @param in the cursor
 * @returns true(1)
 */
int lmdb_trans_cursor_free(struct lmdb_trans_cursor* in);
