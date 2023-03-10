#ifndef __CORE_BUILDER_H__
#define __CORE_BUILDER_H__

#include <stdio.h>

#include "commands/context.h"
#include "repo/config/config.h"
#include "core/ipfs_node.h"

struct BuildCfg {
	int online;
	// ExtraOpts map[string]bool
	int permanent;
	int nil_repo;
	//struct RoutingOption routing;
	//struct HostOption host;
	//struct Repo repo;
};

int ipfs_core_builder_new_node(struct Context* context, struct BuildCfg* build_cfg, struct IpfsNode* buildConfig);

#endif /* builder_h */
