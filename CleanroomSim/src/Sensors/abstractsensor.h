#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <string>
#include <vector>
#include "sensorobserver.h"
#include "sensorvisitor.h"

namespace Sensors {

    class AbstractSensor
    {
    private:
        //Attributi
        unsigned int identifier;    /// identificatore
        std::string name;   /// nome
        std::string description;    /// descrizione
        bool plugged;   /// true se non necessita batteria
        unsigned int batteryPercentage; /// livello batteria

    protected:
        std::vector<SensorObserver*> observersList; /// elenco observers

    public:
        // Costruttori
        AbstractSensor(const unsigned int& identifier, const std::string& name, const std::string description = "", const bool& plugged = true, const unsigned int& batteryPercentage = 100);
        AbstractSensor(const AbstractSensor& other);

        // Getters e setters
        unsigned int getIdentifier() const;
        std::string getName() const;
        std::string getDescription() const;
        bool isPlugged() const;
        unsigned int getBatteryPercentage() const;
        void setIdentifier(const unsigned int& newIdentifier);
        void setName(const std::string &newName);
        void setDescription(const std::string &newDescription);
        void setPlugged(const bool& newPlugged = true);
        void setBatteryPercentage(const unsigned int& newBatteryPercentage = 100);

        // Gestione observers e visitors
        void addObserver(SensorObserver* sensorObserver);
        void removeObserver(SensorObserver* sensorObserver);
        virtual void accept(SensorVisitor& sensorVisitor) const = 0;

        // Gestione astratta simulazione
        /**
         * @brief generateSimulation: genera raccolta dati random
         */
        virtual void generateSimulation() = 0;
        /**
         * @brief simulate: fa partire una nuova simulazione con raccolta dati ed eventuale aggiornamento delle statistiche
         */
        virtual void simulate() = 0;

        // Distruttore
        virtual ~AbstractSensor();
    };

}

#endif // ABSTRACTSENSOR_H
