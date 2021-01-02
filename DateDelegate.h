#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class DateDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QObject * parent = 0);

    QString displayText(const QVariant &value, const QLocale &locale) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // DATEDELEGATE_H
