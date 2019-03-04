#include "common.h"
#include "mainwindow.h"
#include "ldapobjectmodel.h"
#include "ldaptablemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), settings("BaseALT", "admc")
{
    qDebug() << "Start MainWindow";
    setupUi(this);
    createMenu();

    model = new LdapObjectModel(this);
    hierarchy->setModel(model);
    hierarchy->setHeaderHidden(true);

    connectors.append(new Connector(this));
    Connector *c = connectors.back();
    c->connect("dc0.domain.alt");
    model->addConnector(*c);

    table = new LdapTableModel(this);
    objects->setShowGrid(false);
    objects->horizontalHeader()->hide();
    objects->verticalHeader()->hide();
    objects->horizontalHeader()->setMinimumSectionSize(1);
    objects->verticalHeader()->setMinimumSectionSize(1);
    objects->verticalHeader()->setMaximumSectionSize(1);
    objects->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //objects->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    objects->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    objects->verticalHeader()->setDefaultSectionSize(28);
    objects->resizeRowsToContents();
    objects->setModel(table);

    QObject::connect(hierarchy, &QTreeView::pressed, this, &MainWindow::chooseObject);
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

void MainWindow::chooseObject(const QModelIndex &index)
{
    qDebug() << "chooseObject();";

    if (!index.isValid()) {
        qDebug() << "chooseObject(): got invalid index";
        return;
    }
    qDebug() << "chooseObject(): got valid index" << (void*)table;

    table->setRootObject(static_cast<LdapObject*>(index.internalPointer()));
    //table->submit();
    //objects->update(0,0,1,1);
    objects->setModel(table);
}
