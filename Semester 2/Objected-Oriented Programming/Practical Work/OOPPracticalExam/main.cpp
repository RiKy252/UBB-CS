#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto serv = new Service();
    unsigned long long count = serv->getRepo()->getDoctors().size();
    for (unsigned long long i = 0; i < count; i++) {
        string doctorName, doctorSpec;
        doctorName = serv->getRepo()->getDoctors().at(i).getName();
        doctorSpec = serv->getRepo()->getDoctors().at(i).getSpecialisation();
        auto gui = new GUI(nullptr, serv, doctorName, doctorSpec);
        gui->show();
        serv->addObserver(gui);
    }
    return QApplication::exec();
}
