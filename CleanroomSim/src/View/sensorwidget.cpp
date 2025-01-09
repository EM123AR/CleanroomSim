#include "sensorwidget.h"
#include "Sensors/abstractsensor.h"
#include <QVBoxLayout>
#include "sensorviewer.h"
#include <QMouseEvent>

namespace View {

    SensorWidget::SensorWidget(Sensors::AbstractSensor* sensor, QWidget* parent)
    : QFrame{parent}, sensor(sensor) {

        QHBoxLayout* mainLayout = new QHBoxLayout();
        QVBoxLayout* smallIconsLayout = new QVBoxLayout();
        QVBoxLayout* detailsLayout = new QVBoxLayout();

        nameLabel = new QLabel(QString::fromStdString(sensor->getName()) + " - " + QString::number(sensor->getIdentifier()));
        nameLabel->setStyleSheet("font-weight: bold; font-size: 15px");
        descriptionLabel = new QLabel(QString::fromStdString(sensor->getDescription()));
        descriptionLabel->setStyleSheet("font-size: 13px");
        descriptionLabel->setWordWrap(true);
        detailsLayout->addWidget(nameLabel);
        detailsLayout->addWidget(descriptionLabel);

        SensorViewer visitor;
        sensor->accept(visitor);
        iconWidget = visitor.getIconWidget();
        iconWidget->setMaximumSize({50, 50});
        warningIconWidget = visitor.getWarningIconWidget();

        batteryIconWidget = visitor.getBatteryIconWidget();
        batteryIconWidget->setMaximumSize({20, 20});

        if(warningIconWidget){
            warningIconWidget->setMaximumSize({20, 20});
            smallIconsLayout->addWidget(warningIconWidget);
        } else
            smallIconsLayout->addStretch(); /// se non è presente l'icona spinge la successiva verso il basso
        smallIconsLayout->addWidget(batteryIconWidget);

        // Unione layout
        mainLayout->addWidget(iconWidget);
        mainLayout->addLayout(smallIconsLayout);
        mainLayout->addLayout(detailsLayout);

        this->setLayout(mainLayout);

        sensor->addObserver(this);

        this->setMinimumWidth(360);
    }

    Sensors::AbstractSensor* SensorWidget::getSensor() {
        return sensor;
    }

    const Sensors::AbstractSensor* SensorWidget::getSensorConst() const {
        return sensor;
    }

    void SensorWidget::setSensor(Sensors::AbstractSensor* sensor) {
        this->sensor = sensor;
    }

    void SensorWidget::mousePressEvent(QMouseEvent* event) {
        if(event->button() == Qt::LeftButton)
            emit mousePressed(this->getSensor());

        QFrame::mousePressEvent(event);
    }

    void SensorWidget::notify(Sensors::AbstractSensor& sensor) {
        if(nameLabel->text() != QString::fromStdString(sensor.getName())) {
            nameLabel->setText(QString::fromStdString(sensor.getName()) + " - " + QString::number(sensor.getIdentifier()));
            nameLabel->setWordWrap(true);
        }
        if(descriptionLabel->text() != QString::fromStdString(sensor.getDescription())) {
            descriptionLabel->setText(QString::fromStdString(sensor.getDescription()));
            descriptionLabel->setWordWrap(true);
        }
    }

    void SensorWidget::destructor() {
        sensor = nullptr;
    }

    SensorWidget::~SensorWidget() {
        if(sensor)
            sensor->removeObserver(this);
    }
}
