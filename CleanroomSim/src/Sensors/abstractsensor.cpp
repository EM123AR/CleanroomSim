#include "abstractsensor.h"
#include <algorithm>

namespace Sensors {

    AbstractSensor::AbstractSensor(const unsigned int& identifier, const std::string& name, const std::string description, const bool& plugged, const unsigned int& batteryPercentage)
    : identifier(identifier), name(name), description(description), plugged(plugged), batteryPercentage(batteryPercentage) {

    }

    AbstractSensor::AbstractSensor(const AbstractSensor& other)
        : identifier(other.getIdentifier()), name(other.getName()), description(other.getDescription()), plugged(other.isPlugged()), batteryPercentage(other.getBatteryPercentage()) {

    }

    unsigned int AbstractSensor::getIdentifier() const {
        return identifier;
    }

    std::string AbstractSensor::getName() const {
        return name;
    }

    std::string AbstractSensor::getDescription() const {
        return description;
    }

    bool AbstractSensor::isPlugged() const {
        return plugged;
    }

    unsigned int AbstractSensor::getBatteryPercentage() const {
        return batteryPercentage;
    }

    void AbstractSensor::setIdentifier(const unsigned int& newIdentifier) {
        identifier = newIdentifier;
        for(auto &observers : observersList)
            observers->notify(*this);

    }

    void AbstractSensor::setName(const std::string &newName) {
        name = newName;
        for(auto &observers : observersList)
            observers->notify(*this);
    }

    void AbstractSensor::setDescription(const std::string &newDescription) {
        description = newDescription;
        for(auto &observers : observersList)
            observers->notify(*this);
    }

    void AbstractSensor::setPlugged(const bool& newPlugged) {
        plugged = newPlugged;
        if(plugged)
            batteryPercentage = 100;
        for(auto &observers : observersList)
            observers->notify(*this);
    }

    void AbstractSensor::setBatteryPercentage(const unsigned int& newBatteryPercentage) {
        batteryPercentage = newBatteryPercentage;
        for(auto &observers : observersList)
            observers->notify(*this);
    }

    void AbstractSensor::addObserver(SensorObserver* sensorObserver) {
        observersList.push_back(sensorObserver);
    }

    void AbstractSensor::removeObserver(SensorObserver* sensorObserver) {
        observersList.erase(std::remove(observersList.begin(), observersList.end(), sensorObserver), observersList.end());
    }

    AbstractSensor::~AbstractSensor() {
        for(auto &observer : observersList)
            observer->destructor();
    }
}
