#include "edithygrometerwindow.h"
#include <QVBoxLayout>
#include "View/sensorviewer.h"
#include <QPushButton>

namespace View {
namespace Dialogs {

    EditHygrometerWindow::EditHygrometerWindow(Sensors::Hygrometer* sensor, QWidget* parent)
    : QDialog{parent}, type(nullptr), name(nullptr), description(nullptr), desiredAvg(nullptr), plugged(nullptr), confirmButton(nullptr), cancelButton(nullptr), sensor(sensor) {
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QHBoxLayout* buttonLayout = new QHBoxLayout();

        // Avvisi campi obbligatori
        QLabel* upperWarnLabel = new QLabel("<b>ATTENZIONE</b>", this);
        QLabel* mainWarnLabel = new QLabel("Nome obbligatorio.");
        mainLayout->addWidget(upperWarnLabel, 0, Qt::AlignHCenter);
        mainLayout->addWidget(mainWarnLabel, 0, Qt::AlignHCenter);

        // Tipo sensore
        QHBoxLayout* typeLayout = new QHBoxLayout();
        QLabel* sensorTypeLabel = new QLabel("Tipo: ",this);
        type = new QLabel(this);
        SensorViewer sVisitor;
        sensor->accept(sVisitor);

        delete sVisitor.getIconWidget();
        delete sVisitor.getInfoWidget();
        type->setText(sVisitor.getType());
        type->setStyleSheet("font-style: italic");

        typeLayout->addWidget(sensorTypeLabel);
        typeLayout->addWidget(type, 0, Qt::AlignRight);

        // Modifica nome
        QHBoxLayout* nameLayout = new QHBoxLayout();
        QLabel* sensorNameLabel = new QLabel("Nome: ", this);
        name = new QLineEdit(QString::fromStdString(sensor->getName()), this);
        name->setPlaceholderText("Nuovo nome...");
        nameLayout->addWidget(sensorNameLabel);
        nameLayout->addWidget(name);

        // Modifica descrizione
        QHBoxLayout* descriptionLayout = new QHBoxLayout();
        QLabel* sensorDescriptionLabel = new QLabel("Descrizione: ", this);
        description = new QTextEdit(QString::fromStdString(sensor->getDescription()), this);
        description->setPlaceholderText("Nuova descrizione...");
        descriptionLayout->addWidget(sensorDescriptionLabel, 0, Qt::AlignTop);
        descriptionLayout->addWidget(description);

        // Modifica media desiderata con etichetta numerica slider dinamica (lambda expression)
        QHBoxLayout* desiredAvgLayout = new QHBoxLayout();
        QLabel* sensorDesiredAvgLabel = new QLabel("Media desiderata (%): ", this);
        desiredAvg = new QSlider(Qt::Horizontal, this);

        QLabel* sliderLabel = new QLabel(QString::number(desiredAvg->value()));
        QObject::connect(desiredAvg, &QSlider::valueChanged, [sliderLabel](int value) {
           sliderLabel->setText(QString::number(value));
        });

        desiredAvg->setValue(sensor->getOptimalAvg());
        desiredAvg->setRange(0, 100);
        desiredAvgLayout->addWidget(sensorDesiredAvgLabel, 0, Qt::AlignTop);
        desiredAvgLayout->addWidget(desiredAvg);
        desiredAvgLayout->addWidget(sliderLabel);

        // Modifica plugged
        QHBoxLayout* pluggedLayout = new QHBoxLayout();
        QLabel* sensorPluggedLabel = new QLabel("Alimentazione: ", this);
        plugged = new QCheckBox("collegato alla rete elettrica", this);
        plugged->setChecked(sensor->isPlugged());
        pluggedLayout->addWidget(sensorPluggedLabel, 0, Qt::AlignTop);
        pluggedLayout->addWidget(plugged);

        // Bottoni
        confirmButton = new QPushButton("Modifica", this);
        buttonLayout->addWidget(confirmButton);

        cancelButton = new QPushButton("Annulla", this);
        buttonLayout->addWidget(cancelButton);

        // Connessioni
        /// Modifica sensore
        connect(confirmButton, &QPushButton::clicked, this, &EditHygrometerWindow::editSensor);
        connect(confirmButton, &QPushButton::clicked, this, &EditHygrometerWindow::close);
        /// Annullamento operazione
        connect(cancelButton, &QPushButton::clicked, this, &EditHygrometerWindow::close);
        /// Controllo inserimento nome
        connect(name, &QLineEdit::textChanged, this, &EditHygrometerWindow::sensorNameChanged);

        // Unione layout
        mainLayout->addLayout(typeLayout);
        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(descriptionLayout);
        mainLayout->addLayout(desiredAvgLayout);
        mainLayout->addLayout(pluggedLayout);

        policy = new QLabel(this);
        policy->setText("<b>INSERIRE TUTTI I DATI RICHIESTI</b>");
        mainLayout->addWidget(policy, 0, Qt::AlignHCenter);
        policy->hide();

        mainLayout->addLayout(buttonLayout);

        this->setLayout(mainLayout);
    }

    void EditHygrometerWindow::editSensor() {
        sensor->setName(name->text().toStdString());
        sensor->setDescription(description->toPlainText().toStdString());
        sensor->setOptimalAvg(desiredAvg->value());
        sensor->setPlugged(plugged->isChecked());
        emit done(QDialog::Accepted);
    }

    void EditHygrometerWindow::sensorNameChanged(const QString &text) {
        if(text == "") {
            confirmButton->setDisabled(true);
            policy->show();
        } else {
            confirmButton->setDisabled(false);
            policy->hide();
        }
    }
}
}
