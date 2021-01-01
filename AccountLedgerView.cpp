#include "AccountLedgerView.h"
#include "ui_AccountLedgerView.h"

AccountLedgerView::AccountLedgerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountLedgerView)
{
    ui->setupUi(this);
}

AccountLedgerView::~AccountLedgerView()
{
    delete ui;
}
