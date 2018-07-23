#include <model/CTableModel.h>
#include <QPixmap>
#include <QSize>

namespace BOP
{

CTableModel::CTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_model(),
      m_pestsDisplay(0),
      m_initialized(false)
{
}

void CTableModel::init(const QModelIndex &index)
{
    m_model.populate(index.row(), index.column());
    m_initialized = true;
    emit gameStarted();
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.width();
}
int CTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.height();
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (Qt::UserRole == role)
    {
        QVariant variant;
        variant.setValue(m_model.field(index.row(), index.column()));
        return variant;
    }

    return QVariant();
}

void CTableModel::resetModel(int32_t width, int32_t height, int32_t pests)
{
    m_initialized  = false;
    m_pestsDisplay = pests;
    m_model.reset(width, height, pests);
    emit pestsDisplay(pests);
    emit layoutChanged();
}

void CTableModel::onTableClicked(const QModelIndex &index)
{
    if (m_model.field(index.row(), index.column()).disarmed == 0)
    {
        discover(index);
    }
}

void CTableModel::discover(const QModelIndex &index)
{
    if (!m_initialized)
    {
        init(index);
    }

    const int32_t x = index.row();
    const int32_t y = index.column();

    m_model.discover(x, y);

    if (m_model.field(x, y).neighbours == 0 && m_model.field(x, y).pests == 0)
    {
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1)); // up
        if (!m_model.getDiscovered(x,   y-1))   discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));   // mid
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1)); // down
        if (!m_model.getDiscovered(x,   y+1))   discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }

    emit dataChanged(index, index);

    if (m_model.field(x, y).pests && m_model.field(x, y).disarmed == 0)
    {
        emit gameLost();
    }
    else if (m_model.checkWinCondition())
    {
        emit gameWon();
    }
}

void CTableModel::onRightClicked(const QModelIndex &index)
{
    const int32_t x = index.row();
    const int32_t y = index.column();

    if (m_model.field(x, y).discovered == 0)
    {
        m_model.disarm(x, y);

        if (m_model.field(x, y).disarmed == 1)
        {
            m_pestsDisplay--;
        }
        else if (m_model.field(x, y).disarmed == 0)
        {
            m_pestsDisplay++;
        }

        emit pestsDisplay(m_pestsDisplay);
        emit dataChanged(index, index);
    }
}

void CTableModel::onBothClicked(const QModelIndex &index)
{
    const int32_t x = index.row();
    const int32_t y = index.column();

    if (m_model.getDiscovered(x, y)
            && m_model.getNeighbours(x, y) == m_model.countFlagsAround(x, y))
    {
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1)); // up
        if (!m_model.getDiscovered(x, y-1))     discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));   // mid
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1)); // down
        if (!m_model.getDiscovered(x, y+1))     discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }
}

} // namespace BOP
