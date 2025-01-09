#include "toolbar.h"

namespace View {

    Toolbar::Toolbar(QWidget* parent)
    : QToolBar{parent}, openButton(nullptr), saveButton(nullptr), saveAsButton(nullptr) {
        QAction* open = new QAction("Apri file", this);
        open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        open->setIcon(QIcon(":/Icons/Buttons/open.svg"));
        open->setToolTip("Apri file Json di salvataggio");

        QAction *save = new QAction("Salva", this);
        save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
        save->setIcon(QIcon(":/Icons/Buttons/save.svg"));
        save->setToolTip("Salva nel file aperto");

        QAction *saveAs = new QAction("Salva con nome", this);
        saveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
        saveAs->setIcon(QIcon(":/Icons/Buttons/save_as.svg"));
        saveAs->setToolTip("Salva su nuovo file Json");

        this->addActions({open, save, saveAs});
        this->insertSeparator(save);
        this->insertSeparator(saveAs);
        this->setMinimumHeight(30);

        openButton = dynamic_cast<QToolButton*>(this->widgetForAction(open));
        openButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        openButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        saveButton = dynamic_cast<QToolButton*>(this->widgetForAction(save));
        saveButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        saveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        saveAsButton = dynamic_cast<QToolButton*>(this->widgetForAction(saveAs));
        saveAsButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        saveAsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        // Connessioni
        /// Carica Json
        connect(open, &QAction::triggered, this, &Toolbar::openButtonPressed);
        /// Salva Json aperto/default
        connect(save, &QAction::triggered, this, &Toolbar::saveButtonPressed);
        /// Salva Json specificato
        connect(saveAs, &QAction::triggered, this, &Toolbar::saveAsButtonPressed);
    }

}
