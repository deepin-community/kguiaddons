/*
    SPDX-FileCopyrightText: 2009 Michael Leupold <lemma@confuego.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "kmodifierkeyinfo.h"
#include "kmodifierkeyinfoprovider_p.h"
#include <kguiaddons_debug.h>

#include <QGuiApplication>
#include <QPluginLoader>

KModifierKeyInfoProvider *createProvider()
{
    QPluginLoader loader(QStringLiteral("kf5/kguiaddons/kmodifierkey/kmodifierkey_") + qGuiApp->platformName());
    auto instance = dynamic_cast<KModifierKeyInfoProvider *>(loader.instance());
    if (instance) {
        return instance;
    }
    qCWarning(KGUIADDONS_LOG) << "Error: could not load plugin for platform" << loader.fileName() << "error:" << loader.errorString() << loader.instance();
    return new KModifierKeyInfoProvider;
}

KModifierKeyInfo::KModifierKeyInfo(QObject *parent)
    : QObject(parent)
    , p(createProvider())
{
    connect(p.data(), &KModifierKeyInfoProvider::keyPressed, this, &KModifierKeyInfo::keyPressed);
    connect(p.data(), &KModifierKeyInfoProvider::keyLatched, this, &KModifierKeyInfo::keyLatched);
    connect(p.data(), &KModifierKeyInfoProvider::keyLocked, this, &KModifierKeyInfo::keyLocked);
    connect(p.data(), &KModifierKeyInfoProvider::buttonPressed, this, &KModifierKeyInfo::buttonPressed);
    connect(p.data(), &KModifierKeyInfoProvider::keyAdded, this, &KModifierKeyInfo::keyAdded);
    connect(p.data(), &KModifierKeyInfoProvider::keyRemoved, this, &KModifierKeyInfo::keyRemoved);
}

KModifierKeyInfo::~KModifierKeyInfo()
{
}

bool KModifierKeyInfo::knowsKey(Qt::Key key) const
{
    return p->knowsKey(key);
}

const QList<Qt::Key> KModifierKeyInfo::knownKeys() const
{
    return p->knownKeys();
}

bool KModifierKeyInfo::isKeyPressed(Qt::Key key) const
{
    return p->isKeyPressed(key);
}

bool KModifierKeyInfo::isKeyLatched(Qt::Key key) const
{
    return p->isKeyLatched(key);
}

bool KModifierKeyInfo::setKeyLatched(Qt::Key key, bool latched)
{
    return p->setKeyLatched(key, latched);
}

bool KModifierKeyInfo::isKeyLocked(Qt::Key key) const
{
    return p->isKeyLocked(key);
}

bool KModifierKeyInfo::setKeyLocked(Qt::Key key, bool locked)
{
    return p->setKeyLocked(key, locked);
}

bool KModifierKeyInfo::isButtonPressed(Qt::MouseButton button) const
{
    return p->isButtonPressed(button);
}
