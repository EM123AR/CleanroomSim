#include "hygrometer.h"
#include <random>
#include <algorithm>
#define DEFAULT_OPTIMAL_AVG 45
#define BATTERY_CONSUMPTION 15

namespace Sensors {

    Hygrometer::Hygrometer(const unsigned int& identifier, const std::string& name, const std::string description, const bool& plugged, const unsigned int& batteryPercentage)
    : AbstractSensor(identifier, name, description, plugged, batteryPercentage), optimalAvg(DEFAULT_OPTIMAL_AVG) {
        Hygrometer::simulate();
    }

    Hygrometer::Hygrometer(const Hygrometer& other)
        : AbstractSensor(other.getIdentifier(), other.getName(), other.getDescription(), other.isPlugged(), other.getBatteryPercentage()), data(*(other.getData())), avg(other.getAvg()), optimalAvg(other.getOptimalAvg()) {

    }

    const std::vector<double>* Hygrometer::getData() const {
        return &data;
    }

    double Hygrometer::getAvg() const {
        return avg;
    }

    double Hygrometer::getOptimalAvg() const {
        return optimalAvg;
    }

    void Hygrometer::setData(const std::vector<double>& newData) {
        data = newData;
    }

    void Hygrometer::setAvg(const double& newAvg) {
        avg = newAvg;
    }

    void Hygrometer::setOptimalAvg(const double& newOptimalAvg) {
        optimalAvg = newOptimalAvg;
    }

    void Hygrometer::accept(SensorVisitor& sensorVisitor) const {
        sensorVisitor.visit(*this);
    }

    void Hygrometer::updateAvg() {
        if(!data.empty()) {
            double sum = 0;
            for(double value : data)
                sum += value;

            avg = sum / data.size();
        }
        else avg = 0;
    }

    void Hygrometer::generateSimulation() {
        data = std::vector<double>(20);

        // Generatore di numeri casuali
        std::random_device rd;
        std::mt19937 gen(rd());

        // Distribuzione uniforme tra 30 e 60
        std::uniform_real_distribution<> dis(30.0, 60.0);

        // Genera 20 valori di umidità
        std::generate(data.begin(), data.end(), [&]() { return dis(gen); });

        // Aggiorna la media dei valori generati
        updateAvg();
    }

    void Hygrometer::simulate() {
        unsigned int batteryP = getBatteryPercentage();

        if(!isPlugged()) {
            if(batteryP > BATTERY_CONSUMPTION) {
                setBatteryPercentage(batteryP - BATTERY_CONSUMPTION);

                Hygrometer::generateSimulation();
            } else {
                setBatteryPercentage(0);
            }
        } else {
            Hygrometer::generateSimulation();
        }
        for(auto &observer : observersList)
            observer->notify(*this);
    }
}
