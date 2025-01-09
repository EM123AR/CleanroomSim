#include "addsensorwindow.h"
#include <QVBoxLayout>
#include "View/sensorviewer.h"
#include <QLineEdit>
#include <QPushButton>
#include "Sensors/hygrometer.h"
#include "Sensors/manometer.h"
#include "Sensors/particlecounter.h"
#include <QMessageBox>

namespace View {
namespace Dialogs {

    AddSensorWindow::AddSensorWindow(QWidget* parent)
    : QDialog{parent}, type(nullptr), name(nullptr), description(nullptr), confirmButton(nullptr), cancelButton(nullptr), policy(nullptr) {
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        // Avviso campi obbligatori
        QLabel* upperWarnLabel = new QLabel("<b>ATTENZIONE</b>", this);
        QLabel* mainWarnLabel = new QLabel("Tipo e nome sono campi obbligatori.");
        mainLayout->addWidget(upperWarnLabel, 0, Qt::AlignHCenter);
        mainLayout->addWidget(mainWarnLabel, 0, Qt::AlignHCenter);

        // Scelta tipo di sensore
        QHBoxLayout* typeLayout = new QHBoxLayout();
        QLabel* sensorTypeLabel = new QLabel("Tipo: ",this);
        type = new QComboBox(this);
        for(const QString &s : SensorViewer::types){
            type->addItem(s);
        }

        type->setCurrentIndex(-1);  //
        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(type);

        // Inserimento nome
        QHBoxLayout* nameLayout = new QHBoxLayout();
        QLabel* sensorNameLabel = new QLabel("Nome: ", this);
        name = new QLineEdit(this);
        name->setPlaceholderText("Nuovo nome...");
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(name);

        // Inserimento descrizione
        QHBoxLayout* descriptionLayout = new QHBoxLayout();
        QLabel* sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        description = new QTextEdit("", this);
        description->setPlaceholderText("Nuova descrizione...");
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(description);

        // Bottoni
        confirmButton = new QPushButton("Conferma", this);
        confirmButton->setDisabled(true);
        cancelButton = new QPushButton("Annulla", this);

        buttonLayout->addWidget(confirmButton);
        buttonLayout->addWidget(cancelButton);

        // Connessioni
        /// Aggiunta sensore
        connect(confirmButton, &QPushButton::clicked, this, &AddSensorWindow::addSensor);
        connect(confirmButton, &QPushButton::clicked, this, &AddSensorWindow::close);
        /// Annullamento operazione
        connect(cancelButton, &QPushButton::clicked, this, &AddSensorWindow::close);
        /// Controllo nome inserito
        connect(name, &QLineEdit::textChanged, this, &AddSensorWindow::sensorNameChanged);
        /// Controllo tipo inserito
        connect(type, &QComboBox::currentIndexChanged, this, &AddSensorWindow::sensorTypeChanged);

        // Unione dei layout
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);

        policy = new QLabel(this);
        policy->setText("<b>INSERIRE TUTTI I DATI RICHIESTI</b>");
        mainLayout->addWidget(policy, 0, Qt::AlignHCenter);

        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
    }

    QString AddSensorWindow::getName() const {
        return name->text();
    }

    QString AddSensorWindow::getDescription() const {
        return description->toPlainText();
    }

    void AddSensorWindow::addSensor() {
        Sensors::AbstractSensor* finalSensor;
        // Indice tipi di sensore:
        /// 0. Igrometro;
        /// 1. Manometro;
        /// 2. Contatore di particelle.

        switch(type->currentIndex())
        {
            // id gestito in Sensors::Storage::Archive
        case 0:
            finalSensor = new Sensors::Hygrometer(0, name->text().toStdString(), description->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        case 1:
            finalSensor = new Sensors::Manometer(0, name->text().toStdString(), description->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        case 2:
            finalSensor = new Sensors::ParticleCounter(0, name->text().toStdString(), description->toPlainText().toStdString());
            emit addButtonPressed(finalSensor);
            break;
        default:
            QMessageBox* alertMessage = new QMessageBox(QMessageBox::Critical, "Errore", "<b>ERRORE</b>nella selezione del tipo!");
                                        alertMessage->setAttribute(Qt::WA_DeleteOnClose);
            alertMessage->addButton("Ok", QMessageBox::YesRole);
            alertMessage->exec();
            break;
        }
    }

    void AddSensorWindow::sensorTypeChanged(const int index) {
        if(index == -1 || name->text() == "") {
            confirmButton->setDisabled(true);
            policy->show();
        } else{
            confirmButton->setDisabled(false);
            policy->hide();
        }
    }

    void AddSensorWindow::sensorNameChanged(const QString& text) {
        if(text == "" || type->currentIndex() == -1) {
            confirmButton->setDisabled(true);
            policy->show();
        } else {
            confirmButton->setDisabled(false);
            policy->hide();
        }
    }

}
}
