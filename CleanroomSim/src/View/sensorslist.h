#ifndef SENSORSLIST_H
#define SENSORSLIST_H

#include "Sensors/abstractsensor.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QScrollArea>
#include "Sensors/Storage/archive.h"

namespace View {

class SensorsList : public QWidget, public Sensors::Storage::ArchiveObserver
    {
        Q_OBJECT

    private:
        // Attributi
        QPushButton* searchButton;  /// bottone ricerca
        QLineEdit* searchBox;   /// casella di testo del filtro ricerca
        QLabel* sensorsCount;   /// contatore sensori filtrati
        QScrollArea* panel; /// elenco sensori filtrati
        QPushButton* addButton; /// bottone aggiungi sensore
        Sensors::Storage::Archive* cache;   /// memoria corrente

    public:
        // Costruttori
        SensorsList(Sensors::Storage::Archive* cache, QWidget* parent = nullptr);

        // Getters e setters
        QString getFilterText() const;
        void setFilterText(QString filterText);

        // Gestione lista
        /**
         * @brief update: aggiorna il panel in base ad un vettore di sensori che rispetta il filtro
         * @param sensors: sensori che rispettano il filtro
         */
        void update(const std::vector<Sensors::AbstractSensor*>* sensors);

        // Gestione observers
        void notify(Sensors::Storage::Archive& archive) override;
        void destructor() override;

        // Distruttori
        ~SensorsList();

    signals:
        // Gestione segnali
        void addButtonPressed(Sensors::AbstractSensor* sensor);
        /**
         * @brief widgetPressed: widget sensore premuto
         * @param sensor: sensore premuto
         */
        void widgetPressed(Sensors::AbstractSensor* sensor);

    private slots:
        // Gestione slots
        void addSensor();
        void openWidget(Sensors::AbstractSensor* sensor);

    public slots:
        void filter();
    };

}

#endif // SENSORSLIST_H
