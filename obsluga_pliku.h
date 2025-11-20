#ifndef OBSLUGA_PLIKU_H
#define OBSLUGA_PLIKU_H
#include "main.h"
#include "ProstyUAR.h"
class Obsluga_pliku
{
    QJsonObject Model_ARX_to_Json(const ModelARX& model_arx) const;
    QJsonObject RegulatorPID_to_Json(const RegulatorPID& regulator_pid) const;
    QJsonObject ProstyUAR_to_Json(const ProstyUAR& prosty_uar) const;
public:
    Obsluga_pliku();
    void zapiszKonfiguracje(const ProstyUAR& uar,const ModelARX& arx,const RegulatorPID& pid)const ;
};

#endif // OBSLUGA_PLIKU_H
