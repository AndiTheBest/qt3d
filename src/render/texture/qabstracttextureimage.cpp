/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qabstracttextureimage.h"
#include "qabstracttextureimage_p.h"
#include <Qt3DCore/qnodepropertychange.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DRender {


/*!
    \qmltype AbstractTextureImage
    \instantiates Qt3DRender::QAbstractTextureImage
    \inherits Node
    \inqmlmodule Qt3D.Render
    \qmlabstract
    \since 5.5
    \brief Encapsulates the necessary information to create an OpenGL texture image.
*/

/*!
    \class Qt3DRender::QAbstractTextureImage
    \inmodule Qt3DRender
    \since 5.5
    \brief Encapsulates the necessary information to create an OpenGL texture image.

    QAbstractTextureImage should be used as the means of providing image data to a
    QAbstractTexture. It contains the necessary information: mipmap
    level, layer, cube face load at the proper place data into an OpenGL texture.

    The actual data is provided through a QTextureImageDataGenerator that will be
    executed by Aspect jobs in the backend. QAbstractTextureImage should be
    subclassed to provide a functor and eventual additional properties needed by
    the functor to load actual data.

    \note: QAbstractTextureImage should never be shared. Expect crashes, undefined
    behavior at best if this rule is not respected.
 */

/*!
    Constructs a new QAbstractTextureImage instance with \a parent as parent.
 */
QAbstractTextureImage::QAbstractTextureImage(QNode *parent)
    : QNode(*new QAbstractTextureImagePrivate, parent)
{
}

/*!
  The destructor.
 */
QAbstractTextureImage::~QAbstractTextureImage()
{
}


/*!
    \qmlproperty int Qt3D.Render::AbstractTextureImage::mipLevel

    Holds the mipmap level of the texture image.
 */

/*!
    \property Qt3DRender::QAbstractTextureImage::mipLevel

    Holds the mipmap level of the texture image.
 */
int QAbstractTextureImage::mipLevel() const
{
    Q_D(const QAbstractTextureImage);
    return d->m_mipLevel;
}

/*!
    \qmlproperty int Qt3D.Render::AbstractTextureImage::layer

    Holds the layer of the texture image.
 */

/*!
    \property Qt3DRender::QAbstractTextureImage::layer

    Holds the layer of the texture image.
 */
int QAbstractTextureImage::layer() const
{
    Q_D(const QAbstractTextureImage);
    return d->m_layer;
}

/*!
    \qmlproperty enumeration Qt3D.Render::AbstractTextureImage::face

    Holds the cube map face of the texture image.

    \value CubeMapPositiveX 0x8515   GL_TEXTURE_CUBE_MAP_POSITIVE_X
    \value CubeMapNegativeX 0x8516   GL_TEXTURE_CUBE_MAP_NEGATIVE_X
    \value CubeMapPositiveY 0x8517   GL_TEXTURE_CUBE_MAP_POSITIVE_Y
    \value CubeMapNegativeY 0x8518   GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
    \value CubeMapPositiveZ 0x8519   GL_TEXTURE_CUBE_MAP_POSITIVE_Z
    \value CubeMapNegativeZ 0x851A   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z

    \note The cube map face has a meaning only for
    \l [CPP] {Qt3DRender::QAbstractTexture::}{TargetCubeMap} and
    \l [CPP] {Qt3DRender::QAbstractTexture::}{TargetCubeMapArray}.
 */

/*!
    \property Qt3DRender::QAbstractTextureImage::face

    Holds the cube map face of the texture image.

    \note The cube map face has a meaning only for
    \l {QAbstractTexture::}{TargetCubeMap} and
    \l {QAbstractTexture::}{TargetCubeMapArray}.
 */
QAbstractTexture::CubeMapFace QAbstractTextureImage::face() const
{
    Q_D(const QAbstractTextureImage);
    return d->m_face;
}

void QAbstractTextureImage::setMipLevel(int level)
{
    Q_D(QAbstractTextureImage);
    if (level != d->m_mipLevel) {
        d->m_mipLevel = level;
        emit mipLevelChanged(level);
    }
}

void QAbstractTextureImage::setLayer(int layer)
{
    Q_D(QAbstractTextureImage);
    if (layer != d->m_layer) {
        d->m_layer = layer;
        emit layerChanged(layer);
    }
}

void QAbstractTextureImage::setFace(QAbstractTexture::CubeMapFace face)
{
    Q_D(QAbstractTextureImage);
    if (face != d->m_face) {
        d->m_face = face;
        emit faceChanged(face);
    }
}

/*!
    Triggers an update of the data generator that is sent to the backend.
 */
void QAbstractTextureImage::notifyDataGeneratorChanged()
{
    Q_D(QAbstractTextureImage);
    if (d->m_changeArbiter != nullptr) {
        QNodePropertyChangePtr change(new QNodePropertyChange(PropertyUpdated, QSceneChange::Node, id()));
        change->setPropertyName("dataGenerator");
        change->setValue(QVariant::fromValue(dataGenerator()));
        d->notifyObservers(change);
    }
}

/*! \internal */
QAbstractTextureImage::QAbstractTextureImage(QAbstractTextureImagePrivate &dd, QNode *parent)
    : QNode(dd, parent)
{
}

Qt3DCore::QNodeCreatedChangeBasePtr QAbstractTextureImage::createNodeCreationChange() const
{
    auto creationChange = Qt3DCore::QNodeCreatedChangePtr<QAbstractTextureImageData>::create(this);
    auto &data = creationChange->data;
    Q_D(const QAbstractTextureImage);
    data.mipLevel = d->m_mipLevel;
    data.layer = d->m_layer;
    data.face = d->m_face;
    data.generator = dataGenerator();
    return creationChange;
}

} // namespace Qt3DRender

QT_END_NAMESPACE
