#ifndef DOCKERMAMA_H
#define DOCKERMAMA_H

#include "Docker.h"

class DockerMama : public Docker
{
public:
    DockerMama();
    ~DockerMama(){}

    void docking() override;
    void undocking() override;
    void stop() override;

};

#endif // DOCKERMAMA_H
