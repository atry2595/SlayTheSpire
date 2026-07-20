#ifndef ABSTRACTENTITYITEM_H
#define ABSTRACTENTITYITEM_H

#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "ui/entities/entityparent.h"
#include "entity/abstractentity.h"
#include "categories/enemies.h"
#include "ui/entities/simplehpbar.h"
#include "ui/entities/getPowerIcon.h"
#include "items/powers/abstractpower.h"
#include "core/setting.h"
#include "powerparent.h"
#include <QObject>
#include <QGraphicsProxyWidget>

class abstractEntityItem : public QObject
{
    Q_OBJECT

protected:
    abstractEntity* entity_source = nullptr;

    QPointF entity_pos;
    QSizeF entity_size;


    qreal z_value;

    EntityParent* entity_parent = nullptr;
    ImageItem* entity_image = nullptr;
    TextItem* entity_name = nullptr;
    TextItem* intent = nullptr;
    SimpleHpBar* hp_bar = nullptr;
    QGraphicsProxyWidget* hp_proxy = nullptr;
    std::vector<PowerParent*> powers_prnt = {};
    std::vector<TextItem*> powers = {};




public:
    abstractEntityItem(abstractEntity* source, QPointF pos, QSizeF size, qreal zValue);
    ~abstractEntityItem();

    // Entity pos
    void setEntitypos(QPointF value) { entity_pos = value; }
    void setEntitypos(qreal w, qreal h) { entity_pos = QPointF(w, h); }
    QPointF getEntitypos() const { return entity_pos; }

    // Entity Size
    void setEntitySize(QSizeF value) { entity_size = value; }
    void setEntitySize(qreal w, qreal h) { entity_size = QSizeF(w, h); }
    QSizeF getEntitySize() const { return entity_size; }

    EntityParent* getParent() { return entity_parent; }
    abstractEntity* getSource() { return entity_source; }
    ImageItem* getImage() { return entity_image; }

    void setHighlight(bool b);
    void setHighlightColor(QColor clr = Qt::yellow);

    void dieAnim();
    void escapeAnim();
};

#endif // ABSTRACTENTITYITEM_H
