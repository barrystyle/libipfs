#include <stdlib.h>
#include <string.h>

#include "protobuf/protobuf.h"
#include "libp2p/secio/propose.h"
#include "libp2p/crypto/key.h"

//                                                        rand                   pubkey                    exchanges                   ciphers                   hashes
enum WireType secio_propose_message_fields[] = { WIRETYPE_LENGTH_DELIMITED, WIRETYPE_LENGTH_DELIMITED, WIRETYPE_LENGTH_DELIMITED, WIRETYPE_LENGTH_DELIMITED, WIRETYPE_LENGTH_DELIMITED };

struct Propose* libp2p_secio_propose_new() {
	struct Propose* retVal = (struct Propose*)malloc(sizeof(struct Propose));
	if (retVal == NULL)
		return NULL;
	memset((void*)retVal, 0, sizeof(struct Propose));
	return retVal;
}

void libp2p_secio_propose_free( struct Propose* in) {
	if (in != NULL) {
		if (in->rand != NULL)
			free(in->rand);
		if (in->public_key != NULL)
			free(in->public_key);
		if (in->ciphers != NULL)
			free(in->ciphers);
		if (in->exchanges != NULL)
			free(in->exchanges);
		if (in->hashes != NULL)
			free(in->hashes);
		free(in);
		in = NULL;
	}
}

int libp2p_secio_propose_set_property(void** to, size_t* to_size, const void* from, size_t from_size) {
	if (*to != NULL)
		free(*to);
	*to = (void*)malloc(from_size);
	if (*to == NULL)
		return 0;
	memcpy(*to, from, from_size);
	*to_size = from_size;
	return 1;
}

/**
 * retrieves the approximate size of an encoded version of the passed in struct
 * @param in the struct to look at
 * @reutrns the size of buffer needed
 */
size_t libp2p_secio_propose_protobuf_encode_size(struct Propose* in) {
	size_t retVal = 0;
	retVal += 11 + in->rand_size;
	retVal += 11 + in->public_key_size;
	retVal += 11 + in->ciphers_size;
	retVal += 11 + in->exchanges_size;
	retVal += 11 + in->hashes_size;
	return retVal;
}

/**
 * Encode the struct Propose in protobuf format
 * @param in the struct to be encoded
 * @param buffer where to put the results
 * @param max_buffer_length the max to write
 * @param bytes_written how many bytes were written to the buffer
 * @returns true(1) on success, otherwise false(0)
 */
int libp2p_secio_propose_protobuf_encode(struct Propose* in, unsigned char* buffer, size_t max_buffer_length, size_t* bytes_written) {
	*bytes_written = 0;
	size_t bytes_used;
	// rand
	if (!protobuf_encode_length_delimited(1, secio_propose_message_fields[0], (char*)in->rand, in->rand_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	// public key
	if (!protobuf_encode_length_delimited(2, secio_propose_message_fields[1], (char*)in->public_key, in->public_key_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	// exchanges
	if (!protobuf_encode_length_delimited(3, secio_propose_message_fields[2], in->exchanges, in->exchanges_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	// ciphers
	if (!protobuf_encode_length_delimited(4, secio_propose_message_fields[3], in->ciphers, in->ciphers_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	// hashes
	if (!protobuf_encode_length_delimited(5, secio_propose_message_fields[4], in->hashes, in->hashes_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	return 1;
}

/**
 * Turns a protobuf array into a Propose struct
 * @param buffer the protobuf array
 * @param buffer_length the length of the buffer
 * @param out a pointer to the new struct Propose NOTE: this method allocates memory
 * @returns true(1) on success, otherwise false(0)
 */
int libp2p_secio_propose_protobuf_decode(const unsigned char* buffer, size_t buffer_length, struct Propose** out) {
	size_t pos = 0;
	int retVal = 0, got_something = 0;;

	if ( (*out = libp2p_secio_propose_new()) == NULL)
		goto exit;

	while(pos < buffer_length) {
		size_t bytes_read = 0;
		int field_no;
		enum WireType field_type;
		if (protobuf_decode_field_and_type(&buffer[pos], buffer_length, &field_no, &field_type, &bytes_read) == 0) {
			goto exit;
		}
		if (field_no < 1 || field_no > 5) {
			fprintf(stderr, "Invalid character in Propose protobuf at position %lu. Value: %02x\n", pos, buffer[pos]);
		}
		pos += bytes_read;
		switch(field_no) {
			case (1): // rand
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->rand), &((*out)->rand_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				got_something = 1;
				break;
			case (2): // public key
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->public_key), &((*out)->public_key_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				got_something = 1;
				break;
			case (3): // exchanges
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->exchanges), &((*out)->exchanges_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				got_something = 1;
				break;
			case (4): // ciphers
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->ciphers), &((*out)->ciphers_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				got_something = 1;
				break;
			case (5): // hashes
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->hashes), &((*out)->hashes_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				got_something = 1;
				break;
		}
	}

	retVal = got_something;

exit:
	if (retVal == 0) {
		libp2p_secio_propose_free(*out);
	}
	return retVal;
}

/***
 * Build a propose structure for sending to the remote client
 * @param nonce a 16 byte nonce, previously defined
 * @param rsa_key the local RSA key
 * @param supportedExchanges a comma separated list of supported exchange protocols
 * @param supportedCiphers a comma separated list of supported ciphers
 * @param supportedHashes a comma separated list of supported hashes
 * @returns an initialized Propose struct, or NULL
 */
struct Propose* libp2p_secio_propose_build(unsigned char nonce[16], struct RsaPrivateKey* rsa_key,
		const char* supportedExchanges, const char* supportedCiphers, const char* supportedHashes) {
	struct Propose* propose = libp2p_secio_propose_new();
	if (propose != NULL) {
		// nonce
		propose->rand = malloc(16);
		memcpy(propose->rand, nonce, 16);
		propose->rand_size = 16;
		// ciphers, exchanges, hashes
		propose->ciphers_size = strlen(supportedCiphers);
		propose->ciphers = malloc(propose->ciphers_size + 1);
		strcpy(propose->ciphers, supportedCiphers);
		propose->exchanges_size = strlen(supportedExchanges);
		propose->exchanges = malloc(propose->exchanges_size + 1);
		strcpy(propose->exchanges, supportedExchanges);
		propose->hashes_size = strlen(supportedHashes);
		propose->hashes = malloc(propose->hashes_size + 1);
		strcpy(propose->hashes, supportedHashes);
		// key
		struct PublicKey pub_key;
		pub_key.type = KEYTYPE_RSA;
		pub_key.data_size = rsa_key->public_key_length;
		pub_key.data = malloc(pub_key.data_size);
		memcpy(pub_key.data, rsa_key->public_key_der, rsa_key->public_key_length);
		propose->public_key_size = libp2p_crypto_public_key_protobuf_encode_size(&pub_key);
		propose->public_key = malloc(propose->public_key_size);
		if (propose->public_key == NULL) {
			free(pub_key.data);
			libp2p_secio_propose_free(propose);
			return NULL;
		}
		if (libp2p_crypto_public_key_protobuf_encode(&pub_key, propose->public_key, propose->public_key_size, &propose->public_key_size) == 0) {
			free(pub_key.data);
			libp2p_secio_propose_free(propose);
			return NULL;
		}
		free(pub_key.data);
	}
	return propose;

}
