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
    Q_UNUSED(parent); // removes warning of unused objects
    return wallets.size(); //returns the size of our wallets QList
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 7; //number of our columns - always 7 in this case
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    //Getting our data to the model on the right place
    if (!index.isValid())
        return QVariant();

    if (index.row() >= wallets.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &wallet = wallets.at(index.row());

        if (index.column() == 0)
            return wallet.name;
        else if (index.column() == 1)
            return wallet.cryptocurrencyName;
        else if (index.column() == 2)
            return wallet.address;
        else if (index.column() == 3)
            return wallet.publicKey;
        else if (index.column() == 4)
            return wallet.privateKey;
        else if (index.column() == 5)
            return wallet.passPhrase;
        else if (index.column() == 6)
            return wallet.wordCode;
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //Setting our table headers
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("Cryptocurrency");

            case 2:
                return tr("Address");

            case 3:
                return tr("Public Key");

            case 4:
                return tr("Private Key");

            case 5:
                return tr("Pass Phrase");

            case 6:
                return tr("Word Code");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    //Inserting rows to the model based on number of wallets in our QList
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
    //Part of remove entry - removes data from model
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        wallets.removeAt(position);

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //Needed for editing entry - emits signal when data in model differs from specified one
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto wallet = wallets.value(row);

        if (index.column() == 0)
            wallet.name = value.toString();
        else if (index.column() == 1)
            wallet.cryptocurrencyName = value.toString();
        else if (index.column() == 2)
            wallet.address = value.toString();
        else if (index.column() == 3)
            wallet.publicKey = value.toString();
        else if (index.column() == 4)
            wallet.privateKey = value.toString();
        else if (index.column() == 5)
            wallet.passPhrase = value.toString();
        else if (index.column() == 6)
            wallet.wordCode = value.toString();
        else
            return false;

        wallets.replace(row, wallet);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
//Setting our items flags for our table model
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}



QList<Wallet> TableModel::getWallets() const
{
    return wallets;
}
