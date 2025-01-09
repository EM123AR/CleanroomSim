#include "mainwindow.h"
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>

namespace View {

    MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, mainSplitter(nullptr), toolbar(nullptr), sensorsList(nullptr), cache(nullptr) {
        // Memoria corrente
        cache = new Sensors::Storage::Archive();

        // Toolbar
        toolbar = new Toolbar(this);
        toolbar->setMovable(false);
        this->addToolBar(toolbar);

        // Splitter principale
        mainSplitter = new QSplitter(this);

        // Parte sinistra
        sensorsList = new SensorsList(cache, mainSplitter);

        // Parte destra
        sensorView = new SensorView(nullptr, this);

        // Unione
        mainSplitter->addWidget(sensorsList);
        mainSplitter->addWidget(sensorView);

        // Imposta figlio non può sparire
        mainSplitter->setChildrenCollapsible(false);

        setCentralWidget(mainSplitter);

        // Connessioni
        /// Aggiungi sensore
        connect(sensorsList, &SensorsList::addButtonPressed, this, &MainWindow::addSensor);
        /// Elimina sensore
        connect(sensorView, &SensorView::deleteButtonPressed, this, &MainWindow::deleteSensor);
        /// Modifiche non salvate
        connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::unsavedChanges);
        /// Mostra sensore
        connect(sensorsList, &SensorsList::widgetPressed, this, &MainWindow::showSensor);
        /// Carica Json
        connect(toolbar, &Toolbar::openButtonPressed, this, &MainWindow::open);
        /// Salva Json aperto/default
        connect(toolbar, &Toolbar::saveButtonPressed, this, &MainWindow::save);
        /// Salva Json specificato
        connect(toolbar, &Toolbar::saveAsButtonPressed, this, &MainWindow::saveAs);

        // Icona e titolo finestra
        this->setWindowIcon(QIcon(":Icons/logo.svg"));
        this->setWindowTitle("Cleanroom Sim");
    }

    MainWindow::~MainWindow() {
        delete cache;
    }

    void MainWindow::addSensor(Sensors::AbstractSensor* sensor) {
        cache->addSensor(sensor);
        this->setWindowTitle("Cleanroom Sim*");
    }

    void MainWindow::deleteSensor(Sensors::AbstractSensor* sensor) {
        Sensors::AbstractSensor *s = cache->takeSensorByIdentifier(sensor->getIdentifier());

        delete s;
        sensorView->deleteLater();
        sensorView = new SensorView(nullptr, this);
        connect(sensorView, &SensorView::deleteButtonPressed, this, &MainWindow::deleteSensor);
        connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::unsavedChanges);
        mainSplitter->addWidget(sensorView);

        this->setWindowTitle("Cleanroom Sim*");
    }

    void MainWindow::showSensor(Sensors::AbstractSensor* sensor) {
        if(sensorView->getSensor() != sensor) {
            sensorView->deleteLater();
            sensorView = new SensorView(sensor, this);
            connect(sensorView, &SensorView::deleteButtonPressed, this, &MainWindow::deleteSensor);
            connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::unsavedChanges);
            mainSplitter->addWidget(sensorView);
        }
    }

    void MainWindow::open() {
        QDir dirToStart(QCoreApplication::applicationDirPath());
        dirToStart.cdUp();
        dirToStart.cdUp();

        QString fileToOpenName = QFileDialog::getOpenFileName(this, "Open JSon File", dirToStart.absolutePath(), "*.json");
        if(fileToOpenName != "") {
            if(!cache->isArchiveEmpty()) {
                if(showWarningMessageBox("<b>ATTENZIONE!</b><br>Tutti i sensori già presenti verranno eliminati.<br>Continuare?") == 0)
                    return;
            }

            sensorsList->setFilterText("");

            cache->load(fileToOpenName.toStdString());

            sensorView->deleteLater();
            sensorView = new SensorView(nullptr, this);
            connect(sensorView, &SensorView::deleteButtonPressed, this, &MainWindow::deleteSensor);
            connect(sensorView, &SensorView::unsavedChanges, this, &MainWindow::unsavedChanges);
            mainSplitter->addWidget(sensorView);;
        }
    }

    void MainWindow::save() {
        cache->save();
        cache->setChangesSaved();
        this->setWindowTitle("Cleanroom Sim");
    }

    void MainWindow::saveAs() {
        QDir dirToStart(QCoreApplication::applicationDirPath());
        dirToStart.cdUp();
        dirToStart.cdUp();
        QString fileToSaveName = QFileDialog::getSaveFileName(this, "Save to JSon File", dirToStart.absolutePath(), "*.json");

        cache->save(fileToSaveName.toStdString());

        cache->setChangesSaved();
        this->setWindowTitle("Cleanroom Sim");
    }

    void MainWindow::unsavedChanges() {
        cache->setChangesSaved(false);
        this->setWindowTitle("Cleanroom Sim*");
    }

    void MainWindow::closeEvent(QCloseEvent* event) {
        if(!cache->isChangesSaved()){
            if(showWarningMessageBox("<b>ATTENZIONE!</b><br>Ci sono modifiche non salvate. Continuare?") == 1)
                event->accept();
            else
                event->ignore();
        }
    }

    int MainWindow::showWarningMessageBox(QString message) {
        QMessageBox* alertMessage = new QMessageBox(this);
        alertMessage->setIcon(QMessageBox::Warning);
        alertMessage->setText(message);
        alertMessage->setWindowTitle("Avviso");
        alertMessage->setAttribute(Qt::WA_DeleteOnClose);
        QPushButton* yesButton = new QPushButton("Ok", this);
        QPushButton* cancelButton = new QPushButton("Annulla", this);
        alertMessage->addButton(yesButton, QMessageBox::YesRole);
        alertMessage->addButton(cancelButton, QMessageBox::NoRole);
        alertMessage->setDefaultButton(yesButton);
        alertMessage->exec();
        if(alertMessage->clickedButton() == yesButton)
            return 1;
        else
            return 0;
    }
}
