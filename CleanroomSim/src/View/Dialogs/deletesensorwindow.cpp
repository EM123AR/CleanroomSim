#include "deletesensorwindow.h"
#include <QVBoxLayout>
#include "View/sensorviewer.h"
#include <QPushButton>

namespace View {
namespace Dialogs {

    DeleteSensorWindow::DeleteSensorWindow(Sensors::AbstractSensor* sensor, QWidget* parent)
    : QDialog{parent}, type(nullptr), name(nullptr), description(nullptr), confirmButton(nullptr), cancelButton(nullptr), sensor(sensor) {
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        // Tipo sensore
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

        // Nome sensore
        QHBoxLayout* nameLayout = new QHBoxLayout();
        QLabel* sensorNameLabel = new QLabel("Nome: ", this);
        name = new QLabel(this);
        name->setText(QString::fromStdString(sensor->getName()));
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(name);

        // Descrizione sensore
        QHBoxLayout* descriptionLayout = new QHBoxLayout();
        QLabel* sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        description = new QLabel(this);
        description->setText(QString::fromStdString(sensor->getDescription()));
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(description);

        // Bottoni
        confirmButton = new QPushButton("Elimina", this);
        buttonLayout->addWidget(confirmButton);

        cancelButton = new QPushButton("Annulla", this);
        buttonLayout->addWidget(cancelButton);

        // Connessioni
        /// Eliminazione sensore
        connect(confirmButton, &QPushButton::clicked, this, &DeleteSensorWindow::deleteSensor);
        connect(confirmButton, &QPushButton::clicked, this, &DeleteSensorWindow::close);
        /// Annullamento operazione
        connect(cancelButton, &QPushButton::clicked, this, &DeleteSensorWindow::close);

        // Unione layout
        mainLayout->addWidget(new QLabel("Vuoi eliminare questo sensore?", this), 0, Qt::AlignHCenter);
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
    }

    QString DeleteSensorWindow::getName() const {
        return name->text();
    }

    QString DeleteSensorWindow::getDescription() const {
        return description->text();
    }

    void DeleteSensorWindow::deleteSensor() {
        emit deleteButtonPressed(sensor);
    }

}
}
