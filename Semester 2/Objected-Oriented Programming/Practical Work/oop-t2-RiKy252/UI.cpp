#include "UI.h"

UI::UI() {
    this->service = Service();
}

void UI::menu() {
    cout << "1. Add car\n";
    cout << "2. Show cars\n";
    cout << "3. Save to file\n";
    cout << "0. Exit\n";
}

void UI::startApp() {
    while (true) {
        menu();
        int option;
        cin >> option;
        if (option == 0)
            break;
        else if (option == 1) {
            string bodyStyle;
            string engineType;
            int autonomy = 0;
            cout << "Type the body style of the car: (Sedan / Convertible)\n";
            cin >> bodyStyle;
            if (bodyStyle != "Sedan" && bodyStyle != "Convertible")
                cout << "Invalid body style\n";
            else {
                cout << "Type the engine type of the car: (ElectricEngine / TurboEngine)\n";
                cin >> engineType;
                if (engineType != "ElectricEngine" && engineType != "TurboEngine")
                    cout << "Invalid engine type\n";
                else {
                    if (engineType == "ElectricEngine") {
                        cout << "Enter the autonomy for the electric engine: \n";
                        cin >> autonomy;
                    }
                    this->service.addCar(bodyStyle, engineType, autonomy);
                    vector<Car *> cars = this->service.getAllCars();
                    cout << cars[cars.size() - 1]->toString() << "\n";
                }
            }
        }
        else if (option == 2) {
            vector<Car*> cars = this->service.getAllCars();
            for (auto car : cars) {
                cout << car->toString();
                cout << "\n";
            }
        }
        else if (option == 3) {
            string filename;
            cout << "Enter the filename: \n";
            cin >> filename;
            double price;
            cout << "Enter the max price: \n";
            cin >> price;
            this->service.writeToFile(filename, this->service.getCarsWithMaxPrice(price));
        }
        else
            cout << "Invalid option!\n";
    }
}
