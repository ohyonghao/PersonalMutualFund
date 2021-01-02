#include "DateDelegate.h"

#include <QDate>
#include <QDateEdit>

DateDelegate::DateDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

QString DateDelegate::displayText(const QVariant &value, const QLocale &locale) const{
    if( value.type() == QVariant::Date || value.type() == QVariant::DateTime ){
        return value.toDate().toString();
    }
    return QStyledItemDelegate::displayText(value, locale);
}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    auto editor = new QDateEdit( parent );
    editor->setCalendarPopup(true);
    return editor;
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    auto date = index.data().toDateTime();
    date.setDate(editor->property("date").toDate());
    model->setData(index, date);
}
