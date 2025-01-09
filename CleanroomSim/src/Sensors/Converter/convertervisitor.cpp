#include "convertervisitor.h"
#include <QJsonArray>
#include "Sensors/particles.h"

namespace Sensors {
namespace Converter {

    ConverterVisitor::ConverterVisitor()
    : content(nullptr) {

    }

    QJsonObject* ConverterVisitor::getContent() const {
        return content;
    }

    void ConverterVisitor::visit(const Hygrometer& sensorH) {
        content = new QJsonObject();

        (*content)["Type"] = "Hygrometer";

        QJsonArray dataValues;
        for(const double& val : *(sensorH.getData()))
            dataValues.push_back(val);
        (*content)["Data"] = dataValues;

        (*content)["Avg"] = sensorH.getAvg();
        (*content)["OptimalAvg"] = sensorH.getOptimalAvg();
    }

    void ConverterVisitor::visit(const Manometer& sensorM) {
        content = new QJsonObject();

        (*content)["Type"] = "Manometer";

        QJsonArray dataValues;
        for(const int& val : *(sensorM.getData()))
            dataValues.push_back(val);
        (*content)["Data"] = dataValues;

        (*content)["Threshold"] = sensorM.getThreshold();

        (*content)["Man"] = sensorM.getMan();
    }

    void ConverterVisitor::visit(const ParticleCounter& sensorPC) {
        content = new QJsonObject();

        (*content)["Type"] = "ParticleCounter";

        QJsonArray dataValues;
        for(const Particles& val : *(sensorPC.getData())) {
            QJsonObject particlesData;
            particlesData["DotOneumCount"] = val.getDotOneumCount();
            particlesData["DotTwoumCount"] = val.getDotTwoumCount();
            particlesData["DotThreeumCount"] = val.getDotThreeumCount();
            particlesData["DotFiveumCount"] = val.getDotFiveumCount();
            particlesData["OneumCount"] = val.getOneumCount();
            particlesData["FiveumCount"] = val.getFiveumCount();
            dataValues.push_back(particlesData);
        }
        (*content)["Data"] = dataValues;

        QJsonObject particlesMax;
        particlesMax["DotOneumCount"] = sensorPC.getMax()->getDotOneumCount();
        particlesMax["DotTwoumCount"] = sensorPC.getMax()->getDotTwoumCount();
        particlesMax["DotThreeumCount"] = sensorPC.getMax()->getDotTwoumCount();
        particlesMax["DotFiveumCount"] = sensorPC.getMax()->getDotFiveumCount();
        particlesMax["OneumCount"] = sensorPC.getMax()->getOneumCount();
        particlesMax["FiveumCount"] = sensorPC.getMax()->getFiveumCount();
        (*content)["Max"] = particlesMax;

        QJsonObject particlesMin;
        particlesMin["DotOneumCount"] = sensorPC.getMin()->getDotOneumCount();
        particlesMin["DotTwoumCount"] = sensorPC.getMin()->getDotTwoumCount();
        particlesMin["DotThreeumCount"] = sensorPC.getMin()->getDotTwoumCount();
        particlesMin["DotFiveumCount"] = sensorPC.getMin()->getDotFiveumCount();
        particlesMin["OneumCount"] = sensorPC.getMin()->getOneumCount();
        particlesMin["FiveumCount"] = sensorPC.getMin()->getFiveumCount();
        (*content)["Min"] = particlesMin;

        QJsonObject particlesAvg;
        particlesAvg["DotOneumCount"] = sensorPC.getAvg()->getDotOneumCount();
        particlesAvg["DotTwoumCount"] = sensorPC.getAvg()->getDotTwoumCount();
        particlesAvg["DotThreeumCount"] = sensorPC.getAvg()->getDotTwoumCount();
        particlesAvg["DotFiveumCount"] = sensorPC.getAvg()->getDotFiveumCount();
        particlesAvg["OneumCount"] = sensorPC.getAvg()->getOneumCount();
        particlesAvg["FiveumCount"] = sensorPC.getAvg()->getFiveumCount();
        (*content)["Avg"] = particlesAvg;

        (*content)["DesiredStandard"] = static_cast<int>(sensorPC.getDesiredStandard());
    }
}
}
