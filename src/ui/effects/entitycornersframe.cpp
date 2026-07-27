#include "entitycornersframe.h"
#include "assetsManager/imagemanager.h"
#include <QParallelAnimationGroup>

entityCornersFrame::entityCornersFrame(QPointF pos, QSizeF size)
{
    parent = new BaseItem(nullptr, size, pos);
    parent->setZValue(9999);
    parent->setOpacity(0);

    ImageItem* c1 = new ImageItem(parent, {30, 30}, {0, 0});
    c1->setPixmap(imageManager::instance().getIcon("corner"));

    ImageItem* c2 = new ImageItem(parent, {30, 30}, {0 + size.width(), 0});
    c2->setPixmap(imageManager::instance().getIcon("corner"));
    c2->setRotation(90);

    ImageItem* c3 = new ImageItem(parent, {30, 30}, {0 + size.width(), 0 + size.height()});
    c3->setPixmap(imageManager::instance().getIcon("corner"));
    c3->setRotation(180);

    ImageItem* c4 = new ImageItem(parent, {30, 30}, {0, 0 + size.height()});
    c4->setPixmap(imageManager::instance().getIcon("corner"));
    c4->setRotation(270);

    corners = {c1, c2, c3, c4};

    b = false;
}

entityCornersFrame::~entityCornersFrame() {
    for (auto item : corners) {
        delete item;
    }
    corners.clear();
}

void entityCornersFrame::EntranceEffect() {

    parent->fadeTo(1);
    b = true;

}

void entityCornersFrame::ExitEffect() {

    parent->fadeTo(0);
    b = false;

}