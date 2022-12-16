#include <stdio.h>
#include <string.h>

#include "libp2p/utils/logger.h"
#include "repo/init.h"
#include "importer/importer.h"
#include "importer/exporter.h"
#include "dnslink/dnslink.h"
#include "core/daemon.h"
#include "core/swarm.h"
#include "cmd/cli.h"
#include "namesys/name.h"

int test_linkage() {
    ipfs_daemon(0, NULL);
    return 1;
}

