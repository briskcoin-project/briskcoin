// Copyright (c) 2011-2020 The Briskcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BRISKCOIN_MAPPORT_H
#define BRISKCOIN_MAPPORT_H

static constexpr bool DEFAULT_NATPMP = true;

void StartMapPort(bool enable);
void InterruptMapPort();
void StopMapPort();

#endif // BRISKCOIN_MAPPORT_H
