#include "editparticlecounterwindow.h"
#include <QVBoxLayout>
#include "View/sensorviewer.h"
#include <QPushButton>

namespace View {
namespace Dialogs {

    EditParticleCounterWindow::EditParticleCounterWindow(Sensors::ParticleCounter* sensor, QWidget* parent)
        : QDialog{parent}, type(nullptr), name(nullptr), description(nullptr), standard(nullptr), plugged(nullptr), confirmButton(nullptr), cancelButton(nullptr), sensor(sensor) {
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        // Avvisi campi obbligatori
        QLabel* upperWarnLabel = new QLabel("<b>ATTENZIONE</b>", this);
        QLabel* mainWarnLabel = new QLabel("Nome obbligatorio.");
        mainLayout->addWidget(upperWarnLabel, 0, Qt::AlignHCenter);
        mainLayout->addWidget(mainWarnLabel, 0, Qt::AlignHCenter);

        QHBoxLayout* typeLayout = new QHBoxLayout();
        QLabel* sensorTypeLabel = new QLabel("Tipo: ",this);
        type = new QLabel(this);
        SensorViewer sVisitor;
        sensor->accept(sVisitor);

        delete sVisitor.getIconWidget();
        delete sVisitor.getInfoWidget();
        type->setText(sVisitor.getType());
        type->setStyleSheet("font-style: italic");

        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(type, 0, Qt::AlignRight);

        // Modifica nome
        QHBoxLayout* nameLayout = new QHBoxLayout();
        QLabel* sensorNameLabel = new QLabel("Nome: ", this);
        name = new QLineEdit(QString::fromStdString(sensor->getName()), this);
        name->setPlaceholderText("Nuovo nome...");
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(name);

        // Modifica descrizione
        QHBoxLayout* descriptionLayout = new QHBoxLayout();
        QLabel* sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        description = new QTextEdit(QString::fromStdString(sensor->getDescription()), this);
        description->setPlaceholderText("Nuova descrizione...");
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(description);

        // Modifica standard desiderato
        QHBoxLayout* standardLayout = new QHBoxLayout();
        QLabel* sensorStandardLabel = new QLabel("Standard desiderato: ", this);
        standard = new QComboBox(this);
        standard->addItem("ISO 1", 1);
        standard->addItem("ISO 2", 2);
        standard->addItem("ISO 3", 3);
        standard->addItem("ISO 4", 4);
        standard->addItem("ISO 5", 5);
        standard->addItem("ISO 6", 6);
        standard->addItem("ISO 7", 7);
        standard->addItem("ISO 8", 8);
        standard->addItem("ISO 9", 9);
        for(unsigned int i=1; i<10; i++) {
            if(i == sensor->getDesiredStandard())
                standard->setCurrentIndex(i-1); /// viene impostato quello già scelto
        }

        standardLayout->addWidget(sensorStandardLabel, 0, Qt::AlignTop);
        standardLayout->addWidget(standard);

        // Modifica plugged
        QHBoxLayout* pluggedLayout = new QHBoxLayout();
        QLabel* sensorPluggedLabel = new QLabel("Alimentazione: ", this);
        plugged = new QCheckBox("collegato alla rete elettrica", this);
        plugged->setChecked(sensor->isPlugged());
        pluggedLayout->addWidget(sensorPluggedLabel, 0, Qt::AlignTop);
        pluggedLayout->addWidget(plugged);

        // Bottoni
        confirmButton = new QPushButton("Modifica", this);
        buttonLayout->addWidget(confirmButton);

        cancelButton = new QPushButton("Annulla", this);
        buttonLayout->addWidget(cancelButton);

        // Connessioni
        /// Modifica sensore
        connect(confirmButton, &QPushButton::clicked, this, &EditParticleCounterWindow::editSensor);
        connect(confirmButton, &QPushButton::clicked, this, &EditParticleCounterWindow::close);
        /// Annullamento operazioni
        connect(cancelButton, &QPushButton::clicked, this, &EditParticleCounterWindow::close);
        /// Controllo inserimento nome
        connect(name, &QLineEdit::textChanged, this, &EditParticleCounterWindow::sensorNameChanged);

        // Unione layout
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(standardLayout);
        mainLayout->addLayout(pluggedLayout);

        policy = new QLabel(this);
        policy->setText("<b>INSERIRE TUTTI I DATI RICHIESTI</b>");
        mainLayout->addWidget(policy, 0, Qt::AlignHCenter);
        policy->hide();

        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
    }

    void EditParticleCounterWindow::editSensor() {
        sensor->setName(name->text().toStdString());
        sensor->setDescription(description->toPlainText().toStdString());
        sensor->setDesiredStandard(standard->currentData().toInt());
        sensor->setPlugged(plugged->isChecked());
        emit done(QDialog::Accepted);
    }

    void EditParticleCounterWindow::sensorNameChanged(const QString &text) {
        if(text == "") {
            confirmButton->setDisabled(true);
            policy->show();
        } else {
            confirmButton->setDisabled(false);
            policy->hide();
        }
    }
}
}
