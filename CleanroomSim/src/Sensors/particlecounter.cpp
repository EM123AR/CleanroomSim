#include "particlecounter.h"
#define DEFAULT_DESIRED_STANDARD 3
#define BATTERY_CONSUMPTION 25

namespace Sensors {

    ParticleCounter::ParticleCounter(const unsigned int& identifier, const std::string& name, const std::string description, const bool& plugged, const unsigned int& batteryPercentage)
    : AbstractSensor(identifier, name, description, plugged, batteryPercentage), desiredStandard(DEFAULT_DESIRED_STANDARD) {
        ParticleCounter::generateSimulation();
    }

    ParticleCounter::ParticleCounter(const ParticleCounter& other)
        : AbstractSensor(other.getIdentifier(), other.getName(), other.getDescription(), other.isPlugged(), other.getBatteryPercentage()), data(*(other.getData())), max(*(other.getMax())),
        min(*(other.getMin())), avg(*(other.getAvg())), desiredStandard(other.getDesiredStandard()) {

    }

    const std::vector<Particles>* ParticleCounter::getData() const {
        return &data;
    }

    const Particles* ParticleCounter::getMax() const {
        return &max;
    }

    const Particles* ParticleCounter::getMin() const {
        return &min;
    }

    const Particles* ParticleCounter::getAvg() const {
        return &avg;
    }

    unsigned int ParticleCounter::getDesiredStandard() const {
        return desiredStandard;
    }

    void ParticleCounter::setData(const std::vector<Particles> &newData) {
        data = newData;
    }

    void ParticleCounter::setMax(const Particles& newMax) {
        max = newMax;
    }

    void ParticleCounter::setMin(const Particles& newMin) {
        min = newMin;
    }

    void ParticleCounter::setAvg(const Particles& newAvg) {
        avg = newAvg;
    }

    void ParticleCounter::setDesiredStandard(const unsigned int& newDesiredStandard) {
        desiredStandard = newDesiredStandard;
    }

    void ParticleCounter::accept(SensorVisitor& sensrVisitor) const {
        sensrVisitor.visit(*this);
    }

    void ParticleCounter::updateMax() {
        if(!data.empty()) {
            Particles temp = data[0];
            for(unsigned int i = 1; i < data.size(); ++i)
                temp.generateMaximum(data[i], temp);

            max = temp;
        }
        else max = 0;
    }

    void ParticleCounter::updateMin() {
        if(!data.empty()) {
            Particles temp = data[0];
            for(unsigned int i = 1; i < data.size(); ++i)
                temp.generateMinimum(data[i], temp);

            min = temp;
        }
        else min = 0;
    }

    void ParticleCounter::updateAvg() {
        Particles temp = 0;
        for(unsigned int i = 0; i < data.size(); ++i)
            temp = temp + data[i];

        avg = temp / (data.size() != 0 ? data.size() : 1);
    }

    void ParticleCounter::updateStats() {
        updateMax();
        updateMin();
        updateAvg();
    }

    void ParticleCounter::generateSimulation() {
        data = std::vector<Particles>(20);
        for(auto it = data.begin(); it != data.end(); ++it)
            it->generateSimulation(desiredStandard);

        updateStats();
    }

    void ParticleCounter::simulate() {
        unsigned int batteryP = getBatteryPercentage();

        if(!isPlugged()) {
            if(batteryP > BATTERY_CONSUMPTION) {
                setBatteryPercentage(batteryP - BATTERY_CONSUMPTION);

                generateSimulation();
            } else {
                setBatteryPercentage(0);
            }
        } else {
            generateSimulation();
        }
        for(auto &observer : observersList)
            observer->notify(*this);
    }
}
