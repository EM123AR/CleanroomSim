#include "parser.h"
#include <QJsonArray>
#include "Sensors/hygrometer.h"
#include "Sensors/manometer.h"
#include "Sensors/particlecounter.h"

namespace Sensors {
namespace Converter {

    Parser::Parser(QJsonObject genericJsonSensor)
    : resultingSensor(nullptr) {
        QString jsonSensorType = genericJsonSensor.value("Type").toString();

        if(jsonSensorType == "Hygrometer")
            buildHygrometer(genericJsonSensor);
        else if(jsonSensorType == "Manometer")
            buildManometer(genericJsonSensor);
        else if(jsonSensorType == "ParticleCounter")
            buildParticleCounter(genericJsonSensor);

    }

    Sensors::AbstractSensor* Parser::getResultingSensor() const {
        return resultingSensor;
    }

    void Parser::buildHygrometer(QJsonObject genericJsonSensor) {
        unsigned int identifier = genericJsonSensor.value("Identifier").toInt();
        QString name = genericJsonSensor.value("Name").toString();
        QString description = genericJsonSensor.value("Description").toString();
        bool plugged = genericJsonSensor.value("Plugged").toBool();
        unsigned int batteryPercentage = genericJsonSensor.value("BatteryPercentage").toInt();
        resultingSensor = new Sensors::Hygrometer(identifier, name.toStdString(), description.toStdString(), plugged, batteryPercentage);

        QJsonArray jsonData = genericJsonSensor.value("Data").toArray();
        std::vector<double> data;
        for(const QJsonValue& val : jsonData)
            data.push_back(val.toDouble());

        static_cast<Sensors::Hygrometer*>(resultingSensor)->setData(data);

        double avg = genericJsonSensor.value("Avg").toDouble();
        static_cast<Sensors::Hygrometer*>(resultingSensor)->setAvg(avg);

        double optimalAvg = genericJsonSensor.value("OptimalAvg").toDouble();
        static_cast<Sensors::Hygrometer*>(resultingSensor)->setOptimalAvg(optimalAvg);
    }

    void Parser::buildManometer(QJsonObject genericJsonSensor) {
        unsigned int identifier = genericJsonSensor.value("Identifier").toInt();
        QString name = genericJsonSensor.value("Name").toString();
        QString description = genericJsonSensor.value("Description").toString();
        bool plugged = genericJsonSensor.value("Plugged").toBool();
        unsigned int batteryPercentage = genericJsonSensor.value("BatteryPercentage").toInt();
        resultingSensor = new Sensors::Manometer(identifier, name.toStdString(), description.toStdString(), plugged, batteryPercentage);

        QJsonArray jsonData = genericJsonSensor.value("Data").toArray();
        std::vector<int> data;
        for(const QJsonValue& val : jsonData)
            data.push_back(val.toInt());

        static_cast<Sensors::Manometer*>(resultingSensor)->setData(data);

        int threshold = genericJsonSensor.value("Threshold").toInt();
        static_cast<Sensors::Manometer*>(resultingSensor)->setThreshold(threshold);

        double man = genericJsonSensor.value("Man").toDouble();
        static_cast<Sensors::Manometer*>(resultingSensor)->setMan(man);
    }

    void Parser::buildParticleCounter(QJsonObject genericJsonSensor) {
        unsigned int identifier = genericJsonSensor.value("Identifier").toInt();
        QString name = genericJsonSensor.value("Name").toString();
        QString description = genericJsonSensor.value("Description").toString();        
        bool plugged = genericJsonSensor.value("Plugged").toBool();
        unsigned int batteryPercentage = genericJsonSensor.value("BatteryPercentage").toInt();
        resultingSensor = new Sensors::ParticleCounter(identifier, name.toStdString(), description.toStdString(), plugged, batteryPercentage);

        QJsonArray jsonData = genericJsonSensor.value("Data").toArray();
        std::vector<Particles> data;
        for(const QJsonValue& val : jsonData) {
            QJsonObject obj = val.toObject();

            int dotOneumCount = obj.value("DotOneumCount").toInt();
            int dotTwoumCount = obj.value("DotTwoumCount").toInt();
            int dotThreeumCount = obj.value("DotThreeumCount").toInt();
            int dotFiveumCount = obj.value("DotFiveumCount").toInt();
            int oneumCount = obj.value("OneumCount").toInt();
            int fiveumCount = obj.value("FiveumCount").toInt();

            data.push_back(Particles(dotOneumCount, dotTwoumCount, dotThreeumCount, dotFiveumCount, oneumCount, fiveumCount));
        }

        static_cast<Sensors::ParticleCounter*>(resultingSensor)->setData(data);

        QJsonObject max = genericJsonSensor.value("Max").toObject();
        int dotOneumCount = max.value("DotOneumCount").toInt();
        int dotTwoumCount = max.value("DotTwoumCount").toInt();
        int dotThreeumCount = max.value("DotThreeumCount").toInt();
        int dotFiveumCount = max.value("DotFiveumCount").toInt();
        int oneumCount = max.value("OneumCount").toInt();
        int fiveumCount = max.value("FiveumCount").toInt();
        static_cast<Sensors::ParticleCounter*>(resultingSensor)->setMax(Particles(
            dotOneumCount, dotTwoumCount, dotThreeumCount, dotFiveumCount, oneumCount, fiveumCount));

        QJsonObject min = genericJsonSensor.value("Min").toObject();
        dotOneumCount = min.value("DotOneumCount").toInt();
        dotTwoumCount = min.value("DotTwoumCount").toInt();
        dotThreeumCount = min.value("DotThreeumCount").toInt();
        dotFiveumCount = min.value("DotFiveumCount").toInt();
        oneumCount = min.value("OneumCount").toInt();
        fiveumCount = min.value("FiveumCount").toInt();
        static_cast<Sensors::ParticleCounter*>(resultingSensor)->setMin(Particles(
            dotOneumCount, dotTwoumCount, dotThreeumCount, dotFiveumCount, oneumCount, fiveumCount));

        QJsonObject avg = genericJsonSensor.value("Avg").toObject();
        dotOneumCount = avg.value("DotOneumCount").toInt();
        dotTwoumCount = avg.value("DotTwoumCount").toInt();
        dotThreeumCount = avg.value("DotThreeumCount").toInt();
        dotFiveumCount = avg.value("DotFiveumCount").toInt();
        oneumCount = avg.value("OneumCount").toInt();
        fiveumCount = avg.value("FiveumCount").toInt();
        static_cast<Sensors::ParticleCounter*>(resultingSensor)->setAvg(Particles(
            dotOneumCount, dotTwoumCount, dotThreeumCount, dotFiveumCount, oneumCount, fiveumCount));

        unsigned int desiredStandard = genericJsonSensor.value("DesiredStandard").toInt();
        static_cast<Sensors::ParticleCounter*>(resultingSensor)->setDesiredStandard(desiredStandard);
    }
}
}
