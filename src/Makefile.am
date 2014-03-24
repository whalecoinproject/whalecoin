include Makefile.include

AM_CPPFLAGS += -I$(builddir)

noinst_LIBRARIES = \
  libbitcoin_server.a \
  libbitcoin_common.a \
  libbitcoin_cli.a
if ENABLE_WALLET
noinst_LIBRARIES += libbitcoin_wallet.a
endif

bin_PROGRAMS =

if BUILD_BITCOIND
  bin_PROGRAMS += bitcoind
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += bitcoin-cli
endif

SUBDIRS = . $(BUILD_QT) $(BUILD_TEST)
DIST_SUBDIRS = . qt test
.PHONY: FORCE
# bitcoin core #
BITCOIN_CORE_H = \
addrman.h\
alert.h\
allocators.h\
base58.h\
bignum.h\
bitcoinrpc.h\
bloom.h\
chainparams.h\
checkpoints.h\
checkqueue.h\
clientversion.h\
coincontrol.h\
compat.h\
crypter.h\
db.h\
hash.h\
init.h\
irc.h\
kernel.h\
key.h\
keystore.h\
leveldbwrapper.h\
limitedmap.h\
main.h\
miner.h\
mruset.h\
net.h\
netbase.h\
noui.h\
protocol.h\
rpcclient.h\
strlcpy.h\
script.h\
scrypt_mine.h\
scrypt.h\
serialize.h\
sync.h\
threadsafety.h\
tinyformat.h\
txdb-leveldb.h\
txdb.h\
ui_interface.h\
uint256.h\
util.h\
version.h\
wallet.h\
walletdb.h\
zerocoin/Accumulator.h\
zerocoin/AccumulatorProofOfKnowledge.h\
zerocoin/Coin.h\
zerocoin/CoinSpend.h\
zerocoin/Commitment.h\
zerocoin/ParamGeneration.h\
zerocoin/Params.h\
zerocoin/SerialNumberSignatureOfKnowledge.h\
zerocoin/SpendMetaData.h\
zerocoin/ZeroTest.h\
zerocoin/Zerocoin.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libbitcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  bitcoinrpc.cpp\
  chainparams.cpp \
  checkpoints.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  irc.cpp\
  noui.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

libbitcoin_wallet_a_SOURCES = \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(BITCOIN_CORE_H)

libbitcoin_common_a_SOURCES = \
  chainparams.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  script.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  $(BITCOIN_CORE_H)

libbitcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BITCOIN_CORE_H)

nodist_libbitcoin_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# bitcoind binary #
bitcoind_LDADD = \
  libbitcoin_server.a \
  libbitcoin_cli.a \
  libbitcoin_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
if ENABLE_WALLET
bitcoind_LDADD += libbitcoin_wallet.a
endif
bitcoind_SOURCES = bitcoind.cpp
#

if TARGET_WINDOWS
bitcoind_SOURCES += bitcoind-res.rc
endif

AM_CPPFLAGS += $(BDB_CPPFLAGS)
bitcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS)

# bitcoin-cli binary #
bitcoin_cli_LDADD = \
  libbitcoin_cli.a \
  libbitcoin_common.a \
  $(BOOST_LIBS)
bitcoin_cli_SOURCES = bitcoin-cli.cpp
#

if TARGET_WINDOWS
bitcoin_cli_SOURCES += bitcoin-cli-res.rc
endif

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
leveldb/libleveldb.a: leveldb/libmemenv.a

leveldb/%.a:
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
	  OPT="$(CXXFLAGS) $(CPPFLAGS)"

qt/bitcoinstrings.cpp: $(libbitcoin_server_a_SOURCES) $(libbitcoin_common_a_SOURCES) $(libbitcoin_cli_a_SOURCES)
	@test -n $(XGETTEXT) || echo "xgettext is required for updating translations"
	@cd $(top_srcdir); XGETTEXT=$(XGETTEXT) share/qt/extract_strings_qt.py

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb Makefile.include

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
