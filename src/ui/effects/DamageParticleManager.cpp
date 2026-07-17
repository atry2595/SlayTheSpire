#include "DamageParticleManager.h"

#include <QBrush>
#include <QPen>
#include <QColor>
#include <QRandomGenerator>
#include <cmath>

namespace
{
constexpr int kFrameIntervalMs = 16; // ~60 FPS

constexpr int kMinParticles = 20;
constexpr int kMaxParticles = 25;

constexpr float kMinSpeedPxPerSec = 800.0f;
constexpr float kMaxSpeedPxPerSec = 1100.0f;

constexpr float kMinSize = 8.0f;
constexpr float kMaxSize = 16.0f;

constexpr float kFriction = 0.945f;
constexpr float kFadeStep = 0.016f;
constexpr float kShrinkFactor = 0.98f;

// Converts a px/sec speed into an equivalent px/frame displacement
// for a ~16ms tick.
constexpr float kSecToFrame = kFrameIntervalMs / 1000.0f;

QColor randomDamageColor()
{
    switch (QRandomGenerator::global()->bounded(3))
    {
    case 0:
        return QColor(255, 255, 0); // bright yellow
    case 1:
        return QColor(255, 140, 0); // orange
    default:
        return QColor(220, 20, 0); // red
    }
}

float randomFloat(float minVal, float maxVal)
{
    const double t = QRandomGenerator::global()->generateDouble(); // [0,1)
    return minVal + static_cast<float>(t) * (maxVal - minVal);
}
} // namespace

DamageParticleManager& DamageParticleManager::instance()
{
    static DamageParticleManager manager;
    return manager;
}

void DamageParticleManager::spawn(QGraphicsScene* scene, const QPointF& position)
{
    instance().spawnParticles(scene, position);
}

void DamageParticleManager::spawnParticles(QGraphicsScene* scene, const QPointF& position)
{
    if (!scene)
    {
        return;
    }

    const int count = kMinParticles +
                      QRandomGenerator::global()->bounded(kMaxParticles - kMinParticles + 1);

    particles_.reserve(particles_.size() + static_cast<size_t>(count));

    for (int i = 0; i < count; ++i)
    {
        const float angleDeg = randomFloat(0.0f, 360.0f);
        const float angleRad = angleDeg * static_cast<float>(M_PI) / 180.0f;
        const float speed = randomFloat(kMinSpeedPxPerSec, kMaxSpeedPxPerSec);

        const QPointF velocity(std::cos(angleRad) * speed * kSecToFrame,
                               std::sin(angleRad) * speed * kSecToFrame);

        const float size = randomFloat(kMinSize, kMaxSize);
        const QColor color = randomDamageColor();

        auto* ellipse = new QGraphicsEllipseItem(-size / 2.0, -size / 2.0, size, size);
        ellipse->setBrush(QBrush(color));
        ellipse->setPen(Qt::NoPen);
        ellipse->setPos(position);
        ellipse->setOpacity(1.0);
        ellipse->setZValue(9999 + 1); // draw above other scene items
        scene->addItem(ellipse);

        auto particle = std::make_unique<Particle>();
        particle->item = ellipse;
        particle->velocity = velocity;
        particle->opacity = 1.0f;
        particle->scale = 1.0f;
        particle->lifetime = 0;

        particles_.push_back(std::move(particle));
    }

    startTimerIfNeeded();
}

void DamageParticleManager::startTimerIfNeeded()
{
    if (timer_)
    {
        return;
    }

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &DamageParticleManager::tick);
    timer_->start(kFrameIntervalMs);
}

void DamageParticleManager::stopTimerIfIdle()
{
    if (particles_.empty() && timer_)
    {
        timer_->stop();
        timer_->deleteLater();
        timer_ = nullptr;
    }
}

void DamageParticleManager::tick()
{
    for (auto it = particles_.begin(); it != particles_.end();)
    {
        Particle* p = it->get();

        // Physics update.
        p->velocity *= kFriction;
        p->item->setPos(p->item->pos() + p->velocity);

        // Fade and shrink.
        p->opacity -= kFadeStep;
        p->scale *= kShrinkFactor;
        ++p->lifetime;

        if (p->opacity <= 0.0f)
        {
            if (QGraphicsScene* scene = p->item->scene())
            {
                scene->removeItem(p->item);
            }
            delete p->item;
            p->item = nullptr;

            it = particles_.erase(it); // unique_ptr destructor frees the Particle
        }
        else
        {
            p->item->setOpacity(p->opacity);
            p->item->setScale(p->scale);
            ++it;
        }
    }

    stopTimerIfIdle();
}
