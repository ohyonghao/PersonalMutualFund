#ifndef ACCOUNTLEDGERVIEW_H
#define ACCOUNTLEDGERVIEW_H

#include <QWidget>

namespace Ui {
class AccountLedgerView;
}

class AccountLedgerView : public QWidget
{
    Q_OBJECT

public:
    explicit AccountLedgerView(QWidget *parent = nullptr);
    ~AccountLedgerView();

private:
    Ui::AccountLedgerView *ui;
};

#endif // ACCOUNTLEDGERVIEW_H
