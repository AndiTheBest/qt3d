/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3DEXTRAS_QMORPHINGANIMATION_H
#define QT3DEXTRAS_QMORPHINGANIMATION_H

#include <Qt3DRender/qgeometryrenderer.h>

#include <Qt3DExtras/qabstractanimation.h>
#include <Qt3DExtras/qmorphtarget.h>
#include <Qt3DExtras/qt3dextras_global.h>

#include <QtCore/qeasingcurve.h>

QT_BEGIN_NAMESPACE

namespace Qt3DExtras {

class QMorphingAnimationPrivate;

class QT3DEXTRASSHARED_EXPORT QMorphingAnimation : public QAbstractAnimation
{
    Q_OBJECT
    Q_PROPERTY(QVector<float> targetPositions READ targetPositions WRITE setTargetPositions NOTIFY targetPositionsChanged)
    Q_PROPERTY(float interpolator READ interpolator NOTIFY interpolatorChanged)
    Q_PROPERTY(Qt3DRender::QGeometryRenderer *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QString targetName READ targetName WRITE setTargetName NOTIFY targetNameChanged)
    Q_PROPERTY(QMorphingAnimation::Method method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(QEasingCurve::Type easing READ easing WRITE setEasing NOTIFY easingChanged)

public:
    enum Method
    {
        Normalized,
        Relative
    };
    Q_ENUM(Method)

    explicit QMorphingAnimation(QObject *parent = nullptr);

    QVector<float> targetPositions() const;
    float interpolator() const;
    Qt3DRender::QGeometryRenderer *target() const;
    QString targetName() const;
    QMorphingAnimation::Method method() const;
    QEasingCurve::Type easing() const;

    void setMorphTargets(const QVector<Qt3DExtras::QMorphTarget *> &targets);
    void addMorphTarget(Qt3DExtras::QMorphTarget *target);
    void removeMorphTarget(Qt3DExtras::QMorphTarget *target);

    void setWeights(int positionIndex, const QVector<float> &weights);
    QVector<float> getWeights(int positionIndex);

    QVector<Qt3DExtras::QMorphTarget *> morphTargetList();

public Q_SLOTS:
    void setTargetPositions(const QVector<float> &targetPositions);
    void setTarget(Qt3DRender::QGeometryRenderer *target);
    void setTargetName(const QString name);
    void setMethod(QMorphingAnimation::Method method);
    void setEasing(QEasingCurve::Type easing);

Q_SIGNALS:
    void targetPositionsChanged(const QVector<float> &targetPositions);
    void interpolatorChanged(float interpolator);
    void targetChanged(Qt3DRender::QGeometryRenderer *target);
    void targetNameChanged(const QString &name);
    void methodChanged(QMorphingAnimation::Method method);
    void easingChanged(QEasingCurve::Type easing);

private:

    void updateAnimation(float position);

    Q_DECLARE_PRIVATE(QMorphingAnimation)
};

} // Qt3DExtras

QT_END_NAMESPACE

#endif // QT3DEXTRAS_QMORPHINGANIMATION_H
