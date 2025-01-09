#ifndef PARTICLECOUNTER_H
#define PARTICLECOUNTER_H

#include "abstractsensor.h"
/* inlcusi in abstractsensor.h:
 #include <string>
 #include <vector>
 #include "sensorobserver.h"
 #include "sensorvisitor.h"
*/
#include "particles.h"

namespace Sensors {

    class ParticleCounter : public AbstractSensor
    {
    private:
        // Attributi
        std::vector<Particles> data; /// dati raccolti
        Particles max;  /// conteggio massimo per ciascun diametro
        Particles min;  /// conteggio minimo per ciascun diametro
        Particles avg;  /// conteggio medio
        unsigned int desiredStandard;   /// livello standard ISO desiderato

    public:
        // Costruttori
        ParticleCounter(const unsigned int& identifier, const std::string& name, const std::string description = "", const bool& plugged = true, const unsigned int& batteryPercentage = 100);
        ParticleCounter(const ParticleCounter& other);

        // Getters e setters
        const std::vector<Particles>* getData() const;
        const Particles* getMax() const;
        const Particles* getMin() const;
        const Particles* getAvg() const;
        unsigned int getDesiredStandard() const;
        void setData(const std::vector<Particles> &newData);
        void setMax(const Particles& newMax);
        void setMin(const Particles& newMin);
        void setAvg(const Particles& newAvg);
        void setDesiredStandard(const unsigned int& newDesiredStandard);

        // Gestione visitors
        virtual void accept(SensorVisitor& sensorVisitor) const final override;

        // Gestione simulazione
        /**
         * @brief updateMax: aggiorna conteggio massimo
         */
        void updateMax();
        /**
         * @brief updateMin: aggiorna conteggio minimo
         */
        void updateMin();
        /**
         * @brief updateAvg: aggiorna conteggio medio
         */
        void updateAvg();
        /**
         * @brief updateStats: aggiorna tutte le statistiche
         */
        void updateStats();
        /**
         * @brief generateSimulation: genera raccolta dati random in base allo standard
         */
        void generateSimulation() override;
        /**
         * @brief simulate: fa partire una nuova simulazione con raccolta dati ed eventuale aggiornamento delle statistiche
         */
        void simulate() override;

        // Distruttore
        ~ParticleCounter() = default;
    };

}

#endif // PARTICLECOUNTER_H
