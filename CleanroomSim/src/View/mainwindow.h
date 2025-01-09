#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "toolbar.h"
#include "sensorslist.h"
#include "sensorview.h"

namespace View {

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        // Attributi
        QSplitter* mainSplitter;    /// splitter principale finestra
        Toolbar* toolbar;   /// barra strumenti
        SensorsList* sensorsList;   /// lista dei sensori in memoria corrente che rispettano il filtro
        SensorView* sensorView; /// area vista sensori
        Sensors::Storage::Archive* cache;   /// memoria corrente

        // Ridefinizione evento di chiusura
        void closeEvent(QCloseEvent *event) override;

        // Messaggio di avviso personalizzato
        int showWarningMessageBox(QString message);

    public:
        // Costruttori
        MainWindow(QWidget* parent = nullptr);

        // Distruttori
        ~MainWindow();

    private slots:
        // Gestione slots
        /**
         * @brief addSensor: aggiunta sensore da cache
         * @param sensor: sensore da aggiungere
         */
        void addSensor(Sensors::AbstractSensor* sensor);
        /**
         * @brief deleteSensor: eliminazione sensore da cache
         * @param sensor: sensore da eliminare
         */
        void deleteSensor(Sensors::AbstractSensor* sensor);
        /**
         * @brief showSensor: mostra sensore
         * @param sensor: sensore da mostrare
         */
        void showSensor(Sensors::AbstractSensor* sensor);
        /**
         * @brief open: apri file Json da caricare in cache
         */
        void open();
        /**
         * @brief save: salva cache nel file Json aperto/di default
         */
        void save();
        /**
         * @brief saveAs: salva cache nel file Json specificato
         */
        void saveAs();
        /**
         * @brief unsavedChanges: slot delle modifiche da salvare
         */
        void unsavedChanges();
    };

}

#endif // MAINWINDOW_H
