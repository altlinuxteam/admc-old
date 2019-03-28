#include "common.h"
#include "mainwindow.h"
#include "ldapobjectmodel.h"
#include "ldaptablemodel.h"

#include "ui_userproperties.h"
#include "ui_connectionproperties.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), settings("BaseALT", "admc")
{
    qDebug() << "Start MainWindow";
    setupUi(this);
    createMenu();

    userProperties = new QTabWidget(this);
    Ui_UserProperties uiUserProperties;
    uiUserProperties.setupUi(userProperties);
    userProperties->hide();
    splitter->addWidget(userProperties);

    connectionProperties = new QTabWidget(this);
    Ui_ConnectionProperties uiConnectionProperties;
    uiConnectionProperties.setupUi(connectionProperties);
    splitter->addWidget(connectionProperties);
    currentProperties = connectionProperties;

    model = new LdapObjectModel(this);
    hierarchy->setModel(model);
    hierarchy->setHeaderHidden(true);

    Connector *c = new Connector(this);
    if(c->connect("dc0.domain.alt")){
        connectors.append(c);
        model->addConnector(*c);
    } else {
        delete c;
    }

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
    QObject::connect(objects, &QTreeView::pressed, this, &MainWindow::chooseProperty);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow";
    delete model;
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
    objects->setModel(table);
}

void MainWindow::chooseProperty(const QModelIndex &index)
{
    qDebug() << "chooseProperty()";

    LdapObject* object = static_cast<LdapObject*>(index.internalPointer());
    if (object->type() == UserType)
        setProperty(userProperties);
}

void MainWindow::setProperty(QTabWidget *widget)
{
    if (currentProperties != widget) {
        currentProperties->hide();
        widget->show();
    }
}
