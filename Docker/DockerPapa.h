#ifndef DOCKERPAPA_H
#define DOCKERPAPA_H

#include "Docker.h"

class DockerPapa : public Docker
{
public:
    DockerPapa();
    ~DockerPapa(){}

    void docking() override;
    void undocking() override;
    void stop() override;

private:
    void rodExtension();    // Фукнция выдвижения стрелы
    void rodRetraction();   // Фукнция возврата стрелы
    void pullingUp();       // Функция стягивания дронов
    void pushAway();        // Функция выдвижения стрелы, для расталкивания двух дронов
};

#endif // DOCKERPAPA_H
