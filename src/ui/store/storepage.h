#ifndef STOREPAGE_H
#define STOREPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "categories/general.h"
#include "entity/ironclad.h"
#include "ui/relicbar/relicbar.h"
#include "ui/topbar/combattopbar.h"
#include <QMediaPlayer>
#include "ui/selectItem/selectcard.h"
#include <QAudioOutput>
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplatelegend.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplaterare.h"
#include "ui/entities/potionparent.h"



class StorePage : public QWidget
{
    Q_OBJECT
public:

    StorePage(QWidget *parent = nullptr, ChestType type = ChestType::regular, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void initialSet();
    void Delete();

    ~StorePage() override;
protected:
    void resizeEvent(QResizeEvent *event) override;

private:

    inline static int non_rare_card_number =5;
    inline static int rare_card_number =1;
    inline static int mystery_card_number =1;
    inline static int potion_number =3;
    inline static int remove_card_price =75;
    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;
    BaseItem* board;

    std::vector<abstractCardTemplate*> cards ;
    std::unordered_map<abstractCard* , int> cardprice;

    std::vector<PotionParent*> potions ;
    std::unordered_map<abstractPotion* , int> potionprice;


    QPushButton* remove_btn ;
    QGraphicsProxyWidget* remove_prxy ;

    QPushButton* back_btn ;
    QGraphicsProxyWidget* back_prxy ;


    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;

    std::vector<QString> veilcladLines;
    std::vector<QString> oathcladLines;
private slots:
    void createCollectReward(combatReward* reward);
    void open_setting();
};

#endif // STOREPAGE_H
