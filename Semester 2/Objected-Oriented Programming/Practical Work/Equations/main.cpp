#include "gui.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto* s = new Service("equations");
    GUI gui(s);
    gui.show();
    return QApplication::exec();
}
