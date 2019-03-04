#ifndef LDAPTABLEMODEL_H
#define LDAPTABLEMODEL_H

#include <QAbstractTableModel>
#include "ldapobject.h"

class LdapTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LdapTableModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setRootObject(LdapObject* object);

private:
     LdapObject *parentObject;
};

#endif // LDAPTABLEMODEL_H
