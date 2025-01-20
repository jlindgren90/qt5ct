/*
 * Copyright (c) 2014-2025, Ilya Kotov <forkotov02@ya.ru>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QDir>
#include <QLocale>
#include <QLatin1String>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QFile>
#include <QSettings>
#include <QtDebug>
#include "qt5ct.h"

#ifndef QT5CT_DATADIR
#define QT5CT_DATADIR "/usr/share"
#endif

QSet<Qt5CT::StyleInstance*> Qt5CT::styleInstances;

void Qt5CT::initConfig()
{
    if(QFile::exists(configFile()))
        return;

    QString globalConfig = QStandardPaths::locate(QStandardPaths::GenericConfigLocation, "qt5ct/qt5ct.conf");
    if(globalConfig.isEmpty())
        return;

    QDir("/").mkpath(configPath());
    QFile::copy(globalConfig, configFile());
}

QString Qt5CT::configPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + QLatin1String("/qt5ct");
}

QString Qt5CT::configFile()
{
    return configPath() + QLatin1String("/qt5ct.conf");
}

QStringList Qt5CT::iconPaths()
{
    QStringList paths, out;
    paths << QDir::homePath() + QLatin1String("/.icons");

    for(const QString &p : QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation))
    {
        paths << (p + QLatin1String("/icons"));
    }
    paths.removeDuplicates();

    //remove invalid
    for(const QString &p : qAsConst(paths))
    {
        if(QDir(p).exists())
            out << p;
    }
    return out;
}

QString Qt5CT::userStyleSheetPath()
{
    return configPath() + QLatin1String("/qss");
}

QStringList Qt5CT::sharedStyleSheetPaths()
{
    QStringList paths;
    for(const QString &p : QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation))
    {
        paths << (p + QLatin1String("/qt5ct/qss"));
    }
    paths << QLatin1String(QT5CT_DATADIR"/qt5ct/qss");
    paths.removeDuplicates();
    return paths;
}

QString Qt5CT::userColorSchemePath()
{
    return configPath() + QLatin1String("/colors");
}

QString Qt5CT::styleColorSchemeFile()
{
    return configPath() + QLatin1String("/style-colors.conf");
}

QStringList Qt5CT::sharedColorSchemePaths()
{
    QStringList paths;
    for(const QString &p : QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation))
    {
        paths << (p + QLatin1String("/qt5ct/colors"));
    }
    paths << QLatin1String(QT5CT_DATADIR"/qt5ct/colors");
    paths.removeDuplicates();
    return paths;
}

QString Qt5CT::resolvePath(const QString &path)
{
    QString tmp = path;
    tmp.replace("~", QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    if(!tmp.contains("$"))
        return tmp;

    //find environment variables
    static const QRegularExpression regexp("\\$([A-Z_]+)\\/");
    QRegularExpressionMatchIterator it = regexp.globalMatch(tmp);

    while (it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        QString captured = match.captured(1);
        tmp.replace(QLatin1String("$") + captured, qgetenv(captured.toLatin1().constData()) );
    }

    return tmp;
}

QPalette Qt5CT::loadColorScheme(const QString &filePath, const QPalette &fallback)
{
    QPalette customPalette;
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("ColorScheme");
    QStringList activeColors = settings.value("active_colors").toStringList();
    QStringList inactiveColors = settings.value("inactive_colors").toStringList();
    QStringList disabledColors = settings.value("disabled_colors").toStringList();
    settings.endGroup();

    if(activeColors.count() >= QPalette::NColorRoles &&
            inactiveColors.count() >= QPalette::NColorRoles &&
            disabledColors.count() >= QPalette::NColorRoles)
    {
        for (int i = 0; i < QPalette::NColorRoles; i++)
        {
            QPalette::ColorRole role = QPalette::ColorRole(i);
            customPalette.setColor(QPalette::Active, role, QColor(activeColors.at(i)));
            customPalette.setColor(QPalette::Inactive, role, QColor(inactiveColors.at(i)));
            customPalette.setColor(QPalette::Disabled, role, QColor(disabledColors.at(i)));
        }
    }
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    else if(activeColors.count() == QPalette::NColorRoles - 1 &&
            inactiveColors.count() == QPalette::NColorRoles - 1 &&
            disabledColors.count() == QPalette::NColorRoles - 1)
    {
        //old format compatibility
        for (int i = 0; i < QPalette::NColorRoles - 1; i++)
        {
            QPalette::ColorRole role = QPalette::ColorRole(i);
            customPalette.setColor(QPalette::Active, role, QColor(activeColors.at(i)));
            customPalette.setColor(QPalette::Inactive, role, QColor(inactiveColors.at(i)));
            customPalette.setColor(QPalette::Disabled, role, QColor(disabledColors.at(i)));
        }
        QColor textColor = customPalette.text().color();
        textColor.setAlpha(128);
        customPalette.setColor(QPalette::Active, QPalette::PlaceholderText, textColor);
        customPalette.setColor(QPalette::Inactive, QPalette::PlaceholderText, textColor);
        customPalette.setColor(QPalette::Disabled, QPalette::PlaceholderText, textColor);
    }
#endif
    else
    {
        customPalette = fallback; //load fallback palette
    }

    return customPalette;
}

void Qt5CT::registerStyleInstance(Qt5CT::StyleInstance *instance)
{
    styleInstances.insert(instance);
}

void Qt5CT::unregisterStyleInstance(Qt5CT::StyleInstance *instance)
{
    styleInstances.remove(instance);
}

void Qt5CT::reloadStyleInstanceSettings()
{
    for(auto instance : qAsConst(styleInstances))
        instance->reloadSettings();
}
