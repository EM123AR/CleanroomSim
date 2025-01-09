#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("CleanroomSim");
    View::MainWindow mainWindow;
    mainWindow.resize(1024, 650);
    mainWindow.show();
    return app.exec();
}
