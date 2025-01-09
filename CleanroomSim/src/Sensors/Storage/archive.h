#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <map>
#include "Sensors/abstractsensor.h"
#include "Sensors/Storage/archiveobserver.h"

namespace Sensors {
namespace Storage {

    class Archive
    {
    private:
        // Attributi
        static unsigned int counter;    /// contatore sensori in memoria corrente

        bool changesSaved = true;   /// true se le modifiche sono salvate

        std::string path;   /// percorso del file di salvataggio

        std::map<unsigned int, Sensors::AbstractSensor*> currentSensors;    /// memoria corrente

        std::vector<ArchiveObserver*> observersList;    /// lista observers

    public:
        // Costruttori
        Archive();

        // Getters e setters
        bool isChangesSaved() const;
        std::string getPath() const;
        std::map<unsigned int, Sensors::AbstractSensor*>* getCurrentSensors();
        const std::map<unsigned int, Sensors::AbstractSensor*>* getCurrentSensorsConst() const;
        void setChangesSaved(bool changesSaved = true);
        void setPath(std::string path);
        void setCurrentSensors(const std::map<unsigned int, Sensors::AbstractSensor*>& currentSensors);

        // Gestione observers
        void addObserver(ArchiveObserver* archiveObserver);
        void removeObserver(ArchiveObserver* archiveObserver);

        // Gestione memoria corrente
        bool isArchiveEmpty() const;
        Sensors::AbstractSensor* getSensorByIdentifier(unsigned int identifier) const;
        void addSensor(Sensors::AbstractSensor* abstractSensor);
        Sensors::AbstractSensor* takeSensorByIdentifier(unsigned int identifier);

        // Metodi d'utilità
        /**
         * @brief getDocumentsPath
         * @return percorso della cartella Documents in base al sistema operativo
         */
        //std::string getDocumentsPath() const;
        /**
         * @brief toLowerCase
         * @param str: stringa da convertire in caratteri minuscoli
         * @return stringa convertita in caratteri minuscoli
         */
        std::string toLowerCase(const std::string& str) const;
        /**
         * @brief sensorsToVector
         * @return sensori in memoria corrente su vector
         */
        std::vector<Sensors::AbstractSensor*>* sensorsToVector() const;

        // Gestione filtro
        const std::vector<std::string>* splitFilterString(std::string filter) const;
        const std::vector<Sensors::AbstractSensor*>* filterName(std::string name) const;

        // Salvataggio e caricamento file
        /**
         * @brief save: salva memoria corrente nel percorso specificato in formato Json
         * @param newPath: se lasciato vuoto si utilizza "[Directory progetto]/CleanroomSim/defaultSave.json"
         */
        void save(std::string newPath = "");
        /**
         * @brief load: carica file Json in memoria corrente
         * @param path: percorso e nome del file Json da caricare
         */
        void load(std::string path);

        // Distruttori
        ~Archive();
    };

}
}

#endif // ARCHIVE_H
