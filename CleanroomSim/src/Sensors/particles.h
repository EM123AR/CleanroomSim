#ifndef PARTICLES_H
#define PARTICLES_H

namespace Sensors {

    class Particles
    {
    private:
        // Attributi
        int values[6];  /// ciascuna colonna indica il conteggio di particelle di un diametro diverso in um (0.1, 0.2, 0.3, 0.5, 1, 5)

    public:
        // Costruttori
        Particles(const int& dotOneumCount =0, const int& dotTwoumCount =0, const int& dotThreeumCount =0, const int& dotFiveumCount =0, const int& oneumCount =0, const int& fiveumCount =0);
        Particles(const Particles& other);

        // Getters e setters
        int getDotOneumCount() const;
        int getDotTwoumCount() const;
        int getDotThreeumCount() const;
        int getDotFiveumCount() const;
        int getOneumCount() const;
        int getFiveumCount() const;
        void setDotOneumCount(const int& newDotOneumCount);
        void setDotTwoumCount(const int& newDotTwoumCount);
        void setDotThreeumCount(const int& newDotThreeumCount);
        void setDotFiveumCount(const int& newDotFiveumCount);
        void setOneumCount(const int& newOneumCount);
        void setFiveumCount(const int& newFiveumCount);

        // Ridefinizione operatori
        Particles operator+(const Particles& p);
        Particles operator/(const int& val);
        Particles& operator=(const Particles& p);
        Particles& operator=(const int& val);

        // Gestione simulazione
        /**
         * @brief generateSimulation: genera dati in base allo standard
         * @param standard: standard ISO desiderato
         */
        void generateSimulation(const unsigned int& standard);
        /**
         * @brief generateMaximum: per ciascun diametro, si inserisce nei dati il contatore massimo tra quello di p1 e p2
         * @param p1
         * @param p2
         */
        void generateMaximum(const Particles& p1, const Particles& p2);
        /**
         * @brief generateMinimum: per ciascun diametro, si inserisce nei dati il contatore minimo tra quello di p1 e p2
         * @param p1
         * @param p2
         */
        void generateMinimum(const Particles& p1, const Particles& p2);

        // Distruttori
        ~Particles() = default;
    };

}

#endif // PARTICLES_H
