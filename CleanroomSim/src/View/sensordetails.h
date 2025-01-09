#ifndef SENSORDETAILS_H
#define SENSORDETAILS_H

#include <QWidget>
#include "Sensors/sensorobserver.h"
#include <QLabel>

namespace View {

    class SensorDetails : public QWidget, public Sensors::SensorObserver
    {
        Q_OBJECT

    private:
        // Attributi
        Sensors::AbstractSensor* sensor;    /// sensore da visualizzare
        QLabel* name;   /// nome sensore
        QLabel* description;    /// descrizione sensore
        QWidget* iconWidget;    /// icona
        QWidget* infoWidget;    /// informazioni

    public:
        // Costruttori
        SensorDetails(Sensors::AbstractSensor* sensor, QWidget* parent = nullptr);

        // Gestione observers
        void notify(Sensors::AbstractSensor& sensor) override;
        void destructor() override;

        // Distruttori
        ~SensorDetails();
    };

}

#endif // SENSORDETAILS_H
