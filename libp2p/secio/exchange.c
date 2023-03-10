#include <stdlib.h>
#include <string.h>

#include "libp2p/secio/exchange.h"
#include "libp2p/crypto/ephemeral.h"
#include "protobuf/protobuf.h"

//                                                  epubkey                      signature
enum WireType secio_exchange_message_fields[] = { WIRETYPE_LENGTH_DELIMITED, WIRETYPE_LENGTH_DELIMITED };


struct Exchange* libp2p_secio_exchange_new() {
	struct Exchange* out = (struct Exchange*)malloc(sizeof(struct Exchange));
	if (out != NULL) {
		out->epubkey = NULL;
		out->epubkey_size = 0;
		out->signature = NULL;
		out->signature_size = 0;
	}
	return out;
}

void libp2p_secio_exchange_free( struct Exchange* in) {
	if (in != NULL) {
		if (in->epubkey != NULL)
			free(in->epubkey);
		if (in->signature != NULL)
			free(in->signature);
		free(in);
	}
}

/**
 * retrieves the approximate size of an encoded version of the passed in struct
 * @param in the struct to look at
 * @reutrns the size of buffer needed
 */
size_t libp2p_secio_exchange_protobuf_encode_size(struct Exchange* in) {
	size_t retVal = 0;
	retVal += 11 + in->epubkey_size;
	retVal += 11 + in->signature_size;
	return retVal;
}

/**
 * Encode the struct Exchange in protobuf format
 * @param in the struct to be encoded
 * @param buffer where to put the results
 * @param max_buffer_length the max to write
 * @param bytes_written how many bytes were written to the buffer
 * @returns true(1) on success, otherwise false(0)
 */
int libp2p_secio_exchange_protobuf_encode(struct Exchange* in, unsigned char* buffer, size_t max_buffer_length, size_t* bytes_written) {
	*bytes_written = 0;
	size_t bytes_used;
	// epubkey
	if (!protobuf_encode_length_delimited(1, secio_exchange_message_fields[0], (char*)in->epubkey, in->epubkey_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	// signature
	if (!protobuf_encode_length_delimited(2, secio_exchange_message_fields[1], (char*)in->signature, in->signature_size, &buffer[*bytes_written], max_buffer_length - *bytes_written, &bytes_used))
		return 0;
	*bytes_written += bytes_used;
	return 1;
}

/**
 * Turns a protobuf array into an Exchange struct
 * @param buffer the protobuf array
 * @param buffer_length the length of the buffer
 * @param out a pointer to the new struct Exchange NOTE: this method allocates memory
 * @returns true(1) on success, otherwise false(0)
 */
int libp2p_secio_exchange_protobuf_decode(unsigned char* buffer, size_t buffer_length, struct Exchange** out) {
	size_t pos = 0;
	int retVal = 0;

	if ( (*out = libp2p_secio_exchange_new()) == NULL)
		goto exit;

	while(pos < buffer_length) {
		size_t bytes_read = 0;
		int field_no;
		enum WireType field_type;
		if (protobuf_decode_field_and_type(&buffer[pos], buffer_length, &field_no, &field_type, &bytes_read) == 0) {
			goto exit;
		}
		pos += bytes_read;
		switch(field_no) {
			case (1): // epubkey
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->epubkey), &((*out)->epubkey_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				break;
			case (2): // signature
				if (protobuf_decode_length_delimited(&buffer[pos], buffer_length - pos, (char**)&((*out)->signature), &((*out)->signature_size), &bytes_read) == 0)
					goto exit;
				pos += bytes_read;
				break;
		}
	}

	retVal = 1;

exit:
	if (retVal == 0) {
		libp2p_secio_exchange_free(*out);
	}

	return retVal;
}

/***
 * Forward declaration
 */
int libp2p_secio_sign(struct PrivateKey* priv, const char* bytes_to_send, size_t bytes_size, uint8_t** signature, size_t* signature_size);

/***
 * Build an exchange object based on passed in values
 * @param local_session the SessionContext
 * @param private_key the local RsaPrivateKey
 * @param bytes_to_be_signed the bytes that should be signed
 * @param bytes_size the length of bytes_to_be_signed
 * @returns an Exchange object or NULL
 */
struct Exchange* libp2p_secio_exchange_build(struct SessionContext* local_session, struct RsaPrivateKey* private_key, const char* bytes_to_be_signed, size_t bytes_size) {
	struct Exchange* exchange_out = libp2p_secio_exchange_new();
	if (exchange_out != NULL) {
		// don't send the first byte (to stay compatible with GO version)
		exchange_out->epubkey = (unsigned char*)malloc(local_session->ephemeral_private_key->public_key->bytes_size - 1);
		if (exchange_out->epubkey == NULL) {
			libp2p_secio_exchange_free(exchange_out);
			return NULL;
		}
		memcpy(exchange_out->epubkey, &local_session->ephemeral_private_key->public_key->bytes[1], local_session->ephemeral_private_key->public_key->bytes_size - 1);
		exchange_out->epubkey_size = local_session->ephemeral_private_key->public_key->bytes_size - 1;

		struct PrivateKey* priv = libp2p_crypto_private_key_new();
		priv->type = KEYTYPE_RSA;
		priv->data = (unsigned char*)private_key->der;
		priv->data_size = private_key->der_length;
		libp2p_secio_sign(priv, bytes_to_be_signed, bytes_size, &exchange_out->signature, &exchange_out->signature_size);
		free(priv);
	}
	return exchange_out;
}
