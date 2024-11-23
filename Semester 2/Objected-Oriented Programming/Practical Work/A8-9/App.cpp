#include "interface.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    /*
    // A8
    QApplication app(argc, argv);
    QWidget* window = interfaceA8();
    int result = app.exec();
    delete window;
    return result;
    */
    // A9
    QApplication app(argc, argv);
    GUI gui;
    gui.show();
    gui.startApp();
    return app.exec();
}

