#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QToolButton>

namespace View {

    class Toolbar : public QToolBar
    {    Q_OBJECT

    private:
        // Attributi
        QToolButton *openButton;    /// bottone apri file Json
        QToolButton *saveButton;    /// bottone salva in file aperto/default Json
        QToolButton *saveAsButton;  /// bottone salva su file Json specificato

    public:
        // Costruttori
        Toolbar(QWidget* parent = nullptr);

        // Distruttori
        ~Toolbar() = default;

    signals:
        // Gestione segnali
        void openButtonPressed();
        void saveButtonPressed();
        void saveAsButtonPressed();
    };

}

#endif // TOOLBAR_H
