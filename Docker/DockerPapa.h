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

private:
    void rodExtension();    // Фукнция выдвижения стрелы
    void rodRetraction();   // Фукнция возврата стрелы
};

#endif // DOCKERPAPA_H
