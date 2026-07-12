#include "abstractentityitem.h"

abstractEntityItem::abstractEntityItem(abstractEntity* source, QPointF pos, QSizeF size, qreal zValue)
    :entity_source(source),
        entity_pos(pos),
        entity_size(size),
        z_value(zValue)
{}

abstractEntityItem::~abstractEntityItem() {
    delete entity_image;
    delete entity_name;
    delete intent_icon;
    delete intent_value;
    delete hp_bar;
    delete hp_proxy;
    for (auto item : powers) delete item;
    powers.clear();
    delete entity_parent;
}