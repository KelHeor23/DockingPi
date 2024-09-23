#ifndef DOCKERFACTORY_H
#define DOCKERFACTORY_H

#include <memory>

#include "DockerMama.h"
#include "DockerPapa.h"

std::string types_g = "Mama Papa";

enum Dockers {
    Mama,
    Papa
};

class DockerFactory
{
public:
    std::unique_ptr<Docker> makeDocker(Dockers type) {
        switch(type){
        case Mama:
            return std::make_unique<DockerMama>();
        case Papa:
            return std::make_unique<DockerPapa>();
        default:
            return nullptr;
        }
    }
};

#endif // DOCKERFACTORY_H
