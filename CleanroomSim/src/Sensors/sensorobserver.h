#ifndef SENSOROBSERVER_H
#define SENSOROBSERVER_H

namespace Sensors {

    class AbstractSensor;

    class SensorObserver
    {
    public:
        // Costruttori
        SensorObserver() = default;

        // Gestione astratta observers
        virtual void notify(AbstractSensor& sensor) = 0;
        virtual void destructor() = 0;

        // Distruttori
        virtual ~SensorObserver() = default;
    };

}

#endif // SENSOROBSERVER_H
