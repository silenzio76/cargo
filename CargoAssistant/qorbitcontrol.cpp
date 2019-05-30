#include "qorbitcontrol.h"

#include <Qt3DCore/qtransform.h>

QT_BEGIN_NAMESPACE

QOrbitControl::QOrbitControl(QObject *parent)
    : QObject(parent)
    , m_target(nullptr)
    , m_matrix()
    , m_radius(1.0f)
    , m_angle(0.0f)
    , m_rotationOrigin()
{
}

void QOrbitControl::setTarget(Qt3DCore::QTransform *target)
{
    if (m_target != target) {
        m_target = target;
        emit targetChanged();
    }
}

Qt3DCore::QTransform *QOrbitControl::target() const
{
    return m_target;
}

void QOrbitControl::setRadius(float radius)
{
    if (!qFuzzyCompare(radius, m_radius)) {
        m_radius = radius;
        updateAxisY(radius);
        emit radiusChanged();
    }
}

float QOrbitControl::radius() const
{
    return m_radius;
}

void QOrbitControl::setAngle(float angle)
{
    if (!qFuzzyCompare(angle, m_angle)) {
        m_angle = angle;
        updateAxisX(angle);
        emit angleChanged();
    }
}

float QOrbitControl::angle() const
{
    return m_angle;
}

void QOrbitControl::setRotationOrigin(QVector3D orRot)
{
    m_rotationOrigin = orRot;
}

QVector3D QOrbitControl::rotationOrigin() const
{
    return m_rotationOrigin;
}


void QOrbitControl::updateAxisY(float angle)
{
    //take the existing matrix to not lose any previous transformations
    m_matrix = m_target->matrix();
    // Move to the origin point of the rotation, _rotationOrigin would be a member variable
    m_matrix.translate(m_rotationOrigin);
    // rotate (around the y axis)
    m_matrix.rotate(angle, QVector3D(0.0f, 1.0f, 0.0f));
    // translate back
    m_matrix.translate(-m_rotationOrigin);
    m_target->setMatrix(m_matrix);
}

void QOrbitControl::updateAxisX(float angle)
{
    //take the existing matrix to not lose any previous transformations
    m_matrix = m_target->matrix();
    // Move to the origin point of the rotation, _rotationOrigin would be a member variable
    m_matrix.translate(m_rotationOrigin);
    // rotate (around the x axis)
    m_matrix.rotate(angle, QVector3D(1.0f, 0.0f, 0.0f));
    // translate back
    m_matrix.translate(-m_rotationOrigin);
    m_target->setMatrix(m_matrix);
}

QT_END_NAMESPACE

