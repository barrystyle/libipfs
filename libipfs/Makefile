CC=gcc

CFLAGS= -O2 -I./ -I./include -I./include/ipfs -I../libp2p/include -I../liblmdb/include -Wno-stringop-overflow

LDFLAGS= -lpthread -lm

SOURCES= \
	journal/journal.c \
	journal/journal_entry.c \
	journal/journal_message.c \
	unixfs/unixfs.c \
	core/builder.c \
	core/bootstrap.c \
	core/net.c \
	core/http_request.c \
	core/client_api.c \
	core/swarm.c \
	core/ping.c \
	core/api.c \
	core/null.c \
	core/ipfs_node.c \
	core/daemon.c \
	flatfs/flatfs.c \
	exchange/bitswap/message.c \
	exchange/bitswap/peer_request_queue.c \
	exchange/bitswap/want_manager.c \
	exchange/bitswap/network.c \
	exchange/bitswap/wantlist_queue.c \
	exchange/bitswap/bitswap.c \
	exchange/bitswap/engine.c \
	datastore/key.c \
	datastore/ds_helper.c \
	repo/fsrepo/fs_repo.c \
	repo/fsrepo/lmdb_datastore.c \
	repo/fsrepo/lmdb_cursor.c \
	repo/fsrepo/jsmn.c \
	repo/fsrepo/lmdb_journalstore.c \
	repo/config/identity.c \
	repo/config/swarm.c \
	repo/config/peer.c \
	repo/config/config.c \
	repo/config/gateway.c \
	repo/config/addresses.c \
	repo/config/bootstrap_peers.c \
	repo/config/replication.c \
	repo/init.c \
	multibase/multibase.c \
	util/time.c \
	util/errs.c \
	util/thread_pool.c \
	merkledag/merkledag.c \
	merkledag/node.c \
	path/path.c \
	pin/pin.c \
	cid/set.c \
	cid/cid.c \
	routing/online.c \
	routing/supernode.c \
	routing/offline.c \
	routing/k_routing.c \
	ipfsaddr/ipfs_addr.c \
	namesys/pb.c \
	namesys/proquint.c \
	namesys/dns.c \
	namesys/isdomain.c \
	namesys/base.c \
	namesys/resolver.c \
	namesys/routing.c \
	namesys/name.c \
	namesys/publisher.c \
	namesys/namesys.c \
	dnslink/dnslink.c \
	importer/resolver.c \
	importer/exporter.c \
	importer/importer.c \
	blocks/blockstore.c \
	blocks/block.c \
	cmd/ipfs/init.c \
	cmd/cli.c \
	commands/cli/parse.c \
	commands/argument.c \
	commands/command.c \
	commands/command_option.c \
	linkage.c

OBJECTS=$(SOURCES:.c=.o)
OUTPUT=libipfs.a

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	ar rc $@ $(OBJECTS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.a
	rm -f */*.o
	rm -f */*/*.o
