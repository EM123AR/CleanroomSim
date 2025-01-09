#ifndef ADDSENSORWINDOW_H
#define ADDSENSORWINDOW_H

#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include "Sensors/abstractsensor.h"

namespace View {
namespace Dialogs {

    class AddSensorWindow : public QDialog
    {
        Q_OBJECT

    private:
        // Attributi
        QComboBox* type;    /// tipo sensore
        QLineEdit* name;    /// nome sensore
        QTextEdit* description; /// descrizione sensore

        QPushButton* confirmButton; /// bottone per aggiungere
        QPushButton* cancelButton;  /// bottone per annullare

        QLabel* policy; /// avviso sui campi obbligatori

    public:
        // Costruttori
        AddSensorWindow(QWidget* parent = nullptr);

        // Getters
        QString getName() const;
        QString getDescription() const;

        // Distruttori
        ~AddSensorWindow() = default;

    signals:
        // Gestione segnali
        void addButtonPressed(Sensors::AbstractSensor* sensor);

    private slots:
        // Gestione slots
        void addSensor();

        void sensorTypeChanged(const int index);

        void sensorNameChanged(const QString& text);
    };

}
}

#endif // ADDSENSORWINDOW_H
