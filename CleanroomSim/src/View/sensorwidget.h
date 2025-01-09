#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QFrame>
#include "Sensors/sensorobserver.h"
#include <QLabel>

namespace View {

    class SensorWidget : public QFrame, public Sensors::SensorObserver
    {
        Q_OBJECT

    private:
        // Attributi
        QLabel* nameLabel;  /// nome sensore
        QLabel* descriptionLabel;   /// descrizione sensore
        QWidget* iconWidget;    /// icona sensore
        QWidget* warningIconWidget; /// icona valori anomali
        QWidget* batteryIconWidget; /// icona stato batteria
        Sensors::AbstractSensor* sensor;    /// sensore di riferimento

    public:
        // Costruttori
        SensorWidget(Sensors::AbstractSensor* sensor, QWidget* parent = nullptr);

        // Gettesr e setters
        Sensors::AbstractSensor* getSensor();
        const Sensors::AbstractSensor* getSensorConst() const;
        void setSensor(Sensors::AbstractSensor* sensor);

        // Ridefinizione clic mouse
        void mousePressEvent(QMouseEvent* event) override;

        // Gestione observers
        void notify(Sensors::AbstractSensor& sensor) override;
        void destructor() override;

        // Distruttori
        ~SensorWidget();

    signals:
        // Gestione segnali
        void mousePressed(Sensors::AbstractSensor*);
    };

}

#endif // SENSORWIDGET_H
