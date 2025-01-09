#ifndef MANOMETER_H
#define MANOMETER_H

#include "abstractsensor.h"
/* inlcusi in abstractsensor.h:
 #include <string>
 #include <vector>
 #include "sensorobserver.h"
 #include "sensorvisitor.h"
*/

namespace Sensors {

    class Manometer : public AbstractSensor
    {
    private:
        // Attributi
        std::vector<int> data;  /// dati raccolti
        int threshold;  /// pressione desiderata in Pascal
        double man; /// Mean Absolute Deviation in Pascal / deviazione media assoluta rispetto a soglia

    public:
        // Costruttori
        Manometer(const unsigned int& identifier, const std::string& name, const std::string description = "",  const bool& plugged = true, const unsigned int& batteryPercentage = 100);
        Manometer(const Manometer& other);

        // Getters e setters
        const std::vector<int>* getData() const;
        int getThreshold() const;
        double getMan() const;
        void setData(const std::vector<int> &newData);
        void setThreshold(const int& newThreshold);
        void setMan(const double& newMan);

        // Gestione visitors
        virtual void accept(SensorVisitor& sensorVisitor) const final override;

        // Gestione simulazione
        /**
         * @brief updateMan: aggiorna deviazione media assoluta rispetto a soglia
         */
        void updateMan();
        /**
         * @brief generateSimulation: genera raccolta dati random in base alla soglia
         */
        void generateSimulation() override;
        /**
         * @brief simulate: fa partire una nuova simulazione con raccolta dati ed eventuale aggiornamento delle statistiche
         */
        void simulate() override;

        // Distruttori
        ~Manometer() = default;
    };

}

#endif // MANOMETER_H
