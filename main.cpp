#include "common.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();
}
