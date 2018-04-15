#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "user.h"
//#include "wallet.h"


struct Wallet
{
    QString name;
    QString publicKey;
    QString passPhrase;
    QString privateKey;
    QString wordCode;
    QString address;
    QString cryptocurrencyName;

    bool operator ==(const Wallet &other) const
     {
         return name == other.name && address == other.address && publicKey == other.publicKey && privateKey == other.privateKey && passPhrase == other.passPhrase && wordCode == other.wordCode && cryptocurrencyName == other.cryptocurrencyName ;
     }
};



//inline QDataStream &operator<<(QDataStream &stream, const Contact &contact)
//{
//    return stream << contact.name << contact.address;
//}

//inline QDataStream &operator>>(QDataStream &stream, Contact &contact)
//{
//    return stream >> contact.name >> contact.address;
//}

inline QDataStream &operator<<(QDataStream &stream, const Wallet &wallet)
{
    return stream << wallet.name << wallet.address << wallet.publicKey << wallet.privateKey << wallet.passPhrase << wallet.wordCode << wallet.cryptocurrencyName;
}

inline QDataStream &operator>>(QDataStream &stream, Wallet &wallet)
{
    return stream >> wallet.name >> wallet.address >> wallet.publicKey >> wallet.privateKey >> wallet.passPhrase >> wallet.wordCode >> wallet.cryptocurrencyName;
}


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    //TableModel(QList<Contact> contacts, QObject *parent = 0);
    TableModel(QList<Wallet> wallets, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
   // QList<Contact> getContacts() const;
    QList<Wallet> getWallets() const;

    //Wallet wallet;

private:
   // QList<Contact> contacts;
    QList<Wallet> wallets;
};

#endif // TABLEMODEL_H
