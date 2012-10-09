/*
 * libsynthclone_lv2 - LV2 effect plugin for `synthclone`
 * Copyright (C) 2012 Devin Anderson
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 675 Mass
 * Ave, Cambridge, MA 02139, USA.
 */

#ifndef __EFFECTVIEW_H__
#define __EFFECTVIEW_H__

#include <cassert>

#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableView>

#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <suil/suil.h>

#include <synthclone/designerview.h>
#include <synthclone/types.h>

#include "channelmapdelegate.h"

class EffectView: public synthclone::DesignerView {

    Q_OBJECT

public:

    explicit
    EffectView(QObject *parent=0);

    ~EffectView();

    unsigned int
    getSupportQuality(const QString &widgetTypeURI);

public slots:

    void
    addAudioInputPort(const QString &name);

    void
    addAudioOutputPort(const QString &name);

    void
    clearAudioInputPorts();

    void
    clearAudioOutputPorts();

    void
    removeAudioInputPort();

    void
    removeAudioOutputPort();

    void
    setAudioInputChannel(synthclone::SampleChannelCount inputChannel,
                         int effectChannel);

    void
    setAudioOutputChannel(synthclone::SampleChannelCount outputChannel,
                          int effectChannel);

    void
    setInstanceCount(int instances);

    void
    setName(const QString &name);

    void
    setPortValue(uint32_t index, uint32_t size, uint32_t protocol,
                 void const *value);

    void
    setSampleChannelCount(synthclone::SampleChannelCount channels);

    void
    setURIData(const QString &widgetURI, const QString &widgetTypeURI,
               const QString &pluginURI, const QString &binaryPath,
               const QString &bundlePath);

signals:

    void
    audioInputChannelChanged(synthclone::SampleChannelCount inputChannel,
                             int effectChannel);

    void
    audioOutputChannelChanged(synthclone::SampleChannelCount outputChannel,
                              int effectChannel);

    void
    instanceCountChanged(int instances);

    void
    nameChanged(const QString &name);

    void
    portValueChanged(uint32_t portIndex, uint32_t bufferSize,
                     uint32_t protocol, void const *buffer);

private slots:

    void
    handlePortWriteRequest(uint32_t portIndex, uint32_t bufferSize,
                           uint32_t protocol, void const *buffer);

private:

    static void
    handlePortWriteRequest(SuilController controller, uint32_t portIndex,
                           uint32_t bufferSize, uint32_t protocol,
                           void const *buffer);

    void
    resetInstanceData();

    void
    setModelData(int row, int column, const QVariant &value,
                 int role=Qt::UserRole);

    QStringList audioInputPortNames;
    QStringList audioOutputPortNames;
    ChannelMapDelegate channelMapTableDelegate;
    QStandardItemModel channelMapTableModel;
    QTableView *channelMapTableView;
    QPushButton *closeButton;
    SuilHost *host;
    SuilInstance *instance;
    QSpinBox *instances;
    QWidget *instanceUI;
    QLineEdit *name;
    QWidget *parametersTab;

};

#endif