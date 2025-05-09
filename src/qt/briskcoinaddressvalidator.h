// Copyright (c) 2011-2020 The Briskcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BRISKCOIN_QT_BRISKCOINADDRESSVALIDATOR_H
#define BRISKCOIN_QT_BRISKCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BriskcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BriskcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Briskcoin address widget validator, checks for a valid briskcoin address.
 */
class BriskcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BriskcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // BRISKCOIN_QT_BRISKCOINADDRESSVALIDATOR_H
