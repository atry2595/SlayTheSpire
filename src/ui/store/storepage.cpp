#include "storepage.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "core/setting.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/selectItem/collectreward.h"
#include "ui/topbar/combatsetting.h"
#include "utils/RNG.h"
#include "items/relics/relicfactory.h"
#include "ui/selectItem/selectrelic.h"
#include "cards/cardfactory.h"
#include "items/potions/potionfactory.h"
#include "categories/potions.h"
#include "ui/infobar/combatinfobar.h"
#include "ui/cards/cardparent.h"
#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "assetsManager/imagemanager.h"
#include "ui/selectItem/selectcard.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "ui/selectItem/selectpotion.h"

StorePage::StorePage(QWidget *parent, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , player(plyr)
    , eve(eve)
{

    auto mng = imageManager::instance();
    auto sound = soundManager::instance();



    //----------------------------------------------------
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: black;");

    combatView->setRenderHint(QPainter::Antialiasing, true);
    combatView->setRenderHint(QPainter::SmoothPixmapTransform, true);


    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

    //----------------------------------------------------

    bar = new CombatTopBar(eve, player, true);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());

    soundManager::instance().playBackMusic((combat_data::act == 1) ? (BgMusic::act1_rest) : ((BgMusic::act2_rest) ));

    auto img = new ImageItem(nullptr, {1650, 950}, {0,0}); img->setPixmap(imageManager::instance().getBackroundImage());
    img->setZValue(0);
    combatScene->addItem(img);

    //----------------------------------------------------
    connect(eve,
            &combatEvent::potionRightButton,
            this,
            &StorePage::potion_right_click);

    connect(eve,
            &combatEvent::relicRightButton,
            this,
            &StorePage::relic_right_click);

    connect(
        eve,
        &combatEvent::selectCard,
        this,
        &StorePage::createSelectCard
        );

    connect(eve,
            &combatEvent::cardPressed,
            this,
            [this](CardParent* card)
            {
                if(card == removeCardButton)
                {
                    buyRemoveCard();
                    return;
                }

                buyCard(card->getSource());
            });

    connect(eve, &combatEvent::potionPressed, this, [this](PotionParent* p){
        buyPotion(p->getSource());
    });

    connect(eve, &combatEvent::settingOpen, this, &StorePage::open_setting);

    connect(eve, &combatEvent::selectPotion, this, &StorePage::createSelectPotion);


    black_screen = new BaseItem(nullptr, {1700, 1000}, {-50, -50});
    black_screen->setBackColor(Qt::black);
    black_screen->setOpacity(1);
    black_screen->setZValue(200000);
    combatScene->addItem(black_screen);
    black_screen->fadeTo(0, 500);

    initialSet();
}

StorePage::~StorePage() {

    for (auto tmpl : cards) {
        delete tmpl;
    }
    cards.clear();

    for (auto& pair : cardprice) {
        delete pair.first;
    }
    cardprice.clear();
    cardSources.clear();

    for (auto& pair : potionprice) {
        delete pair.first;
    }
    potionprice.clear();
    potions.clear();

    potionImages.clear();
    cardPriceTexts.clear();
    cardPriceValues.clear();
    potionPriceTexts.clear();
    potionPriceValues.clear();
    cardPriceLabels.clear();
    potionPriceLabels.clear();
    priceCoinIcons.clear();

    removeCardButton = nullptr;
    removeCardPriceLabel = nullptr;

    if (bar) {
        delete bar;
        bar = nullptr;
    }
    if (relic_bar) {
        delete relic_bar;
        relic_bar = nullptr;
    }

    if (black_screen) delete black_screen;

    if (combatScene) {
        delete combatScene;
        combatScene = nullptr;
    }
    if (combatView) {
        delete combatView;
        combatView = nullptr;
    }

    player = nullptr;
    eve = nullptr;
}

void StorePage::Delete() {
    black_screen->setBackColor(Qt::black);
    black_screen->setOpacity(0);
    black_screen->setZValue(200000);
    combatScene->addItem(black_screen);
    black_screen->fadeTo(1, 500);

    QTimer::singleShot(1000, [=](){
        this->deleteLater();
    });
}


void StorePage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

void StorePage::attachCoinIcon(QGraphicsSimpleTextItem* txt, const QRectF& targetRect)
{
    QPixmap coin(":/icon/coin.ico");
    coin = coin.scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* icon = combatScene->addPixmap(coin);
    icon->setZValue(1000);

    qreal gap = 4;
    qreal totalWidth = coin.width() + gap + txt->boundingRect().width();
    qreal startX = targetRect.center().x() - totalWidth / 2.0;
    qreal y = targetRect.bottom() + 2;

    icon->setPos(startX, y + (txt->boundingRect().height() - coin.height()) / 2.0);
    txt->setPos(startX + coin.width() + gap, y);

    priceCoinIcons[txt] = icon;
}

abstractCardTemplate* StorePage::createCardUI(abstractCard *card,QPointF pos,qreal z)
{
    abstractCardTemplate* ui = nullptr;

    switch (combat_data::selected_card_template)
    {
    case cardTemplates::common:
        ui = new CardTemplateCommon(eve,card,pos,QSizeF(200,300),z);
        break;

    case cardTemplates::ancient:
        ui = new CardTemplateUncommon(eve,card,pos,QSizeF(200,300),z);
        break;

    case cardTemplates::metallic:
        ui = new CardTemplateRare(eve,card,pos,QSizeF(200,300),z);
        break;

    case cardTemplates::toxic_blossom:
        ui = new CardTemplateLegend(eve,card,pos,QSizeF(200,300),z);
        break;
    }

    ui->getParent()->setCanHover(false);
    ui->getParent()->setCanSelect(false);


    if(!ui)
        return nullptr;

    combatScene->addItem(ui->getParent());

    ui->updateCard();

    return ui;
}

void StorePage::createCards()
{
    auto& rng = RNG::instance();

    std::vector<cardID> selectedCards;

    // Non Rare
    auto normal = rng.sample(non_rare_cards, non_rare_card_number);

    for (auto id : normal)
        selectedCards.push_back(id);

    // Rare
    auto rare = rng.sample(rare_cards, rare_card_count);

    for (auto id : rare)
        selectedCards.push_back(id);

    QPointF startPos(120, 145);

    const int dx = 275;
    const int dy = 395;

    for (int i = 0; i < (int)selectedCards.size(); i++)
    {
        abstractCard* card = CardFactory::createCard(selectedCards[i]);

        if(card == nullptr)
            continue;

        if(i < non_rare_card_number)
            cardprice[card] = rng.randint(50,80);
        else
            cardprice[card] = rng.randint(120,180);

        int row = i / 4;
        int col = i % 4;

        QPointF pos(
            startPos.x() + col * dx,
            startPos.y() + row * dy
            );

        auto ui = createCardUI(card, pos);

        if(ui == nullptr)
            continue;

        cards.push_back(ui);
        cardSources[ui] = card;
    }
}

void StorePage::createCardPrices()
{
    QFont font;
    font.setFamily(setting::game_language== language::English ? (Fonts::Cascadia) : (Fonts::koodak));
    font.setPointSize(22);
    font.setBold(true);

    for (int i = 0; i < cards.size(); i++)
    {
        auto card = cards[i];

        auto sourceItr = cardSources.find(card);

        if(sourceItr == cardSources.end())
            continue;

        abstractCard* source = sourceItr->second;

        auto itr = cardprice.find(source);

        if(itr == cardprice.end())
            continue;

        int price = itr->second;

        auto* txt = combatScene->addSimpleText(QString::number(price), font);

        if(player->get_gold() >= price)
        {
            txt->setBrush(QColor(255,220,80));
        }
        else
        {
            txt->setBrush(QColor(200,40,40));
        }

        QRectF rect = card->getParent()->sceneBoundingRect();
        attachCoinIcon(txt, rect);

        txt->setZValue(1000);


        cardPriceTexts.push_back(txt);
        cardPriceValues[txt] = price;
        cardPriceLabels[source] = txt;
    }
}

void StorePage::updateCardPricesColor()
{
    for(auto& item : cardPriceValues)
    {
        QGraphicsSimpleTextItem* txt = item.first;
        int price = item.second;


        if(player->get_gold() >= price)
        {
            txt->setBrush(QColor(255,220,80));
        }
        else
        {
            txt->setBrush(QColor(200,40,40));
        }
    }
}

void StorePage::createPotions()
{
    auto& rng = RNG::instance();

    std::vector<potionID> allPotions;

    allPotions.insert(
        allPotions.end(),
        common_potions.begin(),
        common_potions.end());

    allPotions.insert(
        allPotions.end(),
        uncommon_potions.begin(),
        uncommon_potions.end());

    allPotions.insert(
        allPotions.end(),
        rare_potions.begin(),
        rare_potions.end());

    auto selected = rng.sample(allPotions, potion_number);

    QPointF startPos(1325,145);

    const int dy = 225;

    for(int i = 0 ; i < selected.size() ; i++)
    {
        abstractPotion* potion =
            PotionFactory::createPotion(selected[i], player);

        if(!potion)
            continue;

        potionprice[potion] = rng.randint(60,120);

        auto* ui = new PotionParent(eve,potion,parent,QSizeF(130,130),QPointF(startPos.x(),startPos.y()+i*dy),30);

        ui->setCanHover(false);
        ui->setCanSelect(false);

        ImageItem* img = new ImageItem(
            ui,
            QSizeF(130,130),
            QPointF(0,0)
            );

        img->setPixmap(
            imageManager::instance().getPotionIcon(
                potion->get_ID()
                )
            );

        potions.push_back(ui);
        potionImages.push_back(img);
    }
}

void StorePage::buyPotion(abstractPotion* potion)
{
    // find قیمت


    auto priceItr = potionprice.find(potion);

    if(priceItr == potionprice.end())
        return;

    int price = priceItr->second;

    if(player->get_gold() < price)
        return;

    player->lose_gold(price);
    soundManager::instance(). playSoundEffect(SoundEffect::drinkPotion);


    bar->updateBar();

    updateCardPricesColor();
    updatePotionPricesColor();

    player->potion_list_add(potion);

    PotionParent* potionUI = nullptr;

    for(auto item : potions)
    {
        if(item->getSource() == potion)
        {
            potionUI = item;
            break;
        }
    }


    if(potionUI == nullptr)
        return;

    auto labelIt = potionPriceLabels.find(potion);
    if (labelIt != potionPriceLabels.end()) {
        QGraphicsSimpleTextItem* txt = labelIt->second;

        auto iconIt = priceCoinIcons.find(txt);
        if (iconIt != priceCoinIcons.end()) {
            combatScene->removeItem(iconIt->second);
            delete iconIt->second;
            priceCoinIcons.erase(iconIt);
        }

        combatScene->removeItem(txt);
        potionPriceValues.erase(txt);
        potionPriceTexts.erase(std::remove(potionPriceTexts.begin(), potionPriceTexts.end(), txt), potionPriceTexts.end());
        delete txt;
        potionPriceLabels.erase(labelIt);
    }

    for(auto it = potionImages.begin();
         it != potionImages.end();
         ++it)
    {
        if((*it)->parentItem() == potionUI)
        {
            potionImages.erase(it);
            break;
        }
    }

    potions.erase(
        std::remove(potions.begin(), potions.end(), potionUI),
        potions.end()
        );
    potionprice.erase(potion);

    potionUI->setCanHover(false);
    potionUI->setCanSelect(false);
    potionUI->fadeTo(0, 300, QEasingCurve::OutSine);

    QTimer::singleShot(300, [this, potionUI](){
        combatScene->removeItem(potionUI);
        delete potionUI;
    });


}

void StorePage::potion_right_click(abstractPotion *potion)
{
    auto* info_bar = new CombatInfoBar(potion);

    combatScene->addItem(info_bar->getParent());

    info_bar->Entrance();
}

void StorePage::createPotionPrices()
{
    QFont font;
    font.setFamily(
        setting::game_language == language::English ?
            Fonts::Cascadia :
            Fonts::koodak
        );

    font.setPointSize(22);
    font.setBold(true);

    for (auto* potionParent : potions)
    {
        abstractPotion* source = potionParent->getSource();

        auto itr = potionprice.find(source);

        if (itr == potionprice.end())
            continue;

        int price = itr->second;

        auto* txt =
            combatScene->addSimpleText(QString::number(price), font);

        if (player->get_gold() >= price)
            txt->setBrush(QColor(255,220,80));
        else
            txt->setBrush(QColor(200,40,40));

        QRectF rect = potionParent->sceneBoundingRect();
        attachCoinIcon(txt, rect);

        txt->setZValue(1000);

        potionPriceTexts.push_back(txt);
        potionPriceValues[txt] = price;
        potionPriceLabels[source] = txt;
    }

}

void StorePage::updatePotionPricesColor()
{
    for(auto& item : potionPriceValues)
    {
        QGraphicsSimpleTextItem* txt = item.first;
        int price = item.second;


        if(player->get_gold() >= price)
        {
            txt->setBrush(QColor(255,220,80));
        }
        else
        {
            txt->setBrush(QColor(200,40,40));
        }
    }
}

void StorePage::relic_right_click(abstractRelic* relic)
{
    auto* info_bar = new CombatInfoBar(relic);

    combatScene->addItem(info_bar->getParent());

    info_bar->Entrance();
}

void StorePage::buyCard(abstractCard *card)
{

    auto priceItr = cardprice.find(card);

    if(priceItr == cardprice.end())
        return;

    int price = priceItr->second;

    abstractCardTemplate* cardUI = nullptr;

    for(auto &item : cardSources)
    {
        if(item.second == card)
        {
            cardUI = item.first;
            break;
        }
    }

    if(cardUI == nullptr)
        return;

    if(player->get_gold() < price)
        return;

    player->lose_gold(price);
    soundManager::instance(). playSoundEffect(SoundEffect::cardHover);

    bar->updateBar();
    updateCardPricesColor();
    updatePotionPricesColor();

    player->deck_add(card);


    auto labelIt = cardPriceLabels.find(card);
    if (labelIt != cardPriceLabels.end()) {
        QGraphicsSimpleTextItem* txt = labelIt->second;

        auto iconIt = priceCoinIcons.find(txt);
        if (iconIt != priceCoinIcons.end()) {
            combatScene->removeItem(iconIt->second);
            delete iconIt->second;
            priceCoinIcons.erase(iconIt);
        }

        combatScene->removeItem(txt);
        cardPriceValues.erase(txt);
        cardPriceTexts.erase(std::remove(cardPriceTexts.begin(), cardPriceTexts.end(), txt), cardPriceTexts.end());
        delete txt;
        cardPriceLabels.erase(labelIt);
    }

    CardParent* tileToDelete = cardUI->getParent();
    tileToDelete->setCanHover(false);
    tileToDelete->setCanSelect(false);
    tileToDelete->fadeTo(0, 300, QEasingCurve::OutSine);

    QTimer::singleShot(300, [this, tileToDelete](){
        combatScene->removeItem(tileToDelete);
        delete tileToDelete;
    });


    cards.erase(
        std::remove(cards.begin(), cards.end(), cardUI),
        cards.end()
        );

    cardSources.erase(cardUI);
    cardprice.erase(card);


}

void StorePage::createSelectCard(std::vector<abstractCard*> cards)
{
    auto sc = new selectCard(eve, cards);

    combatScene->addItem(sc->getParent());

    for(auto item : sc->getCards())
    {
        combatScene->addItem(item->getParent());
    }
}

void StorePage::buyRemoveCard()
{
    if(removeUsed) return;
    if(player->get_gold() < remove_card_price) return;

    std::vector<abstractCard*> removable;
    for (auto c : player->get_deck())
        if (c->can_remove_from_deck())
            removable.push_back(c);
    if (removable.empty()) return;

    player->lose_gold(remove_card_price);
    soundManager::instance().playSoundEffect(SoundEffect::cardHover);
    bar->updateBar();
    updateCardPricesColor();
    updatePotionPricesColor();

    removeUsed = true;
    remove_card_price += 25;

    if (removeCardPriceLabel) {
        auto iconIt = priceCoinIcons.find(removeCardPriceLabel);
        if (iconIt != priceCoinIcons.end()) {
            combatScene->removeItem(iconIt->second);
            delete iconIt->second;
            priceCoinIcons.erase(iconIt);
        }

        combatScene->removeItem(removeCardPriceLabel);
        cardPriceValues.erase(removeCardPriceLabel);
        cardPriceTexts.erase(std::remove(cardPriceTexts.begin(), cardPriceTexts.end(), removeCardPriceLabel), cardPriceTexts.end());
        delete removeCardPriceLabel;
        removeCardPriceLabel = nullptr;
    }

    removeCardButton->setCanHover(false);
    removeCardButton->setCanSelect(false);
    removeCardButton->fadeTo(0, 300, QEasingCurve::OutSine);

    CardParent* tileToDelete = removeCardButton;
    removeCardButton = nullptr;
    QTimer::singleShot(300, [tileToDelete](){ delete tileToDelete; });

    connect(
        eve,
        &combatEvent::cardSelected,
        this,
        [this](abstractCard* card)
        {
            if(card == nullptr) return;
            player->deck_remove(card);
        },
        Qt::SingleShotConnection
        );

    emit eve->selectCard(removable);
}

void StorePage::createRemoveButton()
{
    QPointF pos(120 + 3 * 275, 145 + 1 * 395);
    QSizeF  size(200, 300);
    qreal   z = 0;

    removeCardButton = new CardParent(eve, nullptr, size, pos, z);
    removeCardButton->setCanHover(false);
    removeCardButton->setCanSelect(false);
    combatScene->addItem(removeCardButton);

    removeCardBg = new ImageItem(removeCardButton, size, {0, 0});
    removeCardBg->setPixmap(QPixmap(":/image/cards/back/remove_card"));
    removeCardBg->setZValue(z + 1);

    QFont titleFont;
    titleFont.setFamily(setting::game_language == language::English ? Fonts::Cascadia : Fonts::koodak);
    titleFont.setPixelSize(20);
    titleFont.setBold(true);

    removeCardTitle = new TextItem(removeCardButton, {180, 90}, {10, 25});
    removeCardTitle->setFont(titleFont);
    removeCardTitle->setColor(Qt::white);
    removeCardTitle->setAlignment(Qt::AlignCenter);
    removeCardTitle->setText(tr("Card Removal\nService!"));
    removeCardTitle->setZValue(z + 2);

    QFont priceFont;
    priceFont.setFamily(setting::game_language == language::English ? Fonts::Cascadia : Fonts::koodak);
    priceFont.setPointSize(22);
    priceFont.setBold(true);

    removeCardPriceLabel = combatScene->addSimpleText(QString::number(remove_card_price), priceFont);
    if (player->get_gold() >= remove_card_price)
        removeCardPriceLabel->setBrush(QColor(255, 220, 80));
    else
        removeCardPriceLabel->setBrush(QColor(200, 40, 40));

    QRectF rect = removeCardButton->sceneBoundingRect();
    attachCoinIcon(removeCardPriceLabel, rect);

    removeCardPriceLabel->setZValue(1000);

    cardPriceTexts.push_back(removeCardPriceLabel);
    cardPriceValues[removeCardPriceLabel] = remove_card_price;
}

void StorePage::createBackButton()
{
    QFont f;
    f.setBold(true);
    f.setFamily(setting::game_language == language::English ? Fonts::Cascadia : Fonts::koodak);
    f.setPixelSize(24);

    back_btn = new QPushButton();
    back_btn->setFixedSize(135, 60);
    back_btn->setFont(f);
    back_btn->setText(tr("Back"));
    back_btn->setCursor(Qt::PointingHandCursor);
    back_btn->installEventFilter(this);
    back_btn->setStyleSheet(
        "QPushButton{"
        " border-image: url(:/icon/back_icon) 0 0 0 0 stretch stretch;"
        " color: white;"
        " border: none;"
        " background-color: transparent;"
        "}"
        "QPushButton:pressed{"
        "  color: #dddddd;"
        "}"
        );

    back_prxy = new QGraphicsProxyWidget(nullptr);
    back_prxy->setWidget(back_btn);
    back_prxy->setPos(-15, 800);
    back_prxy->setZValue(11500);
    combatScene->addItem(back_prxy);

    connect(back_btn, &QPushButton::clicked, this, [=](){
        emit eve->nextAction();
    });
}

void StorePage::initialSet()
{
    parent = new BaseItem(nullptr, {1600, 900}, {0, 0});

    board = new BaseItem(parent, {1000, 500}, {300, 200});

    combatScene->addItem(parent);

    createCards();
    createCardPrices();
    createPotions();
    createPotionPrices();
    createRemoveButton();
    createBackButton();
}


void StorePage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}


void StorePage::createSelectPotion(std::vector<abstractPotion*> pots) {
    auto sr = new selectPotion(eve, pots);
    combatScene->addItem((sr->getParent()));
}