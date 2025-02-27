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

#include <QApplication>
#include <QSettings>
#include <QStyleFactory>
#include <QWidget>
#include "qt5ctproxystyle.h"

Qt5CTProxyStyle::Qt5CTProxyStyle()
{
    Qt5CT::registerStyleInstance(this);
    Qt5CTProxyStyle::reloadSettings();
}

void Qt5CTProxyStyle::reloadSettings()
{
    QSettings settings(Qt5CT::configFile(), QSettings::IniFormat);
    m_dialogButtonsHaveIcons = settings.value("Interface/dialog_buttons_have_icons", Qt::PartiallyChecked).toInt();
    m_activateItemOnSingleClick = settings.value("Interface/activate_item_on_single_click", Qt::PartiallyChecked).toInt();
    m_underlineShortcut = settings.value("Interface/underline_shortcut", Qt::PartiallyChecked).toInt();

    QString style = settings.value("Appearance/style", "fusion").toString().toLower();
    if(style == "qt5ct-style" || !QStyleFactory::keys().contains(style, Qt::CaseInsensitive))
        style = "fusion";

    if(style != m_style)
    {
        setBaseStyle(QStyleFactory::create(style));
        m_style = style;
    }
}

Qt5CTProxyStyle::~Qt5CTProxyStyle()
{
    Qt5CT::unregisterStyleInstance(this);
}

static int adjustIconSize(int size)
{
    return (size < 14) ? size :
           (size < 19) ? 16 :
           (size < 27) ? 22 :
           (size < 40) ? 32 :
           (size < 56) ? 48 : size;
}

int Qt5CTProxyStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    int size = QProxyStyle::pixelMetric(metric, option, widget);
    qreal scale = widget ? widget->devicePixelRatioF() : qApp->devicePixelRatio();

    // at 1x or 2x, adjust icon sizes to match common raster sizes
    if (scale != 1.0 && scale != 2.0)
        return size;

    switch (metric) {
    case PM_ToolBarIconSize:
    case PM_SmallIconSize:
    case PM_LargeIconSize:
    case PM_IconViewIconSize:
    case PM_ListViewIconSize:
    case PM_TabBarIconSize:
    case PM_MessageBoxIconSize:
    case PM_ButtonIconSize:
        return adjustIconSize(size * (int)scale) / (int)scale;
    default:
        return size;
    }
}

int Qt5CTProxyStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if(hint == QStyle::SH_DialogButtonBox_ButtonsHaveIcons)
    {
        if(m_dialogButtonsHaveIcons == Qt::Unchecked)
            return 0;
        if(m_dialogButtonsHaveIcons == Qt::Checked)
            return 1;
    }
    else if(hint == QStyle::SH_ItemView_ActivateItemOnSingleClick)
    {
        if(m_activateItemOnSingleClick == Qt::Unchecked)
            return 0;
        if(m_activateItemOnSingleClick == Qt::Checked)
            return 1;
    }
    else if(hint == QStyle::SH_UnderlineShortcut)
    {
        if(m_underlineShortcut == Qt::Unchecked)
            return 0;
        if(m_underlineShortcut == Qt::Checked)
            return 1;
    }
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

bool Qt5CTProxyStyle::event(QEvent *e)
{
    // QProxyStyle::event() doesn't handle DeferredDelete correctly
    // (forwards it to the baseStyle instead of deleting itself)
    if (e->type() == QEvent::DeferredDelete)
        return QObject::event(e);

    return QProxyStyle::event(e);
}
