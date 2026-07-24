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

    int f3 = QFontDatabase::addApplicationFont(":/fonts/titrZ");
    const QStringList titrFamilies = QFontDatabase::applicationFontFamilies(f3);
    if (!titrFamilies.isEmpty())
        Fonts::titrZ = titrFamilies.first();

    int f4 = QFontDatabase::addApplicationFont(":/fonts/rock");
    const QStringList rockFamilies = QFontDatabase::applicationFontFamilies(f4);
    if (!rockFamilies.isEmpty())
        Fonts::rock = rockFamilies.first();

    int f5 = QFontDatabase::addApplicationFont(":/fonts/cinema");
    const QStringList cinemaFamilies = QFontDatabase::applicationFontFamilies(f5);
    if (!cinemaFamilies.isEmpty())
        Fonts::cinema = cinemaFamilies.first();

    int f6 = QFontDatabase::addApplicationFont(":/fonts/lotrance");
    const QStringList lotranceFamilies = QFontDatabase::applicationFontFamilies(f6);
    if (!lotranceFamilies.isEmpty())
        Fonts::lotrance = lotranceFamilies.first();

    int f7 = QFontDatabase::addApplicationFont(":/fonts/forte");
    const QStringList forteFamilies = QFontDatabase::applicationFontFamilies(f7);
    if (!forteFamilies.isEmpty())
        Fonts::forte = forteFamilies.first();

    int f8 = QFontDatabase::addApplicationFont(":/fonts/ebhaar");
    const QStringList ebhaarFamilies = QFontDatabase::applicationFontFamilies(f8);
    if (!ebhaarFamilies.isEmpty())
        Fonts::ebhaar = ebhaarFamilies.first();

    if (!Fonts::Cascadia.isEmpty()) {
        a.setFont(QFont(Fonts::Cascadia, 11));

        QString globalStyle = QString(
                                  "* { font-family: '%1' !important; }"
                                  ).arg(Fonts::Cascadia);

        a.setStyleSheet(globalStyle);
    }


    MainWindow w;
    w.show();
    return QApplication::exec();

}
