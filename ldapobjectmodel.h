#ifndef LDAPITEMMODEL_H
#define LDAPITEMMODEL_H

#include <QAbstractItemModel>
#include "ldapconnection.h"

class LdapObjectModel : public QAbstractItemModel
{
    Q_OBJECT

    //Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
    //Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    //Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)

//Q_SIGNALS:
//    void basednChanged(const QString &newBasedn);
//    void objectRenamed(const QString &baseDn, const QString &oldName, const QString &newName);
//    void containerLoaded(const QString &baseDn);

public:
    enum Roles {
        ObjectIconRole = Qt::DecorationRole,
        ObjectDNRole = Qt::UserRole + 1,
        ObjectNameRole = Qt::DisplayRole
    };

public:
    explicit LdapObjectModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = ObjectNameRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addConnector(Connector &c);
private:
    QList<LdapConnection*> connections;
};

#endif // LDAPITEMMODEL_H
