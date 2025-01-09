#ifndef ARCHIVEOBSERVER_H
#define ARCHIVEOBSERVER_H

namespace Sensors {
namespace Storage {

    class Archive;

    class ArchiveObserver
    {
    public:
        // Costruttori
        ArchiveObserver() = default;

        // Gestione astratta observers
        virtual void notify(Archive& archive) = 0;
        virtual void destructor() = 0;

        // Distruttori
        virtual ~ArchiveObserver() = default;
    };

}
}

#endif // ARCHIVEOBSERVER_H
