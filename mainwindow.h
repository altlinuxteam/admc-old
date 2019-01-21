#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_mainwindow.h"
#include <QMainWindow>

class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void newFile();
    void openFile();
    
private:
    void createMenu();

    QAction *newAct;
    QAction *openAct;
};

#endif // MAINWINDOW_H
