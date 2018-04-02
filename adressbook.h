#ifndef ADRESSBOOK_H
#define ADRESSBOOK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>


 class QLabel;
 class QLineEdit;
 class QTextEdit;

 class AddressBook : public QWidget
 {
     Q_OBJECT

 public:
     AddressBook(QWidget *parent = 0);

 private:
     QLineEdit *nameLine;
     QTextEdit *addressText;
 };

#endif // ADRESSBOOK_H
