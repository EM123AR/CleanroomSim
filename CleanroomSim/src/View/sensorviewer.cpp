#include "sensorviewer.h"
#include <QSvgWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "Sensors/hygrometer.h"
#include "Sensors/manometer.h"
#include "Sensors/particlecounter.h"

namespace View {

    std::vector<QString> SensorViewer::types = {"Igrometro", "Manometro", "Contatore di particelle"};

    SensorViewer::SensorViewer()
        : iconWidget(nullptr), warningIconWidget(nullptr), batteryIconWidget(nullptr), infoWidget(nullptr)    {

    }

    QString SensorViewer::getType() const {
        return type;
    }

    QWidget* SensorViewer::getIconWidget() const {
        return iconWidget;
    }

    QWidget* SensorViewer::getWarningIconWidget() const {
        return warningIconWidget;
    }

    QWidget* SensorViewer::getBatteryIconWidget() const {
        return batteryIconWidget;
    }

    QWidget* SensorViewer::getInfoWidget() const {
        return infoWidget;
    }

    void SensorViewer::visit(const Sensors::Hygrometer& sensorH) {
        type = "Igrometro";
        iconWidget = new QSvgWidget(":Icons/Sensors/hygrometer.svg");

        infoWidget = new QWidget();
        QHBoxLayout* infoWidgetLayout = new QHBoxLayout(infoWidget);

        // Gestione warning dati simulazione
        if(sensorH.getAvg() > sensorH.getOptimalAvg())
            warningIconWidget = new QSvgWidget(":Icons/warning.svg");
        else
            warningIconWidget = nullptr;

        // Gestione stato batteria
        if(!sensorH.isPlugged()) {
            unsigned int batteryPercentage = sensorH.getBatteryPercentage();    /// mostra percentuale solo se alimentato a batteria
            QLabel* infoBattery = new QLabel("Batteria: " + QString::number(batteryPercentage) + " %");
            infoWidgetLayout->addWidget(infoBattery);

            /// cambia icona in base al livello/alimentazione
            if(batteryPercentage > 75)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_100.svg");
            else if(batteryPercentage > 50)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_75.svg");
            else if(batteryPercentage > 25)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_50.svg");
            else if(batteryPercentage > 0)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_25.svg");
            else
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_0.svg");
        } else {
            batteryIconWidget = new QSvgWidget(":Icons/Battery/plugged.svg");
        }

        QLabel* infoOptimalAvg = new QLabel("Media desiderata: " + QString::number(sensorH.getOptimalAvg()) + " %");
        infoWidgetLayout->addWidget(infoOptimalAvg);
        QLabel* infoAvg = new QLabel("Media: " + QString::number(sensorH.getAvg()) + " %");
        if(warningIconWidget)
            infoAvg->setStyleSheet("font-weight: bold;");
        infoWidgetLayout->addWidget(infoAvg);


        infoWidget->setLayout(infoWidgetLayout);
        infoWidget->setStyleSheet("font-size: 15px");
    }

    void SensorViewer::visit(const Sensors::Manometer& sensorM) {
        type = "Manometro";
        iconWidget = new QSvgWidget(":Icons/Sensors/manometer.svg");

        infoWidget = new QWidget();
        QHBoxLayout* infoWidgetLayout = new QHBoxLayout(infoWidget);

        // Gestione warning dati simulazione
        if(sensorM.getMan() > 2.5)
            warningIconWidget = new QSvgWidget(":Icons/warning.svg");
        else
            warningIconWidget = nullptr;

        // Gestione stato batteria
        if(!sensorM.isPlugged()) {
            unsigned int batteryPercentage = sensorM.getBatteryPercentage();    /// mostra percentuale solo se alimentato a batteria
            QLabel* infoBattery = new QLabel("Batteria: " + QString::number(batteryPercentage) + " %");
            infoWidgetLayout->addWidget(infoBattery);

            /// cambia icona in base al livello/alimentazione
            if(batteryPercentage > 75)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_100.svg");
            else if(batteryPercentage > 50)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_75.svg");
            else if(batteryPercentage > 25)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_50.svg");
            else if(batteryPercentage > 0)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_25.svg");
            else
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_0.svg");
        } else {
            batteryIconWidget = new QSvgWidget(":Icons/Battery/plugged.svg");
        }

        QLabel* infoThreshold = new QLabel("Soglia: " + QString::number(sensorM.getThreshold()) + " Pa");
        infoWidgetLayout->addWidget(infoThreshold);
        QLabel* infoMan = new QLabel("Deviazione media: " + QString::number(sensorM.getMan()));
        if(warningIconWidget)
            infoMan->setStyleSheet("font-weight: bold;");
        infoWidgetLayout->addWidget(infoMan);
        infoWidget->setLayout(infoWidgetLayout);
        infoWidget->setStyleSheet("font-size: 15px");
    }
    void SensorViewer::visit(const Sensors::ParticleCounter& sensorPC) {
        type = "Contatore di particelle";
        iconWidget = new QSvgWidget(":Icons/Sensors/particle_counter.svg");

        infoWidget = new QWidget();
        QHBoxLayout* infoWidgetLayout = new QHBoxLayout(infoWidget);

        // Gestione warning dati simulazione
        switch(sensorPC.getDesiredStandard()) {
        case 1:
            if(sensorPC.getMax()->getDotOneumCount() > 10) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 2) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            /*if(sensorPC.getMax()->getDotThreeumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }*/
            warningIconWidget = nullptr;
            break;
        case 2:
            if(sensorPC.getMax()->getDotOneumCount() > 100) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 24) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotThreeumCount() > 10) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 4) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            /*if(sensorPC.getMax()->getOneumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }*/
            warningIconWidget = nullptr;
            break;
        case 3:
            if(sensorPC.getMax()->getDotOneumCount() > 1000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 237) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotThreeumCount() > 102) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 35) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 8) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            /*if(sensorPC.getMax()->getFiveumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }*/
            warningIconWidget = nullptr;
            break;
        case 4:
            if(sensorPC.getMax()->getDotOneumCount() > 10000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 2370) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotThreeumCount() > 1020) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 352) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 83) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 0) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        case 5:
            if(sensorPC.getMax()->getDotOneumCount() > 100000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 23700) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotThreeumCount() > 10200) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 3520) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 832) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 29) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        case 6:
            if(sensorPC.getMax()->getDotOneumCount() > 1000000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;  /// appena un valore sfora lo standard si esce dallo switch
            }
            if(sensorPC.getMax()->getDotTwoumCount() > 237000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotThreeumCount() > 102000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getDotFiveumCount() > 35200) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 8320) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 293) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        case 7:
            if(sensorPC.getMax()->getDotFiveumCount() > 352000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 83200) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 2930) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        case 8:
            if(sensorPC.getMax()->getDotFiveumCount() > 3520000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 832000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 29300) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        case 9:
            if(sensorPC.getMax()->getDotFiveumCount() > 35200000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getOneumCount() > 8320000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            if(sensorPC.getMax()->getFiveumCount() > 293000) {
                warningIconWidget = new QSvgWidget(":Icons/warning.svg");
                break;
            }
            warningIconWidget = nullptr;
            break;
        default:
            // ERRORE
            break;
        }



        // Gestione stato batteria
        if(!sensorPC.isPlugged()) {
            unsigned int batteryPercentage = sensorPC.getBatteryPercentage();    /// mostra percentuale solo se alimentato a batteria
            QLabel* infoBattery = new QLabel("Batteria: " + QString::number(batteryPercentage) + " %");
            infoWidgetLayout->addWidget(infoBattery);

            /// cambia icona in base al livello/alimentazione
            if(batteryPercentage > 75)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_100.svg");
            else if(batteryPercentage > 50)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_75.svg");
            else if(batteryPercentage > 25)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_50.svg");
            else if(batteryPercentage > 0)
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_25.svg");
            else
                batteryIconWidget = new QSvgWidget(":Icons/Battery/battery_0.svg");
        } else {
            batteryIconWidget = new QSvgWidget(":Icons/Battery/plugged.svg");
        }

        QLabel* infoStandard = new QLabel("Standard: ISO " + QString::number(sensorPC.getDesiredStandard()));
        infoWidgetLayout->addWidget(infoStandard);
        QString dotOne = "<b>0.1 µm</b> = " + QString::number(sensorPC.getMax()->getDotOneumCount());
        QString dotTwo = "<b>0.2 µm</b> = " + QString::number(sensorPC.getMax()->getDotTwoumCount());
        QString dotThree = "<b>0.3 µm</b> = " + QString::number(sensorPC.getMax()->getDotThreeumCount());
        QString dotFive = "<b>0.5 µm</b> = " + QString::number(sensorPC.getMax()->getDotFiveumCount());
        QString one = "<b>1 µm</b> = " + QString::number(sensorPC.getMax()->getOneumCount());
        QString five = "<b>5 µm</b> = " + QString::number(sensorPC.getMax()->getDotFiveumCount());

        QLabel* infoMax = new QLabel("Valori massimi:<br>" + dotOne + "<br>" + dotTwo + "<br>" + dotThree
                                    + "<br>" + dotFive + "<br>" + one + "<br>" + five);

        if(warningIconWidget)
            infoMax->setStyleSheet("font-weight: bold;");
        infoWidgetLayout->addWidget(infoMax);

        dotOne = "<b>0.1 µm</b> = " + QString::number(sensorPC.getMin()->getDotOneumCount());
        dotTwo = "<b>0.2 µm</b> = " + QString::number(sensorPC.getMin()->getDotTwoumCount());
        dotThree = "<b>0.3 µm</b> = " + QString::number(sensorPC.getMin()->getDotThreeumCount());
        dotFive = "<b>0.5 µm</b> = " + QString::number(sensorPC.getMin()->getDotFiveumCount());
        one = "<b>1 µm</b> = " + QString::number(sensorPC.getMin()->getOneumCount());
        five = "<b>5 µm</b> = " + QString::number(sensorPC.getMin()->getDotFiveumCount());

        QLabel* infoMin = new QLabel("Valori minimi:<br>" + dotOne + "<br>" + dotTwo + "<br>" + dotThree
                                    + "<br>" + dotFive + "<br>" + one + "<br>" + five);

        infoWidgetLayout->addWidget(infoMin);

        dotOne = "<b>0.1 µm</b> = " + QString::number(sensorPC.getAvg()->getDotOneumCount());
        dotTwo = "<b>0.2 µm</b> = " + QString::number(sensorPC.getAvg()->getDotTwoumCount());
        dotThree = "<b>0.3 µm</b> = " + QString::number(sensorPC.getAvg()->getDotThreeumCount());
        dotFive = "<b>0.5 µm</b> = " + QString::number(sensorPC.getAvg()->getDotFiveumCount());
        one = "<b>1 µm</b> = " + QString::number(sensorPC.getAvg()->getOneumCount());
        five = "<b>5 µm</b> = " + QString::number(sensorPC.getAvg()->getDotFiveumCount());

        QLabel* infoAvg = new QLabel("Valori media:<br>" + dotOne + "<br>" + dotTwo + "<br>" + dotThree
                                     + "<br>" + dotFive + "<br>" + one + "<br>" + five);

        infoWidgetLayout->addWidget(infoAvg);

        infoWidget->setLayout(infoWidgetLayout);
        infoWidget->setStyleSheet("font-size: 15px");
    }
}
