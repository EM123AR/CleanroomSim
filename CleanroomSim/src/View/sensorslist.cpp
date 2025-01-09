#include "sensorslist.h"
#include <QVBoxLayout>
#include "sensorwidget.h"
#include "Dialogs/addsensorwindow.h"

namespace View {

    SensorsList::SensorsList(Sensors::Storage::Archive* cache, QWidget* parent)
        : QWidget{parent}, cache(cache) {
        QVBoxLayout* mainLayout = new QVBoxLayout();

        searchBox = new QLineEdit("");
        searchBox->setPlaceholderText("Filtra per nome...");
        searchButton = new QPushButton("Ricerca");
        QHBoxLayout* searchLayout = new QHBoxLayout();
        searchLayout->addWidget(searchBox);
        searchLayout->addWidget(searchButton);
        sensorsCount = new QLabel("<b>Sensori trovati:</b> 0");

        // Connessioni
        /// Bottone ricerca (anche se superfluo)
        connect(searchButton, &QPushButton::clicked, this, &SensorsList::filter);
        /// Inserimento testo nella casella ricerca
        connect(searchBox, &QLineEdit::textChanged, this, &SensorsList::filter);

        panel = new QScrollArea(this);

        addButton = new QPushButton("Aggiungi sensore");
        connect(addButton, &QPushButton::clicked, this, &SensorsList::addSensor);

        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(sensorsCount);
        mainLayout->addWidget(panel);
        mainLayout->addWidget(addButton);

        this->setLayout(mainLayout);

        this->setMaximumWidth(400);
        this->setMinimumWidth(300);

        cache->addObserver(this);
    }

    QString SensorsList::getFilterText() const {
        return searchBox->text();
    }

    void SensorsList::setFilterText(QString filterText) {
        searchBox->setText(filterText);
    }

    void SensorsList::update(const std::vector<Sensors::AbstractSensor*>* sensors) {
        if(panel->widget())
            panel->takeWidget()->deleteLater();

        QWidget* panelWidget = new QWidget(panel);
        QVBoxLayout* panelWidgetLayout = new QVBoxLayout();

        for(Sensors::AbstractSensor* value : *sensors) {

            SensorWidget* panelSensorWidget = new SensorWidget(value, panelWidget);
            panelSensorWidget->setFrameStyle(QFrame::Box | QFrame::Plain);
            panelSensorWidget->setLineWidth(1);
            panelSensorWidget->setMidLineWidth(0);
            panelSensorWidget->setFrameShadow(QFrame::Sunken);
            panelSensorWidget->setStyleSheet("border-color: black");

            connect(panelSensorWidget, &SensorWidget::mousePressed, this, &SensorsList::openWidget);
            panelWidgetLayout->addWidget(panelSensorWidget);
        }

        sensorsCount->setText("<b>Sensori trovati:</b> " + QString::number(sensors->size()));
        panelWidget->setLayout(panelWidgetLayout);
        panel->setWidget(panelWidget);
        delete sensors;
    }

    void SensorsList::notify(Sensors::Storage::Archive& cache) {
        update(cache.filterName(searchBox->text().toStdString()));
    }

    void SensorsList::destructor() {
        cache = nullptr;
    }

    void SensorsList::openWidget(Sensors::AbstractSensor* sensor) {
        emit widgetPressed(sensor);
    }

    void SensorsList::filter() {
        update(cache->filterName(searchBox->text().toStdString()));
    }

    void SensorsList::addSensor() {
        Dialogs::AddSensorWindow* addWindow = new Dialogs::AddSensorWindow(this);
        addWindow->setWindowTitle("Aggiungi sensore");

        addWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(addWindow, &Dialogs::AddSensorWindow::addButtonPressed, this, &SensorsList::addButtonPressed);
        addWindow->exec();
    }

    SensorsList::~SensorsList() {
        if(cache)
            cache->removeObserver(this);
    }

}
