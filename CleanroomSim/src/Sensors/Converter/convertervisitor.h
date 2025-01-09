#ifndef CONVERTERVISITOR_H
#define CONVERTERVISITOR_H

#include "Sensors/sensorvisitor.h"
#include <QJsonObject>
#include "Sensors/hygrometer.h"
#include "Sensors/manometer.h"
#include "Sensors/particlecounter.h"

namespace Sensors {
namespace Converter {

    class ConverterVisitor : public Sensors::SensorVisitor
    {
    private:
        // Attributi
        QJsonObject* content;   /// contenuto sensore da convertire in Json

    public:
        // Costruttori
        ConverterVisitor();

        // Getters
        QJsonObject* getContent() const;

        // Gestione visitors
        void visit(const Hygrometer& sensorH) override;
        void visit(const Manometer& sensorM) override;
        void visit(const ParticleCounter& sensorPC) override;

        // Distruttori
        ~ConverterVisitor() = default;
    };

}
}

#endif // CONVERTERVISITOR_H
