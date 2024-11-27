// Copyright (c) 2023 Briskcoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"
#include "nontrivial-threadlocal.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class BriskcoinModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<briskcoin::LogPrintfCheck>("briskcoin-unterminated-logprintf");
        CheckFactories.registerCheck<briskcoin::NonTrivialThreadLocal>("briskcoin-nontrivial-threadlocal");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<BriskcoinModule>
    X("briskcoin-module", "Adds briskcoin checks.");

volatile int BriskcoinModuleAnchorSource = 0;
