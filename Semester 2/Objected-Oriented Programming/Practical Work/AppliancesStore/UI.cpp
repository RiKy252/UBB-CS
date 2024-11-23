#include "UI.h"

UI::UI() {
    this->service = Service();
}

void UI::menu() {
    cout << "1. Add appliance\n";
    cout << "2. Show all\n";
    cout << "3. Show inefficient\n";
    cout << "4. Save to file\n";
    cout << "0. Exit\n";
}

void UI::run() {
    while (true) {
        menu();
        int command;
        cin >> command;
        if (command == 0)
            break;
        if (command == 1) {
            string type;
            cout << "Type: ";
            cin >> type;
            if (type == "Refrigerator") {
                string id, usage;
                bool freezer;
                cout << "Id: ";
                cin >> id;
                cout << "Usage: ";
                cin >> usage;
                cout << "Freezer: ";
                cin >> freezer;
                this->service.addAppliance(new Refrigerator(id, usage, freezer));
            }
            else if (type == "WashingMachine") {
                string id;
                double electricity;
                cout << "Id: ";
                cin >> id;
                cout << "Electricity: ";
                cin >> electricity;
                this->service.addAppliance(new WashingMachine(id, electricity));
            }
        }
        else if (command == 2) {
            for (auto appliance : this->service.getAllAppliances()) {
                cout << appliance->toString() << endl;
            }
        }
        else if (command == 3) {
            for (auto appliance : this->service.getAppliancesConsumingMoreThan(100)) {
                cout << appliance->toString() << endl;
            }
        }
        else if (command == 4) {
            string filename;
            double value;
            cout << "Filename: ";
            cin >> filename;
            cout << "Value: ";
            cin >> value;
            this->service.writeToFile(filename, value);
        }
    }
}
