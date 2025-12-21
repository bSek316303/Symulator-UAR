#include "arxconfig.h"

ARXConfig::ARXConfig() {}

void ARXConfig::set_obserwator(obserwator obserwator){
    m_obserwator = std::move(obserwator);
}
