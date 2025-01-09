#ifndef EDITMANOMETERWINDOW_H
#define EDITMANOMETERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "Sensors/manometer.h"

namespace View {
namespace Dialogs {

    class EditManometerWindow : public QDialog
    {
        Q_OBJECT

    private:
        // Attributi
        QLabel* type;   /// tipo sensore
        QLineEdit* name;    /// nome sensore
        QTextEdit* description; /// descrizione sensore
        QSpinBox* threshold;    /// soglia desiderata sensore
        QCheckBox* plugged; /// true se sensore collegato alla rete elettrica

        QPushButton* confirmButton; /// bottone modifica
        QPushButton* cancelButton; /// bottone annulla

        Sensors::Manometer* sensor; /// sensore da modificare

        QLabel* policy; /// avviso campi obbligatori

    public:
        // Costruttori
        EditManometerWindow(Sensors::Manometer* sensor, QWidget* parent = nullptr);

        // Distruttori
        ~EditManometerWindow() = default;

    private slots:
        // Gestione slots
        void editSensor();

        void sensorNameChanged(const QString& text);
    };

}
}

#endif // EDITMANOMETERWINDOW_H
