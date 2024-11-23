#include "UI.h"


UI::UI() {
    BMI* a = new BMI("2024.11.2" , 13);
    p.addAnalysis(a);
    BP* b = new BP("2024.10.3" , 10,11);
    p.addAnalysis(b);

}

void UI::startApp() {
    while(true){
        UI::menu();
        int cmd;
        cout<< "Your command : ";
        cin>> cmd;
        if (cmd == 0)
            break;
        if (cmd == 1)
        {
            string type;
            cout<< "Type(BMI/BP) : ";
            cin>>type;
            if (type == "BMI"){
                string date;
                cout<<"Date : ";
                cin>> date;
                double value;
                cout<<"Value : ";
                cin>>value;
                MedicalAnalysis* a = new BMI(date , value);
                p.addAnalysis(a);
            }
            if (type == "BP")
            {
                string date;
                cout<<"Date : ";
                cin>> date;
                int d,s;
                cout<<"DV : ";
                cin>>d;
                cout<<"SV : ";
                cin>>s;
                BP* a = new BP(date , d,s);
                p.addAnalysis(a);
            }
        }
        if (cmd == 2){
            for (auto a : this->p.getAllAnalyses()) {
                cout<< a->toString();
                cout << '\n';

            }
        }
        if (cmd == 3){
            int m ;
            cout<<"Month : ";
            cin>>m;
            if (!this->p.isIll(m))
                cout << "Person is ill"<<'\n';
            else
                cout<<"Person is not ill"<<'\n';
        }
        if (cmd == 4)
        {
            string f,d1,d2;
            cout<<"Filename : ";
            cin>>f;
            cout<<"Date1 : ";
            cin>>d1;
            cout<<"Date2 : ";
            cin>>d2;
            this->p.writeToFile(f,d1,d2);
        }

    }
}

void UI::menu() {
    cout << "1. Add analysis\n";
    cout << "2. Show analyses\n";
    cout << "3. Show ilness\n";
    cout << "4. Save to file\n";
    cout << "0. Exit\n";
}
