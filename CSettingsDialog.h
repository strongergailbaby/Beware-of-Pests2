#ifndef CSETTINGSDIALOG_H
#define CSETTINGSDIALOG_H

#include <SPreferences.h>
#include <QDialog>

namespace Ui {
class CSettingsDialog;
}

namespace BOP
{

class CSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    ~CSettingsDialog();
    static bool getPreferences(SPreferences &prefs, QWidget* parent = 0);

public slots:
    void updateRange();

private:
    explicit CSettingsDialog(QWidget *parent = 0);
    Ui::CSettingsDialog *ui;
};

} // namespace BOP
#endif // CSETTINGSDIALOG_H
