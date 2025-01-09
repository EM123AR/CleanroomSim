#ifndef EDITPARTICLECOUNTERWINDOW_H
#define EDITPARTICLECOUNTERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include "Sensors/particlecounter.h"

namespace View {
namespace Dialogs {

    class EditParticleCounterWindow : public QDialog
    {
        Q_OBJECT

    private:
        // Attributi
        QLabel* type;   /// tipo sensore
        QLineEdit* name;    /// nome sensore
        QTextEdit* description; /// descrizione sensore
        QComboBox* standard;    /// standard desiderato sensore
        QCheckBox* plugged; /// true se sensore collegato alla rete elettrica

        QPushButton* confirmButton; /// bottone modifica
        QPushButton* cancelButton;  /// bottone annulla

        Sensors::ParticleCounter* sensor;   /// sensore da modificare

        QLabel* policy; /// avviso campi obbligatori

    public:
        // Costruttori
        EditParticleCounterWindow(Sensors::ParticleCounter* sensor, QWidget* parent = nullptr);

        // Distruttori
        ~EditParticleCounterWindow() = default;

    private slots:
        // Gestione slots
        void editSensor();

        void sensorNameChanged(const QString& text);
    };

}
}

#endif // EDITPARTICLECOUNTERWINDOW_H
