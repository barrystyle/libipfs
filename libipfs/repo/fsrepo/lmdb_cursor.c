#include <stdlib.h>

#include "repo/fsrepo/lmdb_cursor.h"

/**
 * Create a new lmdb_trans_cursor struct
 * @returns a newly allocated trans_cursor struct
 */
struct lmdb_trans_cursor* lmdb_trans_cursor_new() {
	struct lmdb_trans_cursor* out = (struct lmdb_trans_cursor*) malloc(sizeof(struct lmdb_trans_cursor));
	if (out != NULL) {
		out->environment = NULL;
		out->cursor = NULL;
		out->parent_transaction = NULL;
		out->transaction = NULL;
		out->database = NULL;
	}
	return out;
}

/***
 * Clean up resources from a lmdb_trans_cursor struct
 * @param in the cursor
 * @returns true(1)
 */
int lmdb_trans_cursor_free(struct lmdb_trans_cursor* in) {
	if (in != NULL) {
		free(in);
	}
	return 1;
}
