#include "relicbar.h"
#include "ui/relicbar/getRelicImage.h"

RelicBar::RelicBar(std::vector<abstractRelic*> rlcs) {

    parent = new BaseItem(nullptr, {1600, 50}, {0, 75});
    parent->setZValue(10001);

    for (int i = 0; i < rlcs.size(); i++) {
        ImageItem* img = new ImageItem(parent, {50, 50}, QPointF(65 * i + 15, 0));
        img->setPixmap(getRelicImage(rlcs[i]->get_id()));
        rlcs_image.push_back(img);
    }
}
