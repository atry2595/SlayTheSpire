#include "treasurepage.h"
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

TreasurePage::TreasurePage(QWidget *parent, ChestType type, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , type(type)
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
    ImageItem* bg = new ImageItem(nullptr, {1632, 918}, {-16, -9});
    bg->setPixmap(mng.getBackroundImage());
    bg->setZValue(0);
    combatScene->addItem(bg);

    bar = new CombatTopBar(eve, player, true);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());
    //----------------------------------------------------
    veilcladLines = {
        tr("You're still standing, Ironclad. Good. Kneeling here means only one thing. Open this chest—inside is a wound-wrap. Every time your vision darkens, unravel it."),
        tr("You are of the burned and the risen. This chest holds a cold ember from a fire that never died. Take it. When the path is lost, clench your fist around it—it will burn and show the way."),
        tr("Every time you reach this place, something is missing. This chest holds a vial of silence. Don't drink it. Shatter it. The silent explosion will scar the spells you cannot see."),
        tr("I dreamt of you last night. You were made of rust and screaming. This chest holds a small bellows. When your inner fire dims to embers, pump it once against your chest. It won't bring back the flames, but it'll keep the smoke moving."),
        tr("I've been here so long I've forgotten my name. But I remember this: the Spire has a heartbeat. This chest holds a tuning fork. Strike it against your armor. If the hum deepens, you're close to the heart. If it goes flat, turn back."),
        tr("Don't say goodbye. We are in a loop. Take this silent bell from the chest. When you return and don't see me, shake it. I will appear in the sound you cannot hear, and show you the new way."),
        tr("Your wounds run deeper than you think. This isn't salve—it's liquid tattoo ink, and it's in this chest. Mark your arm. The pattern is the map of the next floor, waiting for your return."),
        tr("I can see the fire inside you. There is no water here, only blood-steam. Take this seal from the chest. Next time you return, press it to an open wound and watch what armor grows from pain."),
        tr("Don't rush. The faster you run, the later you return. This chest holds a shard of cold metal, the coolness of patience for inflamed days. Take it and pass, but swear you'll come back."),
        tr("Your hands shake. Don't hide it. Shaking hands grip harder when the blade meets bone. Open this chest. Inside is resin from a weeping tree. Rub it on your palms. It'll burn, then it'll hold."),
        tr("There's a crack in the ceiling above us. I've watched it grow for years. This chest holds a splinter from that crack. Keep it. When the Spire's walls shift, the splinter will tremble first. You'll feel the change before it kills you."),
        tr("You ever wonder why the torches stay lit? They feed on ambition. Open the chest. There's a snuffer inside. Use it on one torch before the next fight. The darkness you make is yours, not the Spire's."),
        tr("One came before you, and only half of him returned. The other half is here. This chest holds a finger-bone of his. Take it. Perhaps you'll find the rest of his body in the depths and claim the reward."),
        tr("I hear your footsteps. Every step is a demand. Take this serrated coin from the chest. Throw it into the Wishing Well—not for a wish, but to buy the silence of the monsters beneath it."),
        tr("Your gaze is fixed on the horizon, but the Spire's floor is veined. Take this dull blade from the chest. Wherever the ground pulses, carve into it. Hidden paths only open for those who wound."),
        tr("You return. The Spire hates those who return. This chest holds a thread from a burial shroud. Sew it into your cloak. The Spire will mistake you for something already dead and look the other way."),
        tr("You carry too much guilt. Guilt is weight, and weight slows the sword. Take this hollow stone from the chest. Whisper your regrets into it, then seal it with wax. Leave it here. I'll keep it buried."),
        tr("The enemies ahead don't bleed like you do. They leak memories. This chest holds a vial of your own sweat from the last time you passed. Drink it. It'll remind your body what it felt like to survive, and survival is a pattern the flesh remembers."),
        tr("Enemies aren't just the ones you see. Take this rope from the chest, woven from spirit-hair. When you feel your breath being stolen, tie it around your throat. It gives back the truth."),
        tr("The floor you walk on was poured with betrayal. Literally. Take this chisel from the chest. Scratch the ground where you stand. If the scratch weeps, don't fight there. Move ten paces left and make your stand."),
        tr("You're not the first Ironclad to pass through, but you're the first to listen. This chest holds a braid of hair from a soldier who didn't listen. She's dead. Her hair remembers her mistakes. Wear it, and let it whisper warnings."),
        tr("Breathe. No, really breathe. The air here has spores that make you forget why you're climbing. This chest holds a pouch of dried herbs from outside the Spire. Crush one and inhale when your purpose starts to blur."),
        tr("You know your sword well, but not your shadow. This chest holds a broken mirror. Look into it once, then shatter it. The shards will guide your next strikes."),
        tr("They'll try to separate you from your shadow. Don't let them. This chest holds two iron nails. Hammer one into your shadow's hand and one into yours. You'll move slower, but you'll never move alone."),
    };

    oathcladLines = {
        tr("Chest. Open it. Inside is a whetstone soaked in old blood. It's mine. Sharpen your blade with it. Every swing will carry a piece of my oath, and my oath is simple: keep standing, or I'll find your corpse and stand it up myself."),
        tr("You look half-dead already. Good. The almost-dead fight dirtiest. Open the chest. There's a rusted pauldron inside. It's ugly and heavy. Wear it. It'll take the hit that would've killed the last bit of hope in you."),
        tr("You think you're the first to burn? This chest holds a lump of coal from a warrior who burned brighter and still fell. Take it. Swallow your pride, not the coal. When you're truly finished, crush it in your hand and remember: even ash can blind an enemy."),
        tr("Stop staring at the tower. Look at me. Look at the chest. Take the jagged knife inside. It's not for your enemy's heart. It's for yours. When the demon's fire in your blood goes quiet, cut yourself open and let it breathe again."),
        tr("I've seen your kind before. You break beautifully. Take this iron splint from the chest. Bind it to your sword-arm before the next fight. It won't make you faster. It'll make sure your bones don't shatter before your will does."),
        tr("Listen closely, because I'll only say this once. The chest contains a single manacle. Lock it onto your wrist, not your ankle. When the floor tries to drag you down, that manacle will catch on something invisible. What it catches is your own stubbornness."),
        tr("Ironclad. Kneel or don't, I don't care. This chest is open. Inside is a broken chain. Take it. Wear it. Let it remind you that you belong to no master except the fire you still owe a debt to."),
        tr("You want a blessing? Blessings are for priests. I have a curse and a hammer. The chest holds both. The curse is in a glass bead. Swallow it. The hammer is for when the curse starts talking too loud. Hit yourself in the sternum. It'll shut up."),
        tr("You climbed all this way with a dead clan on your back. Put them down. Take the urns from this chest. Two of them. One holds their ashes. The other holds the ashes of the thing that killed them. Smash them both before your next fight. Let them mix. Let them fight again. You just watch."),
        tr("You're not a hero. Heroes sing songs. You just endure. This chest holds a mouthful of salt. Take it. Before the next battle, pour it on your tongue. The thirst will drive you mad, and madness is a weapon when swords feel too light."),
        tr("You're bleeding. Don't apologize. Bleeding means you're still liquid enough to move. There's a corked gourd in the chest. Don't drink it. Pour it on the floor where you stand. Next time you die, this spot will pull you back. Once."),
        tr("Final words? You get none. The Spire doesn't care about last words. Take this jawbone from the chest. It's my jawbone. If you die before the top, throw it as far as you can. I want something of mine to see the summit, even if you don't."),
        tr("Again? You're either brave or stupid. Probably both. The chest. Open it. Inside is a strip of leather cut from my own back. Chew it when the pain gets loud. It tastes like failure. You'll hate it. You'll fight harder."),
        tr("I've watched a hundred like you climb. Ninety-nine are bones now. This chest holds the kneecap of the one who made it furthest. Boil it. Drink the broth. It won't give you strength—it'll give you the one thing he had: refusal."),
        tr("You want to know what's above? More of the same, but taller and meaner. This chest holds a severed finger wearing a ring. The ring is cursed. Put it on. Every time an enemy lands a blow, the curse tightens—but so does your grip on your weapon."),
        tr("Your armor is cracked. I can hear it wheezing. Take this iron rivet from the chest. It's not for the armor. It's for your collarbone. Hammer it in. The pain will anchor you when the berserk tries to throw you off the edge."),
        tr("You think rage is a furnace. It's not. It's a leak. It spills everywhere and leaves you empty. This chest holds a plug. It's ugly and made of lead. Shove it into the wound the demon left. Your rage stays in. Their faces come off."),
        tr("Don't look at me like that. I'm not your father. I'm the one who buried fathers. This chest holds a shovel's blade. It's small. Dig with it before you rest. Bury your doubts. If you don't, they'll crawl into your mouth while you sleep."),
        tr("You'll die again. Accept it. This chest holds a small hourglass. When you fall, it shatters. The sand doesn't measure time—it measures how long you have to get back up before the Spire forgets you. So don't stay down. The sand runs fast."),
        tr("You want help? Help is for the weak. This is a transaction. The chest holds a blackened torch. It gives no light, only smoke. Light it when you're surrounded. The smoke will choke them. It'll choke you too, but your lungs are already scarred. You'll outlast them."),
        tr("You're slow. Don't deny it. Slowness kills. This chest holds a pair of spurs. Strap them to your heels, but don't spur a horse. Spur yourself. Every time you hesitate, kick your own ankles bloody. The pain will speed you up."),
        tr("You're shaking your head. You think you're ready. You're not. Open the chest. There's a jar of tar inside. Smear it on your eyes before the boss room. You'll fight blind. But so will every invisible thing waiting to ambush you."),
        tr("The demon in your blood is a coward. It only speaks when you're winning. This chest holds a leash made of sinew. Tie it to your wrist. When the demon goes quiet, yank the leash. Remind it who bled first."),
        tr("There's a door up ahead that only opens when you scream the right name. I don't know the name. But this chest holds a tongue preserved in salt. It's from someone who did know. Eat it. Maybe your voice will remember what your mind forgot."),
    };

    connect(eve, &combatEvent::settingOpen, this, &TreasurePage::open_setting);

    initialSet();
    showHost();
}

TreasurePage::~TreasurePage() {

    if (bar) {
        delete bar;
        bar = nullptr;
    }
    if (relic_bar) {
        delete relic_bar;
        relic_bar = nullptr;
    }

    if (black_screen) delete black_screen;

    // Clean up combat view and scene
    if (combatScene) {
        // QGraphicsScene will clean up its items when deleted
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

void TreasurePage::Delete() {
    black_screen = new BaseItem(nullptr, {1700, 1000}, {-50, -50});
    black_screen->setBackColor(Qt::black);
    black_screen->setOpacity(0);
    black_screen->setZValue(200000);
    combatScene->addItem(black_screen);
    black_screen->fadeTo(1, 500);

    QTimer::singleShot(1000, [=](){
        this->deleteLater();
    });
}


void TreasurePage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

void TreasurePage::createCollectReward(combatReward* reward){
    QTimer::singleShot(1000, [=]() {
        auto cr = new collectReward(eve, reward, player);
        combatScene->addItem(cr->getParent());
    });
}


void TreasurePage::showHost() {

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent; color: yellow;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;


    int try_count= 0;
    if (setting::current_player){
        try_count = setting::current_player->getStats().getTimesPlayed();
    }

    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 0, 180)));
    parent->setZValue(13100);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setStyleSheet(blank_css);
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);
    connect(overlay, &QPushButton::clicked, this, [=](){
        parent->fadeTo(0, 500);
        getRew();
    });

    dialog_parent = new BaseItem(parent, {1100, 450}, {500, 450});
    dialog_parent->setZValue(11);
    host_dilogbox = new ImageItem(dialog_parent, {1100, 350}, {0, 100});
    host_name = new TextItem(dialog_parent, {600, 100}, {50, 0});
    QFont hdf;
    hdf.setFamily(Fonts::forte);
    hdf.setPixelSize(65);
    host_name->setFont(hdf);
    host_name->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    host_mess = new TextItem(dialog_parent, {890, 315}, {143, 120});
    QFont hmf;
    hmf.setFamily(Fonts::Cascadia);
    hmf.setPixelSize(26);
    host_mess->setFont(hmf);
    host_mess->setColor(Qt::black);

    if (type == ChestType::boss) {
        qreal w = 564;
        qreal h = 484;
        qreal x = 0;
        qreal y = 900 - h;

        host_image = new ImageItem(parent, {w, h}, {x, y});
        host_image->setPixmap(imageManager::instance().getEntityImage(entityID::oathclad));
        host_image->setZValue(10);
        host_dilogbox->setPixmap(imageManager::instance().getDialogImage(ChestType::boss));
        host_name->setText(tr("Oathclad"));
        host_name->setColor(QColor::fromRgb(243, 7, 27));
        host_mess->setText(oathcladLines[try_count % oathcladLines.size()]);

    }

    else if (type == ChestType::regular) {
        qreal w = 534;
        qreal h = 512;
        qreal x = 0;
        qreal y = 900 - h;

        host_image = new ImageItem(parent, {w, h}, {x, y});
        host_image->setPixmap(imageManager::instance().getEntityImage(entityID::veilclad));
        host_image->setZValue(10);
        host_dilogbox->setPixmap(imageManager::instance().getDialogImage(ChestType::regular));
        host_name->setText(tr("Veilclad"));
        host_name->setColor(QColor::fromRgb(150, 120, 220));
        host_mess->setText(veilcladLines[try_count % veilcladLines.size()]);
    }

    parent->setOpacity(0);
    combatScene->addItem(parent);
    QTimer::singleShot(1000, [=](){
        parent->fadeTo(1, 500);
    });

}

void TreasurePage::initialSet() {
    if (type == ChestType::boss) {
        qreal w = 250;
        qreal h = 200;
        qreal x = (1600 - w) / 2;
        qreal y = 900 / 2;

        chest_image = new ImageItem(nullptr, {w, h}, {x, y});
        chest_image->setZValue(5);
    }

    else if (type == ChestType::regular) {
        qreal w = 220;
        qreal h = 200;
        qreal x = (1600 - w) / 2;
        qreal y = 900 / 2;

        chest_image = new ImageItem(nullptr, {w, h}, {x, y});
        chest_image->setZValue(5);
    }

    if (chest_image) {
        chest_image->setPixmap(imageManager::instance().getChestImage(type));
        combatScene->addItem(chest_image);
    }
}


void TreasurePage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}

void TreasurePage::getRew() {
    auto& rng = RNG::instance();
    combatReward* rew = new combatReward();

    if (type == ChestType::regular) {
        if (rng.chance(0.5)){
            rew->add_gold(rng.randint(23, 82));
        }

        std::vector<relicID> rlcs;
        std::vector<double> wei;
        for (auto item : common_relic){
            if (player->get_spec_relic(item)) continue;
            rlcs.push_back(item);
            wei.push_back(6);
        }
        for (auto item : uncommon_relic) {
            if (player->get_spec_relic(item)) continue;
            rlcs.push_back(item);
            wei.push_back(3);
        }
        for (auto item : rare_relic) {
            if (player->get_spec_relic(item)) continue;
            rlcs.push_back(item);
            wei.push_back(1);
        }

        auto selected2 = rng.weighted_sample(rlcs, wei, 1);

        for (auto item : selected2){
            abstractRelic* created_relic = RelicFactory::createRelic(item, player);
            rew->add_relic(created_relic);
        }
        createCollectReward(rew);
    }

    else if (type == ChestType::boss) {

        std::vector<relicID> rlcs = boss_relic;

        auto selected2 = rng.sample(rlcs, 3);

        std::vector<abstractRelic*> created;
        for (auto item : selected2){
            created.push_back(RelicFactory::createRelic(item, player));
        }
        auto sr = new selectRelic(eve, created);
        combatScene->addItem((sr->getParent()));
        connect(eve, &combatEvent::relicSelected, this, [=](abstractRelic* rlc){
            rew->add_relic(rlc);
            createCollectReward(rew);
        });
    }
}
