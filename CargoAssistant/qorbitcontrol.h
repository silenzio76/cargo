#ifndef QORBITCONTROL_H
#define QORBITCONTROL_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>

QT_BEGIN_NAMESPACE

namespace Qt3DCore {
class QTransform;
}

class QOrbitControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(float radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
    Q_PROPERTY(QVector3D rotationOrigin READ rotationOrigin WRITE setRotationOrigin NOTIFY rotationChanged)

public:
    QOrbitControl(QObject *parent = nullptr);

    void setTarget(Qt3DCore::QTransform *target);
    Qt3DCore::QTransform *target() const;

    void setRadius(float radius);
    float radius() const;

    void setAngle(float angle);
    float angle() const;
    void setRotationOrigin(QVector3D orRot);
    QVector3D rotationOrigin() const;

signals:
    void targetChanged();
    void radiusChanged();
    void angleChanged();
    void rotationChanged();

protected:
    void updateAxisY(float angle);
    void updateAxisX(float angle);

private:
    Qt3DCore::QTransform *m_target;
    QMatrix4x4 m_matrix;
    float m_radius;
    float m_angle;
    QVector3D m_rotationOrigin;
};

QT_END_NAMESPACE

#endif // QORBITCONTROL_H
