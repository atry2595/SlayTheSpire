#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include <QHash>

enum class BgMusic {
    act1_general,
    act1_elite,
    act1_boss,
    act1_rest,
    act2_general,
    act2_elite,
    act2_boss,
    act2_rest,
    main
};

enum class SoundEffect {
    attack,         // pass - combat page / attack
    setShield,      // move to combat page / block signal
    cardHover,      // pass - card parent / hover enter
    cawCaw,         // pass - add to cultist & cultist headpiece
    gameLose,
    victory,
    mapHover,
    mapSelect,
    mapRoll,
    menuHover,
    menuSelect,
    smith,
    drinkPotion,    // pass - add to combat page / potion release
    skinSelect
};

class soundManager
{

    soundManager();

    QMediaPlayer* media_player;
    QAudioOutput* audio_output;

    QHash<SoundEffect, QSoundEffect*> effect_table;
    QHash<BgMusic, QUrl> bg_table;

public:

    static soundManager& instance();

    void playBackMusic(BgMusic mus);
    void setBackVolume(qreal value);
    void playSoundEffect(SoundEffect eff);


};

#endif // SOUNDMANAGER_H
