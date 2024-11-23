//
// Created by Riki on 6/21/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"
#include "ui_GUI.h"


GUI::GUI(QWidget *parent, Service *service, string doctorName, string doctorSpec) :
        QWidget(parent), ui(new Ui::GUI), service(service), doctorName(doctorName), doctorSpec(doctorSpec) {
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(doctorName));
    populateList();
    connectSignalsAndSlots();
}

GUI::~GUI() {
    delete ui;
}

void GUI::update() {
    vector<Patient>& patients = this->service->getRepo()->getPatients();
    for (int i = 0; i < patients.size(); i++) {
        for (int j = i + 1; j < patients.size(); j++) {
            if (patients.at(i).getAdmissionDate() > patients.at(j).getAdmissionDate()) {
                swap(patients.at(i), patients.at(j));
            }
        }
    }
    populateList();
}

void GUI::populateList() {
    ui->patientsListWidget->clear();
    for (auto &patient : service->getRepo()->getPatients()) {
        if (patient.getCurrentDoctor() == doctorName) {
            auto item = new QListWidgetItem(QString::fromStdString(patient.toString()));
            item->setBackground(Qt::green);
            ui->patientsListWidget->addItem(item);
        } else if (patient.getSpecialisationNeeded() == doctorSpec || patient.getDiagnosis() == "undiagnosed") {
            ui->patientsListWidget->addItem(QString::fromStdString(patient.toString()));
        }
    }
}

void GUI::connectSignalsAndSlots() {
    connect(ui->yourPatientsCheckBox, &QCheckBox::stateChanged, this, [this]() {
        if (ui->yourPatientsCheckBox->isChecked()) {
            ui->patientsListWidget->clear();
            for (auto patient : service->getRepo()->getPatients()) {
                if (patient.getCurrentDoctor() == doctorName) {
                    auto item = new QListWidgetItem(QString::fromStdString(patient.toString()));
                    item->setBackground(Qt::green);
                    ui->patientsListWidget->addItem(item);
                }
            }
        } else {
            populateList();
        }
    });
    connect(ui->addPatientButton, &QPushButton::clicked, this, [this]() {
        string name = ui->nameLineEdit->text().toStdString();
        string diagnosis = ui->diagnosisLineEdit->text().toStdString();
        string specialisationNeeded = ui->specialisationNeededLineEdit->text().toStdString();
        string currentDoctor = ui->currentDoctorLineEdit->text().toStdString();
        string admissionDate = ui->admissionDateLineEdit->text().toStdString();
        if (name == "") {
            QMessageBox::warning(this, "Error!", "The name cannot be empty!");
        }
        else if (admissionDate < "2024-06-21") {
            QMessageBox::warning(this, "Error!", "The admission date is in the past!");
        }
        else {
            if (diagnosis == "") {
                diagnosis = "undiagnosed";
            }
            Patient p(name, diagnosis, specialisationNeeded, currentDoctor, admissionDate);
            service->addPatient(p);
            QMessageBox::information(this, "Success!", "Patient added!");
        }
    });
    connect(ui->updateDiagnosisButton, &QPushButton::clicked, this, [this]() {
        auto selectedItems = ui->patientsListWidget->selectedItems();
        if (selectedItems.size() == 0) {
            QMessageBox::warning(this, "Error!", "No patient selected!");
        } else {
            string name = selectedItems.at(0)->text().toStdString();
            string diagnosis = ui->diagnosisLineEdit->text().toStdString();
            string specialisation = ui->specialisationNeededLineEdit->text().toStdString();
            if (diagnosis == "") {
                QMessageBox::warning(this, "Error!", "The diagnosis cannot be empty!");
            }
            else if (diagnosis == "undiagnosed") {
                QMessageBox::warning(this, "Error!", "The diagnosis cannot be undiagnosed!");
            }
            else {
                for (auto &patient : service->getRepo()->getPatients()) {
                    if (patient.toString() == name) {
                        if (patient.getDiagnosis() == "undiagnosed" || patient.getCurrentDoctor() == this->doctorName) {
                            patient.setDiagnosis(diagnosis);
                            patient.setSpecialisation(specialisation);
                            service->notify();
                            QMessageBox::information(this, "Success!", "Diagnosis and specialisation updated!");
                            break;
                        }
                        else {
                            QMessageBox::warning(this, "Error!", "Invalid patient!");
                        }
                    }
                }
            }
        }
    });
}


