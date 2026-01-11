#ifndef TESTY_SETTEROW_H
#define TESTY_SETTEROW_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "ProstyUAR.h"

class Testy_setterow
{
public:
    Testy_setterow();
    std::vector<std::string> wykonaj_testy();
    using Test = std::pair<std::string, std::function<bool()>>;
    static std::vector<Test> testy;
private:
    //testy arx dla ciebie kuba trzeba napisac testy do setterow z arx potem a uara i menedzera
    //testy regulator pid
    //testy generator
    //testy setterow w prosty uar
    //testy setterow w menedzer
};

#endif // TESTY_SETTEROW_H
