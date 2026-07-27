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
#include <QGraphicsPixmapItem>



class StorePage : public QWidget
{
    Q_OBJECT
public:

    StorePage(QWidget *parent = nullptr, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void initialSet();
    void Delete();

    ~StorePage() override;
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    abstractCardTemplate* createCardUI(abstractCard* card,
                                       QPointF pos,
                                       qreal z = 10);


    void createCardPrices();

    std::vector<QGraphicsSimpleTextItem*> cardPriceTexts;
    std::map<QGraphicsSimpleTextItem*, int> cardPriceValues;

    std::vector<QGraphicsSimpleTextItem*> potionPriceTexts;
    std::map<QGraphicsSimpleTextItem*, int> potionPriceValues;

    inline static constexpr int non_rare_card_number = 5;
    inline static constexpr int rare_card_count = 2;
    inline static constexpr int potion_number = 3;
    inline static int remove_card_price =75;
    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;
    BaseItem* board;

    std::vector<abstractCardTemplate*> cards ;
    std::unordered_map<abstractCard* , int> cardprice;

    std::vector<ImageItem*> potionImages;
    std::vector<PotionParent*> potions ;
    std::unordered_map<abstractPotion* , int> potionprice;

    std::unordered_map<abstractPotion*, QGraphicsSimpleTextItem*> potionPriceLabels;
    std::unordered_map<abstractCard*, QGraphicsSimpleTextItem*> cardPriceLabels;

    std::unordered_map<abstractCardTemplate*, abstractCard*> cardSources;


    void updateCardPricesColor();
    void updatePotionPricesColor();

    QPushButton* back_btn ;
    QGraphicsProxyWidget* back_prxy ;


    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;

    void createCards();

    void createPotions();

    void buyCard(abstractCard* card);

    void buyPotion(abstractPotion* potion);

    void buyRemoveCard();

    void createPotionPrices();

    void createRemoveButton();

    void createBackButton();

    bool removeUsed = false;

    CardParent* removeCardButton = nullptr;
    ImageItem* removeCardBg = nullptr;
    TextItem*  removeCardTitle = nullptr;
    TextItem*  removeCardDesc = nullptr;
    QGraphicsSimpleTextItem* removeCardPriceLabel = nullptr;

    std::unordered_map<QGraphicsSimpleTextItem*, QGraphicsPixmapItem*> priceCoinIcons;

    void attachCoinIcon(QGraphicsSimpleTextItem* txt, const QRectF& targetRect);

private slots:
    void createSelectCard(std::vector<abstractCard*> cards);
    void open_setting();
    void potion_right_click(abstractPotion* potion);
    void relic_right_click(abstractRelic* relic);
};

#endif // STOREPAGE_H
