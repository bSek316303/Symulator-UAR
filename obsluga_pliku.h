#ifndef OBSLUGA_PLIKU_H
#define OBSLUGA_PLIKU_H
#include "main.h"
#include "ProstyUAR.h"
class Obsluga_pliku
{
    QJsonObject Model_ARX_to_Json() const;
    QJsonObject RegulatorPID_to_Json() const;
    QJsonObject ProstyUAR_to_Json() const;
public:
    Obsluga_pliku();
};

#endif // OBSLUGA_PLIKU_H
