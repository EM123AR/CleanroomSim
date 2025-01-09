#include "archive.h"
#include <algorithm>
#include <stdexcept>

/*
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>  // Per SHGetFolderPathA
#elif __APPLE__ || __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#endif*/

#include <QJsonArray>
#include <QJsonObject>
#include "Sensors/Converter/convertervisitor.h"
#include "Sensors/Converter/parser.h"
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <cctype>

namespace Sensors {
namespace Storage {

    unsigned int Archive::counter = 0;

    Archive::Archive() /*: path(getDocumentsPath() + "/CleanroomSimSaves/defaultSave.json")*/ {
        QDir dirToStart(QCoreApplication::applicationDirPath());
        dirToStart.cdUp();
        dirToStart.cdUp();
        path = dirToStart.absolutePath().toStdString() + "/defaultSave.json";
    }

    bool Archive::isChangesSaved() const {
        return changesSaved;
    }

    std::string Archive::getPath() const {
        return path;
    }

    std::map<unsigned int, Sensors::AbstractSensor*>* Archive::getCurrentSensors() {
        return &currentSensors;
    }

    const std::map<unsigned int, Sensors::AbstractSensor*>* Archive::getCurrentSensorsConst() const {
        return &currentSensors;
    }

    void Archive::setChangesSaved(bool changesSaved) {
        this->changesSaved = changesSaved;

        for(auto &observer : observersList)
            observer->notify(*this);
    }

    void Archive::setPath(std::string path) {
        this->path = path;

        for(auto &observer : observersList)
            observer->notify(*this);
    }

    void Archive::setCurrentSensors(const std::map<unsigned int, Sensors::AbstractSensor*>& currentSensors) {
        this->currentSensors = currentSensors;

        for(auto &observer : observersList)
            observer->notify(*this);
    }

    void Archive::addObserver(ArchiveObserver* archiveObserver) {
        observersList.push_back(archiveObserver);
    }

    void Archive::removeObserver(ArchiveObserver* archiveObserver) {
        observersList.erase(std::remove(observersList.begin(), observersList.end(), archiveObserver), observersList.end());
    }

    bool Archive::isArchiveEmpty() const {
        return currentSensors.empty();
    }

    Sensors::AbstractSensor* Archive::getSensorByIdentifier(unsigned int identifier) const {
        Sensors::AbstractSensor* sensor = nullptr;

        if(!isArchiveEmpty())
            try {
                sensor = currentSensors.at(identifier);
            } catch (const std::out_of_range& exception) {
                // NON TROVATO
            }

        return sensor;
    }

    void Archive::addSensor(Sensors::AbstractSensor* abstractSensor) {
        abstractSensor->setIdentifier(counter);
        currentSensors.insert({counter, abstractSensor});

        counter++;
        changesSaved = false;

        for(auto &observer : observersList)
            observer->notify(*this);
    }

    Sensors::AbstractSensor* Archive::takeSensorByIdentifier(unsigned int identifier) {
        Sensors::AbstractSensor* sensor = nullptr;

        if(!isArchiveEmpty()) {
            try {
                sensor = currentSensors.at(identifier);
                currentSensors.erase(identifier);

                changesSaved = false;

                for(auto &observer : observersList)
                    observer->notify(*this);
            } catch (const std::out_of_range& exception) {
                // NON TROVATO
            }
        }

        return sensor;
    }
/*
    std::string Archive::getDocumentsPath() const {
        #ifdef _WIN32
                char path[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path)))
                    return std::string(path);
                else
                    return "./";  // Fallback se SHGetFolderPathA fallisce

        #elif __APPLE__ || __linux__
                const char* homeDir = getenv("HOME");
                if (!homeDir)
                    homeDir = getpwuid(getuid())->pw_dir;

                return std::string(homeDir) + "/Documents";
        #else
                return "./"; // Fallback
        #endif
    }
*/
    std::string Archive::toLowerCase(const std::string& str) const {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),[](unsigned char c) {
            return std::tolower(c);
        });
        return lowerStr;
    }

    std::vector<Sensors::AbstractSensor*>* Archive::sensorsToVector() const {
        std::vector<AbstractSensor*> *vector = new std::vector<AbstractSensor*>();
        for(const auto &value : currentSensors)
            vector->push_back(value.second);

        return vector;
    }

    const std::vector<std::string>* Archive::splitFilterString(std::string filter) const {
        std::vector<std::string>* res = new std::vector<std::string>();
        long unsigned int iPos = 0;
        while(iPos < filter.size()) {
            iPos = filter.find(" ");
            res->push_back(filter.substr(0, iPos));
            filter.erase(0, iPos+1);
        }
        return res;
    }

    const std::vector<Sensors::AbstractSensor*>* Archive::filterName(std::string name) const {
        std::vector<Sensors::AbstractSensor*>* res;

        if(name != "") {
            //
            res = new std::vector<Sensors::AbstractSensor*>();
            const std::vector<std::string>* stringsInFilter = splitFilterString(name);
            std::string filterStringLower = toLowerCase(stringsInFilter->at(0));

            for(const auto &mapVal : currentSensors) {
                std::string sensorNameLower = toLowerCase(mapVal.second->getName());

                if(sensorNameLower.find(filterStringLower) != std::string::npos)
                    res->push_back(mapVal.second);
            }
            delete stringsInFilter;
        } else
            res = sensorsToVector();

        return res;
    }


    void Archive::save(std::string newPath) {
        if(newPath != "")
            path = newPath;

        QJsonArray jsonSensorsList;
        std::vector<Sensors::AbstractSensor*> *sensorsVector = sensorsToVector();


        for(const Sensors::AbstractSensor* sensor : *sensorsVector) {
            QJsonObject jsonSensor;

            jsonSensor["Identifier"] = (int)sensor->getIdentifier();
            jsonSensor["Name"] = QString::fromStdString(sensor->getName());
            jsonSensor["Description"] = QString::fromStdString(sensor->getDescription());
            jsonSensor["Plugged"] = (bool)sensor->isPlugged();
            jsonSensor["BatteryPercentage"] = (int)sensor->getBatteryPercentage();

            Converter::ConverterVisitor converter;
            sensor->accept(converter);

            QJsonObject* tempSensor = converter.getContent();
            foreach(const QString& genericKey, tempSensor->keys())
                jsonSensor[genericKey] = tempSensor->value(genericKey);


            jsonSensorsList.append(jsonSensor);
            delete tempSensor;
        }

        QJsonDocument jsonDocument(jsonSensorsList);
        QFile jsonFile(QString::fromStdString(path));

        if(!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // ERRORE APERTURA FILE
            return;
        }

            jsonFile.write(jsonDocument.toJson());
            jsonFile.close();

            changesSaved = true;
            for(auto &observer : observersList)
                observer->notify(*this);
    }


    void Archive::load(std::string path) {
        QFile jsonFile(QString::fromStdString(path));

        if(jsonFile.exists()) {
            if(jsonFile.open(QIODevice::ReadOnly)) {
                QByteArray rawData = jsonFile.readAll();

                QJsonParseError parsingError;
                QJsonDocument jsonDocument = QJsonDocument::fromJson(rawData, &parsingError);

                if(parsingError.error == QJsonParseError::NoError) {
                    if(jsonDocument.isArray()) {
                        std::vector<Sensors::AbstractSensor*>* currentVector = sensorsToVector();
                        for(auto &sensor : *currentVector)
                            delete sensor;

                        currentSensors.clear();
                        counter = 0;

                        QJsonArray sensorsToLoad = jsonDocument.array();
                        for(auto iterator = sensorsToLoad.begin(); iterator != sensorsToLoad.end(); ++iterator) {
                            Converter::Parser parser((*iterator).toObject());

                            Sensors::AbstractSensor* sensorToLoad = parser.getResultingSensor();

                            if(sensorToLoad != nullptr) {
                                currentSensors.insert({sensorToLoad->getIdentifier(), sensorToLoad});
                                counter = counter > sensorToLoad->getIdentifier() ? counter : sensorToLoad->getIdentifier()+1;
                            }
                        }

                        changesSaved = true;
                        this->path = path;
                        for(auto &observer : observersList)
                            observer->notify(*this);
                    }
                }
            }
        }
    }

    Archive::~Archive() {
        for(auto& value : currentSensors)
            delete value.second;

        for(auto& observer : observersList)
            observer->destructor();
    }

}
}
