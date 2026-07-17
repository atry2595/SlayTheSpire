#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QTimer>
#include <memory>
#include <vector>

// Reusable 2D particle effect manager.
// Currently exposes DamageParticleManager::spawn(), but the internal
// architecture (Particle struct, single shared QTimer, manual update loop)
// is intentionally generic so it can be extended/duplicated for other
// effects (Heal, Poison, Burn, etc.) without redesign.
class DamageParticleManager : public QObject
{
    Q_OBJECT

public:
    // Spawns ~10-15 damage particles at 'position' inside 'scene'.
    // This is the ONLY public entry point of the system.
    static void spawn(QGraphicsScene* scene, const QPointF& position);

private:
    DamageParticleManager() = default;
    ~DamageParticleManager() override = default;

    DamageParticleManager(const DamageParticleManager&) = delete;
    DamageParticleManager& operator=(const DamageParticleManager&) = delete;

    static DamageParticleManager& instance();

    struct Particle
    {
        QGraphicsEllipseItem* item = nullptr; // owned raw pointer, manually deleted
        QPointF velocity;
        float opacity = 1.0f;
        float scale = 1.0f;
        int lifetime = 0;
    };

    void spawnParticles(QGraphicsScene* scene, const QPointF& position);
    void tick();
    void startTimerIfNeeded();
    void stopTimerIfIdle();

    std::vector<std::unique_ptr<Particle>> particles_;
    QTimer* timer_ = nullptr; // exactly one timer for the whole manager
};
