#include "gui.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Service service("input.txt");
    GUI gui(service);
    gui.show();
    return a.exec();
}
