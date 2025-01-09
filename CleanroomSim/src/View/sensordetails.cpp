#include "sensordetails.h"
#include <QVBoxLayout>
#include "Sensors/abstractsensor.h"
#include "sensorviewer.h"

namespace View {

    SensorDetails::SensorDetails(Sensors::AbstractSensor* sensor, QWidget* parent)
        : QWidget{parent},  sensor(sensor) {
        if(sensor) {
            QVBoxLayout *mainLayout = new QVBoxLayout();

            name = new QLabel(this);
            name->setText(QString::fromStdString(sensor->getName()));
            name->setStyleSheet("font-weight: bold; font-size: 25px");

            description = new QLabel(this);
            description->setText(QString::fromStdString(sensor->getDescription()));
            description->setStyleSheet("font-size: 20px");
            description->setWordWrap(true);

            QVBoxLayout *commonInfoLayout = new QVBoxLayout();
            commonInfoLayout->addWidget(name);
            commonInfoLayout->addWidget(description);

            SensorViewer visitor;
            sensor->accept(visitor);
            iconWidget = visitor.getIconWidget();
            iconWidget->setMaximumSize(QSize(50, 50));
            iconWidget->setMinimumSize(QSize(20, 20));

            infoWidget = visitor.getInfoWidget();

            QHBoxLayout *upperInfoLayout = new QHBoxLayout();
            upperInfoLayout->addWidget(iconWidget);
            upperInfoLayout->addLayout(commonInfoLayout);

            mainLayout->addLayout(upperInfoLayout);
            mainLayout->addWidget(infoWidget);

            this->setLayout(mainLayout);

            sensor->addObserver(this);
        }

        this->setMinimumHeight(150);
    }

    void SensorDetails::notify(Sensors::AbstractSensor& sensor) {
        if(name->text() != QString::fromStdString(sensor.getName())) {
            name->setText(QString::fromStdString(sensor.getName()));
            name->setWordWrap(true);
        }
        if(description->text() != QString::fromStdString(sensor.getDescription())) {
            description->setText(QString::fromStdString(sensor.getDescription()));
            description->setWordWrap(true);
        }

        SensorViewer visitor;
        sensor.accept(visitor);
        infoWidget->deleteLater();
        infoWidget = visitor.getInfoWidget();
        static_cast<QVBoxLayout*>(this->layout())->addWidget(infoWidget);
    }

    void SensorDetails::destructor() {
        sensor = nullptr;
    }

    SensorDetails::~SensorDetails() {
        if(sensor) sensor->removeObserver(this);
    }
}
