#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class CTopWidget;
}

namespace BOP
{

class CTopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTopWidget(QWidget *parent = 0);
    ~CTopWidget();

signals:
    void buttonClicked();

public slots:
    void setPestsDisplay(int32_t pestsRemained);
    void incrementTimer();
    void resetTimer();
    void onPressed();
    void onReleased();
    void onWon();
    void onLost();
    void setDefault();

private:
    void init();

    Ui::CTopWidget *ui;
    int32_t        m_time;
    QIcon          m_normalFace;
    QIcon          m_fearFace;
    QIcon          m_happyFace;
    QIcon          m_sadFace;
};

} // namespace BOP

#endif // TOPWIDGET_H

