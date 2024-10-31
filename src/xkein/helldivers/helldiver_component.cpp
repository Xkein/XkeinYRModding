#include "xkein/helldivers/helldiver_component.h"

DefaultIniContainer<HelldiverStratagem>& HelldiverStratagem::GetIniContainer()
{
    static DefaultIniContainer<HelldiverStratagem> container;
    return container;
}

