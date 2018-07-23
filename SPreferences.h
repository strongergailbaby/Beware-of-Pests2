#ifndef SPREFERENCES_H
#define SPREFERENCES_H

#include <Constants.h>
#include <stdint.h>

namespace BOP
{

struct SPreferences
{
    SPreferences() : width(DEFAULT_HEIGHT),
                     height(DEFAULT_WIDTH),
                     pests(DEFAULT_PESTS)
    {}

    int32_t width;
    int32_t height;
    int32_t pests;
};

} // namespace BOP

#endif // SPREFERENCES_H
