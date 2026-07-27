#ifndef ENTITYCORNERSFRAME_H
#define ENTITYCORNERSFRAME_H

#include "abstracteffect.h"
#include "ui/imageitem.h"

class entityCornersFrame : public abstractEffect
{

private:
    BaseItem* parent;
    std::vector<ImageItem*> corners = {};
    bool b;

public:
    entityCornersFrame(QPointF pos, QSizeF size);
    ~entityCornersFrame();

    BaseItem* getParent() { return parent; }
    bool getVisisble() { return b; }

    void EntranceEffect() override;
    void ExitEffect() override;

};

#endif // ENTITYCORNERSFRAME_H
