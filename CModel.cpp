#include <model/CModel.h>
#include <cstdlib>
#include <ctime>

namespace BOP
{

using std::rand;

CModel::CModel()
    : m_width(0),
      m_height(0),
      m_totalPestsNr(0),
      m_discoveredFieldsNr(0),
      m_data()
{
}

void CModel::reset(int32_t width, int32_t height, int32_t pestsNumber)
{
    m_width         = width;
    m_height        = height;
    m_totalPestsNr  = pestsNumber;
    m_discoveredFieldsNr = 0;
    m_data.clear();

    const int64_t fieldsNr = size();
    m_data.reserve(fieldsNr);
    m_data.insert(m_data.begin(), fieldsNr, SField());

    srand(std::time(0));
}

void CModel::populate(int32_t xToSkip, int32_t yToSkip)
{
    populatePestsCrew(xToSkip, yToSkip);
    populateNeighbourhood();
}

void CModel::populatePestsCrew(int32_t xToSkip, int32_t yToSkip)
{
    Q_ASSERT(m_totalPestsNr < size());
    const uint64_t noPestsFieldId = yToSkip * m_width + xToSkip;
    int64_t pestsMade             = 0;

    while (pestsMade < m_totalPestsNr)
    {
        const uint64_t fieldId = rand() % size();
        Q_ASSERT(fieldId < m_data.size());

        if ((0 == m_data[fieldId].pests) && (fieldId != noPestsFieldId))
        {
            m_data[fieldId].pests = 1;
            pestsMade++;
        }
    }
}

bool CModel::checkWinCondition() const
{
    const int32_t fieldsToDiscover = size() - m_discoveredFieldsNr - m_totalPestsNr;
    return fieldsToDiscover == 0;
}

void CModel::populateNeighbourhood()
{
    for (int32_t x = 0; x < m_width; ++x)
    {
        for (int32_t y = 0; y < m_height; ++y)
        {
            const uint8_t pestsValue =
                    getPests  (x-1,   y-1) // up
                    + getPests (x,     y-1)
                    + getPests (x+1,   y-1)
                    + getPests (x-1,   y)   // mid
                    + getPests (x,     y)
                    + getPests (x+1,   y)
                    + getPests (x-1,   y+1) // down
                    + getPests (x,     y+1)
                    + getPests (x+1,   y+1);

            field(x,y).neighbours = pestsValue;
        }
    }
}

uint8_t CModel::getFlag(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).disarmed == 1 ? 1 : 0;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::countFlagsAround(int32_t x, int32_t y) const
{
    return getFlag    (x-1,   y-1) // up
            + getFlag (x,     y-1)
            + getFlag (x+1,   y-1)
            + getFlag (x-1,   y)   // mid
            + getFlag (x,     y)
            + getFlag (x+1,   y)
            + getFlag (x-1,   y+1) // down
            + getFlag (x,     y+1)
            + getFlag (x+1,   y+1);
}

uint8_t CModel::getNeighbours(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).neighbours;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::getPests(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).pests;
    }
    else
    {
        return 0;
    }
}

bool CModel::getDiscovered(int32_t x, int32_t y) const
{
    if (isValidIndex(x, y))
    {
        return field(x,y).discovered != 0;
    }
    else
    {
        return true;
    }
}

void CModel::discover(int32_t x, int32_t y)
{
    if (field(x, y).discovered == 0 && field(x,y).disarmed == 0)
    {
        field(x, y).discovered = 1;
        m_discoveredFieldsNr++;
    }
}

void CModel::disarm(int32_t x, int32_t y)
{
    if (field(x, y).disarmed < 2)
    {
        field(x, y).disarmed++;
    }
    else if (field(x, y).disarmed == 2)
    {
        field(x, y).disarmed = 0;
    }
}

bool CModel::isValidIndex(int32_t x, int32_t y) const
{
    return (x >= 0 && x < m_width && y >= 0 && y < m_height);
}

const SField& CModel::field(int32_t x, int32_t y) const
{
    const int32_t id = y * m_width + x;
    Q_ASSERT(id >= 0 && id < size());
    return m_data.at(id);
}

SField& CModel::field(int32_t x, int32_t y)
{
    const int32_t id = y * m_width + x;
    Q_ASSERT(id >= 0 && id < size());
    return m_data[id];
}

} // namespace BOP

