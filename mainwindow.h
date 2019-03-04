#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QSettings>

#include "connector.h"

class LdapObjectModel;
class LdapTableModel;

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void newFile();
    void openFile();
    void chooseObject(const QModelIndex &index);
    
private:
    void createMenu();

    QAction *newAct;
    QAction *openAct;

    QSettings settings;

    QList<Connector*> connectors;

    LdapObjectModel *model;
    LdapTableModel *table;
};

#endif // MAINWINDOW_H
