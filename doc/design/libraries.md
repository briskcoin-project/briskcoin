# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbriskcoin_cli*         | RPC client functionality used by *briskcoin-cli* executable |
| *libbriskcoin_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbriskcoin_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbriskcoin_consensus*   | Consensus functionality used by *libbriskcoin_node* and *libbriskcoin_wallet*. |
| *libbriskcoin_crypto*      | Hardware-optimized functions for data encryption, hashing, message authentication, and key derivation. |
| *libbriskcoin_kernel*      | Consensus engine and support library used for validation by *libbriskcoin_node*. |
| *libbriskcoinqt*           | GUI functionality used by *briskcoin-qt* and *briskcoin-gui* executables. |
| *libbriskcoin_ipc*         | IPC functionality used by *briskcoin-node*, *briskcoin-wallet*, *briskcoin-gui* executables to communicate when [`-DWITH_MULTIPROCESS=ON`](multiprocess.md) is used. |
| *libbriskcoin_node*        | P2P and RPC server functionality used by *briskcoind* and *briskcoin-qt* executables. |
| *libbriskcoin_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbriskcoin_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbriskcoin_wallet*      | Wallet functionality used by *briskcoind* and *briskcoin-wallet* executables. |
| *libbriskcoin_wallet_tool* | Lower-level wallet functionality used by *briskcoin-wallet* executable. |
| *libbriskcoin_zmq*         | [ZeroMQ](../zmq.md) functionality used by *briskcoind* and *briskcoin-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. An exception is *libbriskcoin_kernel*, which, at some future point, will have a documented external interface.

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`add_library(briskcoin_* ...)`](../../src/CMakeLists.txt) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbriskcoin_node* code lives in `src/node/` in the `node::` namespace
  - *libbriskcoin_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbriskcoin_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbriskcoin_util* code lives in `src/util/` in the `util::` namespace
  - *libbriskcoin_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

briskcoin-cli[briskcoin-cli]-->libbriskcoin_cli;

briskcoind[briskcoind]-->libbriskcoin_node;
briskcoind[briskcoind]-->libbriskcoin_wallet;

briskcoin-qt[briskcoin-qt]-->libbriskcoin_node;
briskcoin-qt[briskcoin-qt]-->libbriskcoinqt;
briskcoin-qt[briskcoin-qt]-->libbriskcoin_wallet;

briskcoin-wallet[briskcoin-wallet]-->libbriskcoin_wallet;
briskcoin-wallet[briskcoin-wallet]-->libbriskcoin_wallet_tool;

libbriskcoin_cli-->libbriskcoin_util;
libbriskcoin_cli-->libbriskcoin_common;

libbriskcoin_consensus-->libbriskcoin_crypto;

libbriskcoin_common-->libbriskcoin_consensus;
libbriskcoin_common-->libbriskcoin_crypto;
libbriskcoin_common-->libbriskcoin_util;

libbriskcoin_kernel-->libbriskcoin_consensus;
libbriskcoin_kernel-->libbriskcoin_crypto;
libbriskcoin_kernel-->libbriskcoin_util;

libbriskcoin_node-->libbriskcoin_consensus;
libbriskcoin_node-->libbriskcoin_crypto;
libbriskcoin_node-->libbriskcoin_kernel;
libbriskcoin_node-->libbriskcoin_common;
libbriskcoin_node-->libbriskcoin_util;

libbriskcoinqt-->libbriskcoin_common;
libbriskcoinqt-->libbriskcoin_util;

libbriskcoin_util-->libbriskcoin_crypto;

libbriskcoin_wallet-->libbriskcoin_common;
libbriskcoin_wallet-->libbriskcoin_crypto;
libbriskcoin_wallet-->libbriskcoin_util;

libbriskcoin_wallet_tool-->libbriskcoin_wallet;
libbriskcoin_wallet_tool-->libbriskcoin_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class briskcoin-qt,briskcoind,briskcoin-cli,briskcoin-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Crypto* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus, crypto, and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbriskcoin_wallet* and *libbriskcoin_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbriskcoin_crypto* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbriskcoin_consensus* should only depend on *libbriskcoin_crypto*, and all other libraries besides *libbriskcoin_crypto* should be allowed to depend on it.

- *libbriskcoin_util* should be a standalone dependency that any library can depend on, and it should not depend on other libraries except *libbriskcoin_crypto*. It provides basic utilities that fill in gaps in the C++ standard library and provide lightweight abstractions over platform-specific features. Since the util library is distributed with the kernel and is usable by kernel applications, it shouldn't contain functions that external code shouldn't call, like higher level code targeted at the node or wallet. (*libbriskcoin_common* is a better place for higher level code, or code that is meant to be used by internal applications only.)

- *libbriskcoin_common* is a home for miscellaneous shared code used by different Briskcoin Core applications. It should not depend on anything other than *libbriskcoin_util*, *libbriskcoin_consensus*, and *libbriskcoin_crypto*.

- *libbriskcoin_kernel* should only depend on *libbriskcoin_util*, *libbriskcoin_consensus*, and *libbriskcoin_crypto*.

- The only thing that should depend on *libbriskcoin_kernel* internally should be *libbriskcoin_node*. GUI and wallet libraries *libbriskcoinqt* and *libbriskcoin_wallet* in particular should not depend on *libbriskcoin_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be able to get it from *libbriskcoin_consensus*, *libbriskcoin_common*, *libbriskcoin_crypto*, and *libbriskcoin_util*, instead of *libbriskcoin_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbriskcoinqt*, *libbriskcoin_node*, *libbriskcoin_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](../../src/interfaces/) abstract interfaces.

## Work in progress

- Validation code is moving from *libbriskcoin_node* to *libbriskcoin_kernel* as part of [The libbriskcoinkernel Project #27587](https://github.com/briskcoin/briskcoin/issues/27587)
