CC=gcc

CFLAGS= -O2 -I./include -Wno-stringop-overflow
LDFLAGS= -lpthread -lm

SOURCES= \
	mbedtls/md5.c \
	mbedtls/ssl_tls.c \
	mbedtls/pkwrite.c \
	mbedtls/xtea.c \
	mbedtls/sha256.c \
	mbedtls/blowfish.c \
	mbedtls/ccm.c \
	mbedtls/asn1parse.c \
	mbedtls/md.c \
	mbedtls/x509_create.c \
	mbedtls/ssl_cookie.c \
	mbedtls/ecjpake.c \
	mbedtls/aesni.c \
	mbedtls/cipher.c \
	mbedtls/entropy.c \
	mbedtls/ctr_drbg.c \
	mbedtls/debug.c \
	mbedtls/entropy_poll.c \
	mbedtls/x509_crl.c \
	mbedtls/pem.c \
	mbedtls/ecp_curves.c \
	mbedtls/md4.c \
	mbedtls/dhm.c \
	mbedtls/certs.c \
	mbedtls/pkparse.c \
	mbedtls/ssl_srv.c \
	mbedtls/x509write_crt.c \
	mbedtls/sha1.c \
	mbedtls/des.c \
	mbedtls/md2.c \
	mbedtls/error.c \
	mbedtls/havege.c \
	mbedtls/aes.c \
	mbedtls/ecdh.c \
	mbedtls/hmac_drbg.c \
	mbedtls/version.c \
	mbedtls/pkcs11.c \
	mbedtls/x509_csr.c \
	mbedtls/threading.c \
	mbedtls/oid.c \
	mbedtls/sha512.c \
	mbedtls/ssl_cli.c \
	mbedtls/arc4.c \
	mbedtls/gcm.c \
	mbedtls/camellia.c \
	mbedtls/ssl_cache.c \
	mbedtls/ecp.c \
	mbedtls/pk.c \
	mbedtls/version_features.c \
	mbedtls/pk_wrap.c \
	mbedtls/x509.c \
	mbedtls/rsa.c \
	mbedtls/x509write_csr.c \
	mbedtls/cmac.c \
	mbedtls/ripemd160.c \
	mbedtls/asn1write.c \
	mbedtls/memory_buffer_alloc.c \
	mbedtls/bignum.c \
	mbedtls/ssl_ticket.c \
	mbedtls/cipher_wrap.c \
	mbedtls/base64.c \
	mbedtls/ssl_ciphersuites.c \
	mbedtls/pkcs5.c \
	mbedtls/padlock.c \
	mbedtls/x509_crt.c \
	mbedtls/md_wrap.c \
	mbedtls/timing.c \
	mbedtls/ecdsa.c \
	mbedtls/net_sockets.c \
	mbedtls/pkcs12.c \
	mbedtls/platform.c \
	crypto/encoding/x509.c \
	crypto/encoding/base32.c \
	crypto/encoding/base58.c \
	crypto/encoding/base64.c \
	crypto/encoding/base16.c \
	crypto/sha256.c \
	crypto/ephemeral.c \
	crypto/key.c \
	crypto/peerutils.c \
	crypto/sha1.c \
	crypto/aes.c \
	crypto/sha512.c \
	crypto/rsa.c \
	multiaddr/varint.c \
	multiaddr/varhexutils.c \
	multiaddr/protocols.c \
	multiaddr/protoutils.c \
	multiaddr/base58.c \
	multiaddr/multiaddr.c \
	multihash/errors.c \
	multihash/hashes.c \
	multihash/multihash.c \
	protobuf/varint.c \
	protobuf/protobuf.c \
	swarm/swarm.c \
	db/filestore.c \
	db/datastore.c \
	identify/identify.c \
	secio/propose.c \
	secio/exchange.c \
	secio/secio.c \
	os/memstream.c \
	os/utils.c \
	os/timespec.c \
	peer/providerstore.c \
	peer/peer.c \
	peer/peerstore.c \
	net/connectionstream.c \
	net/server.c \
	net/stream.c \
	net/tcp.c \
	net/socket.c \
	net/multistream.c \
	net/udp.c \
	net/protocol.c \
	net/sctp.c \
	yamux/session.c \
	yamux/stream.c \
	yamux/frame.c \
	yamux/yamux.c \
	conn/tcp_transport_dialer.c \
	conn/transport_dialer.c \
	conn/session.c \
	conn/connection.c \
	conn/dialer.c \
	record/message_handler.c \
	record/message.c \
	record/record.c \
	routing/dht_protocol.c \
	routing/dht.c \
	routing/kademlia.c \
	hashmap/hashmap.c \
	utils/urlencode.c \
	utils/linked_list.c \
	utils/vector.c \
	utils/thread_pool.c \
	utils/string_list.c \
	utils/logger.c \
	utils/threadsafe_buffer.c

OBJECTS=$(SOURCES:.c=.o)
OUTPUT=libp2p.a

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	ar rc $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.a
	rm -f */*.o
	rm -f */*/*.o
