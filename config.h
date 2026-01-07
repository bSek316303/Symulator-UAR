#ifndef CONFIG_H
#define CONFIG_H
#include <functional>
#include <stale.h>

class Config
{
protected:
    using obserwator = std::function<void(Config&)>;
    obserwator m_obserwator;
public:
    Config(){}
    virtual ~Config() = default;
    void powiadom(){
        m_obserwator(*this);
    }
    void set_obserwator(obserwator obserwator){
        m_obserwator = obserwator;
    }
};

#endif // CONFIG_H
