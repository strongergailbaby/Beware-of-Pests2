#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H

#include <QAbstractTableModel>
#include <model/CModel.h>

namespace BOP
{

class CTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit CTableModel(QObject *parent = 0);
    ~CTableModel() = default;

    QVariant data(const QModelIndex &index, int role) const override;
    int      rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int      columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void     resetModel(int32_t width, int32_t height, int32_t pests);

signals:
    void     gameStarted();
    void     gameLost();
    void     gameWon();
    void     pestsDisplay(int32_t pestsCount);

public slots:
    void     onTableClicked(const QModelIndex &index);
    void     onRightClicked(const QModelIndex &index);
    void     onBothClicked(const QModelIndex &index);

private:
    void     init(const QModelIndex &index);
    void     discover(const QModelIndex &index);

    CModel   m_model;
    int32_t  m_pestsDisplay;
    bool     m_initialized;
};

} // namespace BOP

#endif // CTABLEMODEL_H
