#ifndef SENSORVIEWER_H
#define SENSORVIEWER_H

#include "Sensors/sensorvisitor.h"
#include <QString>
#include <QWidget>

namespace View {

    class SensorViewer : public Sensors::SensorVisitor
    {
    private:
        // Attributi
        QString type;   /// tipo sensore
        QWidget* iconWidget;    /// icona sensore
        QWidget* warningIconWidget; /// icona valori anomali
        QWidget* batteryIconWidget; /// icona stato batteria
        QWidget* infoWidget;    /// informazioni sensore

    public:
        static std::vector<QString> types;  /// elenco tipi sensore

        // Costruttori
        SensorViewer();

        // Getters
        QString getType() const;
        QWidget* getIconWidget() const;
        QWidget* getWarningIconWidget() const;
        QWidget* getBatteryIconWidget() const;
        QWidget* getInfoWidget() const;

        // Gestione visitors
        void visit(const Sensors::Hygrometer& sensorH) override;
        void visit(const Sensors::Manometer& sensorM) override;
        void visit(const Sensors::ParticleCounter& sensorPC) override;

        // Distruttori
        ~SensorViewer() = default;
    };

}

#endif // SENSORVIEWER_H
