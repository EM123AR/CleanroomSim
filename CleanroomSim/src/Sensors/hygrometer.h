#ifndef HYGROMETER_H
#define HYGROMETER_H

#include "abstractsensor.h"
/* inlcusi in abstractsensor.h:
 #include <string>
 #include <vector>
 #include "sensorobserver.h"
 #include "sensorvisitor.h"
*/

namespace Sensors {

    class Hygrometer : public AbstractSensor
    {
    private:
        // Attributi
        std::vector<double> data;   /// dati raccolti
        double avg; /// media valori
        double optimalAvg;  /// media ottimale desiderata

    public:
        // Costruttori
        Hygrometer(const unsigned int& identifier, const std::string& name, const std::string description = "", const bool& plugged = true, const unsigned int& batteryPercentage = 100);
        Hygrometer(const Hygrometer& other);

        // Getters e setters
        const std::vector<double>* getData() const;
        double getAvg() const;
        double getOptimalAvg() const;
        void setData(const std::vector<double>& newData);
        void setAvg(const double& newAvg);
        void setOptimalAvg(const double& newOptimalAvg);

        // Gestione visitors
        virtual void accept(SensorVisitor& sensorVisitor) const final override;

        // Gestione simulazione
        /**
         * @brief updateAvg: aggiorna media
         */
        void updateAvg();
        /**
         * @brief generateSimulation: genera raccolta dati random
         */
        void generateSimulation() override;
        /**
         * @brief simulate: fa partire una nuova simulazione con raccolta dati ed eventuale aggiornamento delle statistiche
         */
        void simulate() override;

        // Distruttore
        ~Hygrometer() = default;
    };

}

#endif // HYGROMETER_H
