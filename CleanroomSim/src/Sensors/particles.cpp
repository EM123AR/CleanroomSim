#include "particles.h"
#include <random>

namespace Sensors {

    Particles::Particles(const Particles& other)
        : values{other.getDotOneumCount(), other.getDotTwoumCount(), other.getDotThreeumCount(), other.getDotFiveumCount(),
        other.getOneumCount(), other.getFiveumCount()} {

    }

    Particles::Particles(const int& dotOneumCount, const int& dotTwoumCount, const int& dotThreeumCount, const int& dotFiveumCount, const int& oneumCount, const int& fiveumCount)
        : values{dotOneumCount, dotTwoumCount, dotThreeumCount, dotFiveumCount, oneumCount, fiveumCount} {

    }

    int Particles::getDotOneumCount() const {
        return values[0];
    }

    int Particles::getDotTwoumCount() const {
        return values[1];
    }

    int Particles::getDotThreeumCount() const {
        return values[2];
    }

    int Particles::getDotFiveumCount() const {
        return values[3];
    }

    int Particles::getOneumCount() const {
        return values[4];
    }

    int Particles::getFiveumCount() const {
        return values[5];
    }

    void Particles::setDotOneumCount(const int& newDotOneumCount) {
        values[0] = newDotOneumCount;
    }

    void Particles::setDotTwoumCount(const int& newDotTwoumCount) {
        values[1] = newDotTwoumCount;
    }

    void Particles::setDotThreeumCount(const int& newDotThreeumCount)  {
        values[2] = newDotThreeumCount;
    }

    void Particles::setDotFiveumCount(const int& newDotFiveumCount) {
        values[3] = newDotFiveumCount;
    }

    void Particles::setOneumCount(const int& newOneumCount) {
        values[4] = newOneumCount;
    }

    void Particles::setFiveumCount(const int& newFiveumCount) {
        values[4] = newFiveumCount;
    }

    Particles Particles::operator+(const Particles& p) {
        return Particles(values[0] + p.getDotOneumCount(), values[1] + p.getDotTwoumCount(), values[2] + p.getDotThreeumCount(),
                         values[3] + p.getDotFiveumCount(), values[4] + p.getOneumCount(), values[5] + p.getFiveumCount());
    }

    Particles Particles::operator/(const int& val) {
        return Particles(values[0] / val, values[1] / val, values[2] / val, values[3] / val, values[4] / val, values[5] / val);
    }

    Particles& Particles::operator=(const Particles& p) {
        values[0] = p.getDotOneumCount();
        values[1] = p.getDotTwoumCount();
        values[2] = p.getDotThreeumCount();
        values[3] = p.getDotFiveumCount();
        values[4] = p.getOneumCount();
        values[5] = p.getFiveumCount();

        return *this;
    }

    Particles& Particles::operator=(const int& val) {
        values[0] = val;
        values[1] = val;
        values[2] = val;
        values[3] = val;
        values[4] = val;
        values[5] = val;

        return *this;
    }

    void Particles::generateSimulation(const unsigned int& standard) {
        // Generatore di numeri casuali
        std::random_device rd;
        std::mt19937 gen(rd());

        unsigned int dotOneMax = 0;
        unsigned int dotTwoMax = 0;
        unsigned int dotThreeMax = 0;
        unsigned int dotFiveMax = 0;
        unsigned int oneMax = 0;
        unsigned int fiveMax = 0;

        switch (standard) {
        case 1:
            dotOneMax = 11;
            dotTwoMax = 3;
            dotThreeMax = 1;
            break;
        case 2:
            dotOneMax = 105;
            dotTwoMax = 25;
            dotThreeMax = 11;
            dotFiveMax = 4;
            oneMax = 1;
            break;
        case 3:
            dotOneMax = 1050;
            dotTwoMax = 240;
            dotThreeMax = 110;
            dotFiveMax = 36;
            oneMax = 8;
            break;
        case 4:
            dotOneMax = 10100;
            dotTwoMax = 2400;
            dotThreeMax = 1030;
            dotFiveMax = 355;
            oneMax = 85;
            fiveMax = 1;
            break;
        case 5:
            dotOneMax = 100100;
            dotTwoMax = 23750;
            dotThreeMax = 10250;
            dotFiveMax = 3525;
            oneMax = 835;
            fiveMax = 30;
            break;
        case 6:
            dotOneMax = 1000100;
            dotTwoMax = 237100;
            dotThreeMax = 102050;
            dotFiveMax = 35250;
            oneMax = 8330;
            fiveMax = 300;
            break;
        case 7:
            dotOneMax = 1008000;
            dotTwoMax = 239800;
            dotThreeMax = 103800;
            dotFiveMax = 352100;
            oneMax = 83250;
            fiveMax = 2950;
            break;
        case 8:
            dotOneMax = 1091000;
            dotTwoMax = 249000;
            dotThreeMax = 108000;
            dotFiveMax = 3520100;
            oneMax = 832100;
            fiveMax = 29350;
            break;
        case 9:
            dotOneMax = 2901000;
            dotTwoMax = 399000;
            dotThreeMax = 293000;
            dotFiveMax = 35200200;
            oneMax = 8320200;
            fiveMax = 293200;
            break;
        default:
            // ERRORE
            break;
        }


        // Genera valori particelle
        std::uniform_real_distribution<> disDotOne(0, dotOneMax);
        values[0] = disDotOne(gen);
        std::uniform_real_distribution<> disDotTwo(0, dotTwoMax);
        values[1] = disDotTwo(gen);
        std::uniform_real_distribution<> disDotThree(0, dotThreeMax);
        values[2] = disDotThree(gen);
        std::uniform_real_distribution<> disDotFive(0, dotFiveMax);
        values[3] = disDotFive(gen);
        std::uniform_real_distribution<> disOne(0, oneMax);
        values[4] = disOne(gen);
        std::uniform_real_distribution<> disFive(0, fiveMax);
        values[5] = disFive(gen);
    }

    void Particles::generateMaximum(const Particles& p1, const Particles& p2) {
        for(int i = 0; i < 6; i++)
            values[i] = std::max(p1.values[i], p2.values[i]);
    }

    void Particles::generateMinimum(const Particles& p1, const Particles& p2) {
        for(int i = 0; i < 6; i++)
            values[i] = std::min(p1.values[i], p2.values[i]);
    }
}
