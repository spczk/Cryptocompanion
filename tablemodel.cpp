#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


TableModel::TableModel(QList<Wallet> wallets, QObject *parent)
    : QAbstractTableModel(parent)
    , wallets(wallets)
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return wallets.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= wallets.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &wallet = wallets.at(index.row());

        if (index.column() == 0)
            return wallet.name;
        else if (index.column() == 1)
            return wallet.address;
        else if (index.column() == 2)
            return wallet.publicKey;
        else if (index.column() == 3)
            return wallet.privateKey;
        else if (index.column() == 4)
            return wallet.passPhrase;
        else if (index.column() == 5)
            return wallet.wordCode;
        else if (index.column() == 6)
            return wallet.cryptocurrencyName;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("Address");

            case 2:
                return tr("Public Key");

            case 3:
                return tr("Private Key");

            case 4:
                return tr("Pass Phrase");

            case 5:
                return tr("Word Code");

            case 6:
                return tr("Cryptocurrencies");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    QList<Wallet>::iterator i;
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        wallets.insert(position, {QString(), QString(), QString(), QString(), QString(), QString(), QString()} );

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        wallets.removeAt(position);

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto wallet = wallets.value(row);

        if (index.column() == 0)
            wallet.name = value.toString();
        else if (index.column() == 1)
            wallet.address = value.toString();
        else if (index.column() == 2)
            wallet.publicKey = value.toString();
        else if (index.column() == 3)
            wallet.privateKey = value.toString();
        else if (index.column() == 4)
            wallet.passPhrase = value.toString();
        else if (index.column() == 5)
            wallet.wordCode = value.toString();
        else if (index.column() == 6)
            wallet.cryptocurrencyName = value.toString();
        else
            return false;

        wallets.replace(row, wallet);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}



QList<Wallet> TableModel::getWallets() const
{
    return wallets;
}
