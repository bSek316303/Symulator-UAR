#ifndef TESTY_SYMULACJI_H
#define TESTY_SYMULACJI_H

#include <string>
#include <vector>
#include <functional>

class Testy_symulacji
{
public:
    Testy_symulacji();
    std::vector<std::string> wykonaj_testy();
    using Test = std::pair<std::string, std::function<bool()>>;
    static std::vector<Test> testy;
private:
    //model arx
    static bool test_brakPobudzenia();
    static bool test_skokJednostkowy_1();
    static bool test_skokJednostkowy_2();
    static bool test_skokJednostkowy_3();
    //regulator pid
    static bool test_P_brakPobudzenia();
    static bool test_P_skokJednostkowy();
    static bool test_PI_skokJednostkowy_1();
    static bool test_PI_skokJednostkowy_2();
    static bool test_PID_skokJednostkowy();
    static bool test_PI_skokJednostkowy_3();
    //prosty uar
    static bool test_UAR_1_brakPobudzenia();
    static bool test_UAR_1_skokJednostkowyPID();
    static bool test_UAR_2_skokJednostkowyPID();
    static bool test_UAR_3_skokJednostkowyPID();
};

#endif // TESTY_SYMULACJI_H
