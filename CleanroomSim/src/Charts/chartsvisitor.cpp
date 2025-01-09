#include "chartsvisitor.h"
#include <QSplineSeries>
#include "Sensors/hygrometer.h"
#include <QScatterSeries>
#include "Sensors/manometer.h"
#include <QLineSeries>
#include <QBarSeries>
#include "Sensors/particles.h"
#include "Sensors/particlecounter.h"
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

namespace Charts {

    ChartsVisitor::ChartsVisitor()
    : sensorChart(nullptr) {

    }

    QChart* ChartsVisitor::getSensorChart() {
        return sensorChart;
    }

    void ChartsVisitor::visit(const Sensors::Hygrometer& sensorH) {
        sensorChart = new QChart();

        QSplineSeries* splineSeries = new QSplineSeries(sensorChart);

        // Ottiene i valori dal sensore
        int i = 0;
        const std::vector<double> *vals = sensorH.getData();
        for(const double& val : *(vals)) {
            splineSeries->append(i, val);   // Aggiunge i punti alla serie
            ++i;
        }

        splineSeries->setColor(Qt::darkBlue);   // Imposta il colore

        // Configura il grafico
        sensorChart->legend()->hide();
        sensorChart->addSeries(splineSeries);   // Aggiunge la serie al grafico
        sensorChart->setTitle("Valori umidità relativa");   // Imposta il titolo del grafico
        sensorChart->createDefaultAxes();   // Crea gli assi di default
        sensorChart->axes(Qt::Horizontal).first()->setTitleText("Tempo (h)");
        sensorChart->axes(Qt::Vertical).first()->setTitleText("Umidità (%)");
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size() - 1));
        sensorChart->axes(Qt::Vertical).first()->setRange(0, 100);
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);
    }

    void ChartsVisitor::visit(const Sensors::Manometer& sensorM) {
        sensorChart = new QChart();

        QScatterSeries* scatterSeries = new QScatterSeries(sensorChart);
        scatterSeries->setMarkerSize(10.0); // Dimensione dei punti

        // Ottiene i valori dal sensore
        int i = 0;
        const std::vector<int>* vals = sensorM.getData();
        for (const int& val : *(vals)) {
            scatterSeries->append(i, val);  // Aggiunge i punti alla serie
            ++i;
        }

        scatterSeries->setColor(Qt::green); // Imposta il colore dei punti

        // Crea una serie per la linea orizzontale di soglia
        QLineSeries* thresholdLine = new QLineSeries(sensorChart);

        // Ottiene il valore di soglia dal sensore
        double thresholdValue = sensorM.getThreshold();

        // Aggiunge i punti per la linea orizzontale
        thresholdLine->append(0, thresholdValue);
        thresholdLine->append(vals->size() - 1, thresholdValue);
        thresholdLine->setColor(Qt::red); // Imposta il colore della linea

        // Configura il grafico
        sensorChart->legend()->hide(); // Nasconde la legenda
        sensorChart->addSeries(scatterSeries); // Aggiunge la serie di punti al grafico
        sensorChart->addSeries(thresholdLine);
        sensorChart->setTitle("Valori di pressione"); // Imposta il titolo del grafico
        sensorChart->createDefaultAxes(); // Crea gli assi di default
        sensorChart->axes(Qt::Horizontal).first()->setTitleText("Tempo (h)"); // Imposta il titolo dell'asse X
        sensorChart->axes(Qt::Vertical).first()->setTitleText("Pressione (Pa)"); // Imposta il titolo dell'asse Y
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size() - 1)); // Imposta l'intervallo dell'asse X
        sensorChart->axes(Qt::Vertical).first()->setRange(thresholdValue-100, thresholdValue+100); // Imposta l'intervallo dell'asse Y
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);
    }

    void ChartsVisitor::visit(const Sensors::ParticleCounter& sensorPC) {
        sensorChart = new QChart();

        QBarSeries* barSeries = new QBarSeries(sensorChart);
        const std::vector<Sensors::Particles> *vals = sensorPC.getData();
        QBarSet* dotOne = new QBarSet("0.1", barSeries);
        QBarSet* dotTwo = new QBarSet("0.2", barSeries);
        QBarSet* dotThree = new QBarSet("0.3", barSeries);
        QBarSet* dotFive = new QBarSet("0.5", barSeries);
        QBarSet* one = new QBarSet("1", barSeries);
        QBarSet* five = new QBarSet("5", barSeries);

        // Ottiene i dati dal sensore
        for(const Sensors::Particles& val : *(vals)) {
            dotOne->append(val.getDotOneumCount());
            dotTwo->append(val.getDotTwoumCount());
            dotThree->append(val.getDotThreeumCount());
            dotFive->append(val.getDotFiveumCount());
            one->append(val.getOneumCount());
            five->append(val.getFiveumCount());
        }

        barSeries->append(dotOne);
        barSeries->append(dotTwo);
        barSeries->append(dotThree);
        barSeries->append(dotFive);
        barSeries->append(one);
        barSeries->append(five);

        // Configura grafico
        sensorChart->addSeries(barSeries);
        sensorChart->setTitle("Conteggio particelle in base al diametro (µm)");

        QBarCategoryAxis* axisX = new QBarCategoryAxis(sensorChart);
        axisX->setTitleText("Tempo (h)");
        sensorChart->addAxis(axisX, Qt::AlignBottom);
        barSeries->attachAxis(axisX);

        QValueAxis* axisY = new QValueAxis(sensorChart);
        axisY->setTitleText("Conteggio");
        sensorChart->addAxis(axisY, Qt::AlignLeft);
        barSeries->attachAxis(axisY);

        sensorChart->legend()->setVisible(true);
        sensorChart->legend()->setAlignment(Qt::AlignBottom);
        sensorChart->axes(Qt::Horizontal).first()->setRange(0, QVariant::fromValue(vals->size()));

        // Fissa valore massimo scala grafico in base al valore massimo dei dati
        const Sensors::Particles* valMax = sensorPC.getMax();
        int maxValues[6];
        maxValues[0] = valMax->getDotOneumCount();
        maxValues[1] = valMax->getDotTwoumCount();
        maxValues[2] = valMax->getDotThreeumCount();
        maxValues[3] = valMax->getDotFiveumCount();
        maxValues[4] = valMax->getOneumCount();
        maxValues[5] = valMax->getFiveumCount();

        int maxValue = 0;
        for(int i=0; i<6; ++i) {
            if(maxValues[i] > maxValue)
                maxValue = maxValues[i];
        }

        sensorChart->axes(Qt::Vertical).first()->setRange(0, maxValue);
        sensorChart->setAnimationOptions(QChart::SeriesAnimations);
    }
}
