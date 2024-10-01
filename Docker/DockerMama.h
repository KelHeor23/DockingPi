#ifndef DOCKERMAMA_H
#define DOCKERMAMA_H

#include "Docker.h"

class DockerMama : public Docker
{
public:
    DockerMama();
    ~DockerMama(){}

    void docking()      override;
    void undocking()    override;
    void stop()         override;

private:
    void lockingHooks();            // Функция закрытия крюков
    void cargoTransferBegin();      // Функция плавного старта/подготовки к приему телеги
    void cargoTransferEnding();     // Функция плавного завершения приёма телеги
};

#endif // DOCKERMAMA_H
