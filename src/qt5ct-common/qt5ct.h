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

#ifndef QT5CT_H
#define QT5CT_H

#define QT5CT_VERSION_MAJOR 1
#define QT5CT_VERSION_MINOR 10

#define QT5CT_TOSTRING(s) #s
#define QT5CT_STRINGIFY(s)         QT5CT_TOSTRING(s)

#define QT5CT_VERSION_INT (QT5CT_VERSION_MAJOR<<8 | QT5CT_VERSION_MINOR)
#define QT5CT_VERSION_STR QT5CT_STRINGIFY(QT5CT_VERSION_MAJOR.QT5CT_VERSION_MINOR)

#include <QSet>
#include <QString>
#include <QStringList>
#include <QPalette>

#ifdef QT5CT_LIBRARY
#define QT5CT_EXPORT Q_DECL_EXPORT
#else
#define QT5CT_EXPORT Q_DECL_IMPORT
#endif


class QT5CT_EXPORT Qt5CT
{
public:
    class StyleInstance
    {
    public:
        virtual void reloadSettings() = 0;
    };

    static void initConfig();
    static QString configPath();
    static QString configFile();
    static QStringList iconPaths();
    static QString userStyleSheetPath();
    static QStringList sharedStyleSheetPaths();
    static QString userColorSchemePath();
    static QString styleColorSchemeFile();
    static QStringList sharedColorSchemePaths();
    static QString resolvePath(const QString &path);
    static QPalette loadColorScheme(const QString &filePath, const QPalette &fallback);

    static void registerStyleInstance(StyleInstance *instance);
    static void unregisterStyleInstance(StyleInstance *instance);
    static void reloadStyleInstanceSettings();

private:
    static QSet<StyleInstance*> styleInstances;
};

#endif // QT5CT_H
