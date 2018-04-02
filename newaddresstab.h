#ifndef NEWADDRESSTAB_H
#define NEWADDRESSTAB_H

#include <QWidget>

class QLabel;
class QPushButton;
class QVBoxLayout;

class NewAddressTab : public QWidget
{
    Q_OBJECT

public:
    NewAddressTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(QString name, QString address);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif
