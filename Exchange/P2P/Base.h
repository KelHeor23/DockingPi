#ifndef BASE_H
#define BASE_H

#include <mutex>
#include <string>

class Base{
public:
    std::string msgMama;
    std::string msgPapa;
    std::mutex mtxMama;
    std::mutex mtxPapa;
};
#endif // BASE_H
