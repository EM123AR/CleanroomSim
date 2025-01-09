#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

namespace Sensors {

    class Hygrometer;
    class Manometer;
    class ParticleCounter;

    class SensorVisitor
    {
    public:
        // Costruttori
        SensorVisitor() = default;

        // Gestione astratta visitors
        virtual void visit(const Hygrometer& sensorH) = 0;
        virtual void visit(const Manometer& sensorM) = 0;
        virtual void visit(const ParticleCounter& sensorPC) = 0;

        // Distruttori
        virtual ~SensorVisitor() = default;
    };

}

#endif // SENSORVISITOR_H
