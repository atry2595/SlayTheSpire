#ifndef ABSTRACTEFFECT_H
#define ABSTRACTEFFECT_H

#include <QObject>

class abstractEffect : public QObject
{
    Q_OBJECT
public:
    abstractEffect() {}

    virtual void EntranceEffect() = 0;
    virtual void ExitEffect() = 0;
    virtual void EmphasisEffect() {}
    virtual void MotionEffect() {}
};

#endif // ABSTRACTEFFECT_H
