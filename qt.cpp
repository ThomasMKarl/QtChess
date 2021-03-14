#include "qt/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    qtc::qt::MainWindow window;
    window.show();

    return application.exec();
}
