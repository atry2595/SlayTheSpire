#include "ui/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>
#include "core/setting.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SlayTheSpire_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    int f1 = QFontDatabase::addApplicationFont(":/fonts/cascadia");
    const QStringList cascadiaFamilies = QFontDatabase::applicationFontFamilies(f1);
    if (!cascadiaFamilies.isEmpty())
        Fonts::Cascadia = cascadiaFamilies.first();

    int f2 = QFontDatabase::addApplicationFont(":/fonts/koodak");
    const QStringList koodakFamilies = QFontDatabase::applicationFontFamilies(f2);
    if (!koodakFamilies.isEmpty())
        Fonts::koodak = koodakFamilies.first();



    MainWindow w;
    w.show();
    return QApplication::exec();

}
