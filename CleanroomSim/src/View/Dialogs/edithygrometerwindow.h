#ifndef EDITHYGROMETERWINDOW_H
#define EDITHYGROMETERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSlider>
#include <QCheckBox>
#include "Sensors/hygrometer.h"

namespace View {
namespace Dialogs {

    class EditHygrometerWindow : public QDialog
    {
        Q_OBJECT

    private:
        // Attributi
        QLabel* type;   /// tipo sensore
        QLineEdit* name;    /// nome sensore
        QTextEdit* description; /// descrizione sensore
        QSlider* desiredAvg;    /// media desiderata sensore
        QCheckBox* plugged; /// sensore collegato alla rete elettrica

        QPushButton* confirmButton; /// bottone modifica
        QPushButton* cancelButton;  /// bottone annulla

        Sensors::Hygrometer* sensor;    /// sensore da modificare

        QLabel* policy; /// avviso campi obbligatori

    public:
        // Costruttori
        EditHygrometerWindow(Sensors::Hygrometer* sensor, QWidget* parent = nullptr);

        // Distruttori
        ~EditHygrometerWindow() = default;

    private slots:
        // Gestione slots
        void editSensor();

        void sensorNameChanged(const QString& text);
    };

}
}

#endif // EDITHYGROMETERWINDOW_H
