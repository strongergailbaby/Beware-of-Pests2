#ifndef SFIELD
#define SFIELD
#include <stdint.h>
#include <QMetaType>

namespace BOP
{

struct SField
{
    SField() : pests(0),
               discovered(0),
               disarmed(0),
               neighbours(0)
    {}

    uint8_t pests       : 1;
    uint8_t discovered  : 1;
    uint8_t disarmed    : 2;
    uint8_t neighbours  : 4;
};

} // namespace BOP

Q_DECLARE_METATYPE(BOP::SField)

#endif // SFIELD

