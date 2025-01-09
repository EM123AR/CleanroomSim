#include "manometer.h"
#include <random>
#include <algorithm>
#define DEFAULT_THRESHOLD 101345
#define BATTERY_CONSUMPTION 15

namespace Sensors {

    Manometer::Manometer(const unsigned int& identifier, const std::string& name, const std::string description, const bool& plugged, const unsigned int& batteryPercentage)
    : AbstractSensor(identifier, name, description, plugged, batteryPercentage), threshold(DEFAULT_THRESHOLD) {
        Manometer::simulate();
    }

    Manometer::Manometer(const Manometer& other)
        : AbstractSensor(other.getIdentifier(), other.getName(), other.getDescription(), other.isPlugged(), other.getBatteryPercentage()), data(*(other.getData())), threshold(other.getThreshold()), man(other.getMan()) {

    }

    const std::vector<int>* Manometer::getData() const {
        return &data;
    }

    int Manometer::getThreshold() const {
        return threshold;
    }

    double Manometer::getMan() const {
        return man;
    }

    void Manometer::setData(const std::vector<int> &newData) {
        data = newData;
    }

    void Manometer::setThreshold(const int& newTreshold) {
        threshold = newTreshold;
    }

    void Manometer::setMan(const double& newMan) {
        man = newMan;
    }

    void Manometer::accept(SensorVisitor& sensorVisitor) const {
        sensorVisitor.visit(*this);
    }

    void Manometer::updateMan() {
        if(!data.empty()) {
            double sum = 0;
            for(double value : data)
                sum += std::abs(value - threshold);

            man = sum / data.size();
        }
        else man = 0;
    }

    void Manometer::generateSimulation() {
        data = std::vector<int>(20);

        // Generatore di numeri casuali
        std::random_device rd;
        std::mt19937 gen(rd());

        // Distribuzione uniforme tra +/-5 rispetto alla soglia
        std::uniform_real_distribution<> dis(threshold-5, threshold+5);

        // Genera 20 valori di pressione
        std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

        // Aggiorna la deviazione media assoluta
        updateMan();
    }

    void Manometer::simulate() {
        unsigned int batteryP = getBatteryPercentage();

        if(!isPlugged()) {
            if(batteryP > BATTERY_CONSUMPTION) {
                setBatteryPercentage(batteryP - BATTERY_CONSUMPTION);

                Manometer::generateSimulation();
            } else {
                setBatteryPercentage(0);
            }
        } else {
            Manometer::generateSimulation();
        }
        for(auto &observer : observersList)
            observer->notify(*this);
    }
}
