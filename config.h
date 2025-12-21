#ifndef CONFIG_H
#define CONFIG_H
#include <functional>

class Config
{
protected:
    using obserwator = std::function<void(Config&)>;
public:
    Config();
    virtual void powiadom() = 0;
    virtual void set_obserwator(obserwator obserwator) = 0;
};

#endif // CONFIG_H
