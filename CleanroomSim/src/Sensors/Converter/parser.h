#ifndef PARSER_H
#define PARSER_H

#include "Sensors/abstractsensor.h"
#include <QJsonObject>

namespace Sensors {
namespace Converter {

    class Parser
    {
    private:
        // Attributi
        Sensors::AbstractSensor* resultingSensor;   /// sensore convertito da Json

    public:
        // Costruttori
        Parser(QJsonObject genericJsonSensor);

        // Getters
        Sensors::AbstractSensor* getResultingSensor() const;

        // Costruzione sensori
        void buildHygrometer(QJsonObject genericJsonSensor);
        void buildManometer(QJsonObject genericJsonSensor);
        void buildParticleCounter(QJsonObject genericJsonSensor);

        // Distruttori
        ~Parser() = default;
    };

}
}

#endif // PARSER_H
