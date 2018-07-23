#ifndef CONSTANTS
#define CONSTANTS

#include <QString>

namespace BOP
{

// Global names
const QString APP               = "BewareOfPests";
const QString ORG               = "katecpp";

// Icon path
const QString SMALL_PEST_PATH      = ":/images/small_pest.png";
const QString WRONG_PATH  = ":/images/wrong.png";
const QString BIG_PEST_PATH        = ":/images/big_pest.png";
const QString DISARMED_PATH         = ":/images/disarmed.png";
const QString DISARMED_RED_PATH     = ":/images/disarmed_red.png";
const QString QUESTION_PATH         = ":/images/question.png";
const QString SAD_FACE              = "://images/sad_32.png";
const QString NORMAL_FACE           = "://images/normal_32.png";
const QString FEAR_FACE             = "://images/fear_32.png";
const QString HAPPY_FACE            = "://images/happy_32.png";

// Icon size
const int32_t FIELD_SIZE        = 24;
const int32_t ICON_SIZE         = 16;

// Default game preferences
const int32_t DEFAULT_HEIGHT    = 10;
const int32_t DEFAULT_WIDTH     = 10;
const int32_t DEFAULT_PESTS     = 10;

const int32_t MSG_TIMEOUT       = 5000;

const double MIN_DENSITY        = 0.05;
const double MAX_DENSITY        = 0.95;

} // namespace BOP

#endif // CONSTANTS
