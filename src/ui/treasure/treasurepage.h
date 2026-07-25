#ifndef TREASUREPAGE_H
#define TREASUREPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "categories/general.h"
#include "entity/ironclad.h"
#include "ui/relicbar/relicbar.h"
#include "ui/topbar/combattopbar.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "combat/manageCombat/combatrewards.h"

class TreasurePage : public QWidget
{
    Q_OBJECT
public:
    TreasurePage(QWidget *parent = nullptr, ChestType type = ChestType::regular, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void showHost();
    void initialSet();
    void getRew();
    void Delete();

    ~TreasurePage() override;
protected:
    void resizeEvent(QResizeEvent *event) override;
    ChestType type;

private:

    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;

    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;

    ImageItem* chest_image;
    ImageItem* host_image;
    BaseItem* dialog_parent;
    ImageItem* host_dilogbox;
    TextItem* host_name;
    TextItem* host_mess;

    QMediaPlayer* media_player;
    QAudioOutput* bg_music;

    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;

    std::vector<QString> veilcladLines;
    std::vector<QString> oathcladLines;
private slots:
    void createCollectReward(combatReward* reward);
    void open_setting();
};

#endif // TREASUREPAGE_H
