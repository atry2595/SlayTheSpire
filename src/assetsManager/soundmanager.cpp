#include "soundmanager.h"
#include "core/setting.h"
#include <QDebug>

soundManager& soundManager::instance() {
    static soundManager mng;
    return mng;
}

soundManager::soundManager() {
    bg_table[BgMusic::act1_general] = QUrl("qrc:/sound/music/music1_normal.ogg");
    bg_table[BgMusic::act1_elite] = QUrl("qrc:/sound/music/music1_dark.ogg");
    bg_table[BgMusic::act1_boss] = QUrl("qrc:/sound/music/music1_epic.ogg");
    bg_table[BgMusic::act1_rest] = QUrl("qrc:/sound/music/music1_rest.ogg");
    bg_table[BgMusic::act2_general] = QUrl("qrc:/sound/music/music2_normal.ogg");
    bg_table[BgMusic::act2_elite] = QUrl("qrc:/sound/music/music2_dark.ogg");
    bg_table[BgMusic::act2_boss] = QUrl("qrc:/sound/music/music2_epic.ogg");
    bg_table[BgMusic::act2_rest] = QUrl("qrc:/sound/music/music2_rest.ogg");
    bg_table[BgMusic::main] = QUrl("qrc:/sound/music/music0.ogg");

    QSoundEffect* attck = new QSoundEffect();
    attck->setSource(QUrl("qrc:/sound/effect/damage.wav"));
    effect_table[SoundEffect::attack] = attck;

    QSoundEffect* sh = new QSoundEffect();
    sh->setSource(QUrl("qrc:/sound/effect/blocked_attack.wav"));
    effect_table[SoundEffect::setShield] = sh;

    QSoundEffect* ch = new QSoundEffect();
    ch->setSource(QUrl("qrc:/sound/effect/card_hover.wav"));
    effect_table[SoundEffect::cardHover] = ch;

    QSoundEffect* cc = new QSoundEffect();
    cc->setSource(QUrl("qrc:/sound/effect/crow.wav"));
    effect_table[SoundEffect::cawCaw] = cc;

    QSoundEffect* gl = new QSoundEffect();
    gl->setSource(QUrl("qrc:/sound/effect/game_lose.wav"));
    effect_table[SoundEffect::gameLose] = gl;

    QSoundEffect* vv = new QSoundEffect();
    vv->setSource(QUrl("qrc:/sound/effect/game_win.wav"));
    effect_table[SoundEffect::victory] = vv;

    QSoundEffect* mh = new QSoundEffect();
    mh->setSource(QUrl("qrc:/sound/effect/map_hover.wav"));
    effect_table[SoundEffect::mapHover] = mh;

    QSoundEffect* ms = new QSoundEffect();
    ms->setSource(QUrl("qrc:/sound/effect/map_hover.wav"));
    effect_table[SoundEffect::mapSelect] = ms;

    QSoundEffect* mr = new QSoundEffect();
    mr->setSource(QUrl("qrc:/sound/effect/rolling_map.wav"));
    effect_table[SoundEffect::mapRoll] = mr;

    QSoundEffect* nh = new QSoundEffect();
    nh->setSource(QUrl("qrc:/sound/effect/menu_hover.wav"));
    effect_table[SoundEffect::menuHover] = nh;

    QSoundEffect* ns = new QSoundEffect();
    ns->setSource(QUrl("qrc:/sound/effect/menu_select.wav"));
    effect_table[SoundEffect::menuSelect] = ns;

    QSoundEffect* sm = new QSoundEffect();
    sm->setSource(QUrl("qrc:/sound/effect/smith.wav"));
    effect_table[SoundEffect::smith] = sm;

    QSoundEffect* dp = new QSoundEffect();
    dp->setSource(QUrl("qrc:/sound/effect/drink_potion.wav"));
    effect_table[SoundEffect::drinkPotion] = dp;

    QSoundEffect* ss = new QSoundEffect();
    ss->setSource(QUrl("qrc:/sound/effect/select.wav"));
    effect_table[SoundEffect::skinSelect] = ss;

    media_player = new QMediaPlayer();
    audio_output = new QAudioOutput();
    media_player->setAudioOutput(audio_output);
    media_player->setLoops(QMediaPlayer::Infinite);
}

void soundManager::playBackMusic(BgMusic mus) {
    //can add fade in/out with QPropertyAnim
    media_player->stop();
    media_player->setSource(bg_table[mus]);
    audio_output->setVolume(setting::bg_volume);
    media_player->play();
}

void soundManager::playSoundEffect(SoundEffect eff) {
    effect_table[eff]->setVolume(setting::sfx_volume);
    effect_table[eff]->play();
}


void soundManager::setBackVolume(qreal volume) {
    audio_output->setVolume(volume);
}