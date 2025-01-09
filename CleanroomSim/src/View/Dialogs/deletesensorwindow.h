#ifndef DELETESENSORWINDOW_H
#define DELETESENSORWINDOW_H

#include <QDialog>
#include <QLabel>
#include "Sensors/abstractsensor.h"

namespace View {
namespace Dialogs {

    class DeleteSensorWindow : public QDialog
    {
        Q_OBJECT

    private:
        // Attributi
        QLabel* type;   /// tipo sensore
        QLabel* name;   /// nome sensore
        QLabel* description;    /// descrizione sensore

        QPushButton* confirmButton; /// bottone cancella
        QPushButton* cancelButton;  /// bottone annulla

        Sensors::AbstractSensor* sensor;    /// sensore da cancellare

    public:
        // Costruttori
        DeleteSensorWindow(Sensors::AbstractSensor* sensor, QWidget* parent = nullptr);

        // Getters
        QString getName() const;
        QString getDescription() const;

        // Distruttori
        ~DeleteSensorWindow() = default;

    signals:
        // Gestione segnali
        void deleteButtonPressed(Sensors::AbstractSensor* sensor);

    private slots:
        // Gestione slots
        void deleteSensor();
    };

}
}

#endif // DELETESENSORWINDOW_H
