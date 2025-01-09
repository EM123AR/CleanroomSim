#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "Sensors/abstractsensor.h"
#include "sensordetails.h"
#include <QWidget>
#include <QPushButton>
#include <QChartView>
#include <QLabel>

namespace View {

class SensorView : public QWidget, public Sensors::SensorObserver
    {
        Q_OBJECT

    private:
        // Attributi
        Sensors::AbstractSensor* sensor;    /// sensore da visualizzare
        SensorDetails* details; /// vista dettagliata
        QLabel* nameLabel;  /// nome sensore
        QLabel* descriptionLabel;   /// descrizione sensore
        QWidget* iconWidget;    /// icona sensore
        QWidget* infoWidget;    /// informazioni
        QPushButton* editButton;    /// bottone modifica
        QPushButton* deleteButton;  /// bottone elimina
        QPushButton* simulateButton;    /// bottone simula
        QChartView* chartViewer;    /// grafico dati simulazione

    public:
        // Costruttori
        SensorView(Sensors::AbstractSensor* sensor = nullptr, QWidget* parent = nullptr);

        // Getters
        const Sensors::AbstractSensor* getSensor();

        // Gestione observers
        void notify(Sensors::AbstractSensor& sensor) override;
        void destructor() override;

        // Distruttori
        ~SensorView();

    signals:
        // Gestione segnali
        void deleteButtonPressed(Sensors::AbstractSensor* sensor);
        void unsavedChanges();

    private slots:
        // Gestione slots
        void editSensor();
        void deleteSensor();
        void startSimulation();
    };

}

#endif // SENSORVIEW_H
