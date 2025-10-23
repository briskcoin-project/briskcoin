# Copyright (c) 2023-present The Briskcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(generate_setup_nsi)
  set(abs_top_srcdir ${PROJECT_SOURCE_DIR})
  set(abs_top_builddir ${PROJECT_BINARY_DIR})
  set(CLIENT_URL ${PROJECT_HOMEPAGE_URL})
  set(CLIENT_TARNAME "briskcoin")
  set(BRISKCOIN_WRAPPER_NAME "briskcoin")
  set(BRISKCOIN_GUI_NAME "briskcoin-qt")
  set(BRISKCOIN_DAEMON_NAME "briskcoind")
  set(BRISKCOIN_CLI_NAME "briskcoin-cli")
  set(BRISKCOIN_TX_NAME "briskcoin-tx")
  set(BRISKCOIN_WALLET_TOOL_NAME "briskcoin-wallet")
  set(BRISKCOIN_TEST_NAME "test_briskcoin")
  set(EXEEXT ${CMAKE_EXECUTABLE_SUFFIX})
  configure_file(${PROJECT_SOURCE_DIR}/share/setup.nsi.in ${PROJECT_BINARY_DIR}/briskcoin-win64-setup.nsi USE_SOURCE_PERMISSIONS @ONLY)
endfunction()
