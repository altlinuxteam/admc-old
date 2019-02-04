#include "common.h"
#include "mainwindow.h"
#include "ldapobjectmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), settings("BaseALT", "admc")
{
    qDebug() << "Start MainWindow";
    setupUi(this);
    createMenu();

    LdapObjectModel *model = new LdapObjectModel(this);
    hierarchy->setModel(model);
    hierarchy->setHeaderHidden(true);

    connectors.append(new Connector(this));
    Connector *c = connectors.back();
    c->connect("dc0.domain.alt");
    model->addConnector(*c);
}

void MainWindow::createMenu()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
}

void MainWindow::newFile()
{
    qDebug() << "newFile();";
}

void MainWindow::openFile()
{
    qDebug() << "openFile();";
}
