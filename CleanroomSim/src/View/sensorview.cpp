#include "sensorview.h"
#include <QVBoxLayout>
#include "Charts/chartsvisitor.h"
#include "Dialogs/edithygrometerwindow.h"
#include "Dialogs/editmanometerwindow.h"
#include "Dialogs/editparticlecounterwindow.h"
#include "Dialogs/deletesensorwindow.h"

namespace View {

    SensorView::SensorView(Sensors::AbstractSensor* sensor, QWidget* parent)
    : QWidget{parent}, sensor(sensor), details(nullptr), chartViewer(nullptr) {
        QVBoxLayout* mainLayout = new QVBoxLayout();

        QHBoxLayout* upperButtonsLayout = new QHBoxLayout();
        QVBoxLayout* mainButtonsLayout = new QVBoxLayout();
        editButton = new QPushButton("Modifica", this);
        deleteButton = new QPushButton("Elimina", this);
        simulateButton = new QPushButton("Nuova simulazione", this);
        upperButtonsLayout->addWidget(editButton, 0, Qt::AlignRight);
        upperButtonsLayout->addWidget(deleteButton, 0, Qt::AlignLeft);
        mainButtonsLayout->addLayout(upperButtonsLayout);
        mainButtonsLayout->addWidget(simulateButton, 0, Qt::AlignHCenter);

        // Connessioni
        /// Modifica
        connect(editButton, &QPushButton::clicked, this, &SensorView::editSensor);
        /// Elimina
        connect(deleteButton, &QPushButton::clicked, this, &SensorView::deleteSensor);
        /// Simula
        connect(simulateButton, &QPushButton::clicked, this, &SensorView::startSimulation);

        details = new SensorDetails(sensor, this);

        // Bottoni e grafico
        if(!sensor) {
            editButton->setEnabled(false);
            deleteButton->setEnabled(false);
            simulateButton->setEnabled(false);
            chartViewer = new QChartView(this);
        } else {
            sensor->addObserver(this);
            Charts::ChartsVisitor chartVisitor;
            sensor->accept(chartVisitor);
            chartViewer = new QChartView(chartVisitor.getSensorChart(), this);
            chartViewer->setRenderHint(QPainter::Antialiasing, true);             //Utilizzato per migliorare l'aspetto del grafico
        }

        mainLayout->addWidget(details);
        mainLayout->addLayout(mainButtonsLayout);
        mainLayout->addWidget(chartViewer);

        this->setLayout(mainLayout);
    }

    const Sensors::AbstractSensor* SensorView::getSensor() {
        return sensor;
    }

    void SensorView::notify(Sensors::AbstractSensor &sensor) {
        chartViewer->chart()->deleteLater();
        Charts::ChartsVisitor cVisitor;
        sensor.accept(cVisitor);
        chartViewer->setChart(cVisitor.getSensorChart());
        chartViewer->update();
    }

    void SensorView::destructor() {
        sensor = nullptr;
    }

    SensorView::~SensorView() {
        if(sensor)
            sensor->removeObserver(this);
    }

    void SensorView::editSensor() {
        if(dynamic_cast<Sensors::Hygrometer*>(sensor)) {
            Dialogs::EditHygrometerWindow* editWindow = new Dialogs::EditHygrometerWindow(dynamic_cast<Sensors::Hygrometer*>(sensor), this);
            editWindow->setWindowTitle("Modifica sensore");

            editWindow->setAttribute(Qt::WA_DeleteOnClose); /// elimina alla chiusura
            editWindow->exec();

            if(editWindow->result())
                emit unsavedChanges();
        } else if(dynamic_cast<Sensors::Manometer*>(sensor)) {
            Dialogs::EditManometerWindow* editWindow = new Dialogs::EditManometerWindow(dynamic_cast<Sensors::Manometer*>(sensor), this);
            editWindow->setWindowTitle("Modifica sensore");

            editWindow->setAttribute(Qt::WA_DeleteOnClose); /// elimina alla chiusura
            editWindow->exec();

            if(editWindow->result())
                emit unsavedChanges();
        } else if(dynamic_cast<Sensors::ParticleCounter*>(sensor)) {
            Dialogs::EditParticleCounterWindow* editWindow = new Dialogs::EditParticleCounterWindow(dynamic_cast<Sensors::ParticleCounter*>(sensor), this);
            editWindow->setWindowTitle("Modifica sensore");

            editWindow->setAttribute(Qt::WA_DeleteOnClose); /// elimina alla chiusura
            editWindow->exec();

            if(editWindow->result())
                emit unsavedChanges();
        }
    }

    void SensorView::deleteSensor() {
        Dialogs::DeleteSensorWindow* deleteWindow = new Dialogs::DeleteSensorWindow(sensor, this);
        deleteWindow->setWindowTitle("Elimina sensore");

        deleteWindow->setAttribute(Qt::WA_DeleteOnClose);   /// elimina alla chiusura
        connect(deleteWindow, &Dialogs::DeleteSensorWindow::deleteButtonPressed, this, &SensorView::deleteButtonPressed);
        deleteWindow->exec();
    }

    void SensorView::startSimulation() {
        sensor->simulate();
        emit unsavedChanges();
    }
}
