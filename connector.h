#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>
#include <QProcess>
#include <QDir>

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(QObject *parent = nullptr);

    bool connect(QString server);
    bool connect(QDir mountpoint);

signals:

public slots:

private:
    bool isMounted;
    QDir root;
    QProcess adfs;
};

#endif // CONNECTOR_H
