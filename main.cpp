#include <mainwindow.h>
#include <Constants.h>
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(BOP::ORG);
    a.setOrganizationDomain(BOP::ORG);
    a.setApplicationName(BOP::APP);

    BOP::MainWindow window;
    window.show();
    window.updateView();
    return a.exec();
}
