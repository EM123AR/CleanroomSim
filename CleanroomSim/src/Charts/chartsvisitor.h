#ifndef CHARTSVISITOR_H
#define CHARTSVISITOR_H

#include "Sensors/sensorvisitor.h"
#include <QChart>

namespace Charts {
    class ChartsVisitor : public Sensors::SensorVisitor
    {
    private:
        // Attributi
        QChart *sensorChart;    /// grafico risultante

    public:
        // Costruttori
        ChartsVisitor();

        // Getters
        QChart* getSensorChart();

        // Gestione visitors
        void visit(const Sensors::Hygrometer& sensorH) override;
        void visit(const Sensors::Manometer& sensorM) override;
        void visit(const Sensors::ParticleCounter& sensorPC) override;

        // Distruttori
        ~ChartsVisitor() = default;
    };

}

#endif // CHARTSVISITOR_H
