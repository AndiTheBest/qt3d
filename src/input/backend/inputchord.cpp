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

#include "inputchord_p.h"
#include <Qt3DInput/qinputchord.h>
#include <Qt3DInput/private/qinputchord_p.h>
#include <Qt3DCore/qnodepropertychange.h>
#include <Qt3DCore/qnodeaddedpropertychange.h>
#include <Qt3DCore/qnoderemovedpropertychange.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

namespace Input {

InputChord::InputChord()
    : Qt3DCore::QBackendNode()
    , m_chords()
    , m_inputsToTrigger()
    , m_timeout(0)
    , m_startTime(0)
{
}

void InputChord::initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change)
{
    const auto typedChange = qSharedPointerCast<Qt3DCore::QNodeCreatedChange<QInputChordData>>(change);
    const QInputChordData &data = typedChange->data;
    m_chords = data.chordIds;
    m_timeout = data.timeout;
}

void InputChord::cleanup()
{
    QBackendNode::setEnabled(false);
    m_timeout = 0;
    m_startTime = 0;
    m_chords.clear();
    m_inputsToTrigger.clear();
}

void InputChord::reset()
{
    m_startTime = 0;
    m_inputsToTrigger = m_chords;
}

bool InputChord::actionTriggered(Qt3DCore::QNodeId input)
{
    m_inputsToTrigger.removeOne(input);
    if (m_inputsToTrigger.isEmpty()) {
        //All Triggered
        reset();
        return true;
    }
    return false;
}

void InputChord::setStartTime(qint64 time)
{
    m_startTime = time;
}

void InputChord::sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e)
{
    switch (e->type()) {
    case Qt3DCore::PropertyUpdated: {
        const auto change = qSharedPointerCast<Qt3DCore::QNodePropertyChange>(e);
        if (change->propertyName() == QByteArrayLiteral("timeout"))
            m_timeout = change->value().toInt();
        break;
    }

    case Qt3DCore::NodeAdded: {
        const auto change = qSharedPointerCast<Qt3DCore::QNodeAddedPropertyChange>(e);
        if (change->propertyName() == QByteArrayLiteral("chord")) {
            m_chords.push_back(change->addedNodeId());
            m_inputsToTrigger.push_back(change->addedNodeId());
        }
        break;
    }

    case Qt3DCore::NodeRemoved: {
        const auto change = qSharedPointerCast<Qt3DCore::QNodeRemovedPropertyChange>(e);
        if (change->propertyName() == QByteArrayLiteral("chord")) {
            m_chords.removeOne(change->removedNodeId());
            m_inputsToTrigger.removeOne(change->removedNodeId());
        }
        break;
    }

    default:
        break;
    }
    QBackendNode::sceneChangeEvent(e);
}

} // namespace Input

} // namespace Qt3DInput

QT_END_NAMESPACE

