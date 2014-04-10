/**
 ******************************************************************************
 *
 * @file       configahrstwidget.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup ConfigPlugin Config Plugin
 * @{
 * @brief Telemetry configuration panel
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef CONFIGREVOWIDGET_H
#define CONFIGREVOWIDGET_H

#include "ui_revosensors.h"
#include "configtaskwidget.h"
#include "../uavobjectwidgetutils/configtaskwidget.h"
#include "extensionsystem/pluginmanager.h"
#include "uavobjectmanager.h"
#include "uavobject.h"
#include <QWidget>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QList>
#include <QTimer>
#include <QMutex>
#include "calibration/thermal/thermalcalibrationmodel.h"
#include "calibration/sixpointcalibrationmodel.h"

class Ui_Widget;


class ConfigRevoWidget : public ConfigTaskWidget {
    Q_OBJECT

public:
    ConfigRevoWidget(QWidget *parent = 0);
    ~ConfigRevoWidget();

private:
    OpenPilot::SixPointCalibrationModel *m_sixPointCalibrationModel;
    OpenPilot::ThermalCalibrationModel *m_thermalCalibrationModel;
    Ui_RevoSensorsWidget *m_ui;
    QMutex sensorsUpdateLock;

    int phaseCounter;
    const static double maxVarValue;
    const static int calibrationDelay = 10;

    bool collectingData;

    QList<double> gyro_accum_x;
    QList<double> gyro_accum_y;
    QList<double> gyro_accum_z;

    QList<double> rot_accum_roll;
    QList<double> rot_accum_pitch;


    double rot_data_roll;
    double rot_data_pitch;


    UAVObject::Metadata initialAttitudeStateMdata;
    UAVObject::Metadata initialGyroStateMdata;

    int position;

    static const int NOISE_SAMPLES = 50;

    // Board rotation store/recall
    qint16 storedBoardRotation[3];
    bool isBoardRotationStored;

private slots:
    void displayVisualHelp(QString elementID);
    void storeAndClearBoardRotation();
    void recallBoardRotation();
    void displayInstructions(QString instructions = QString(), bool replace = false);

    // ! Overriden method from the configTaskWidget to update UI
    virtual void refreshWidgetsValues(UAVObject *object = NULL);

    // Slots for calibrating the accel and gyro
    void levelCalibrationStart();
    void levelCalibrationSavePosition();
    void levelCalibrationCompute();
    void levelCalibrationGetSample(UAVObject *);

    // Slots for gyro bias zero
    void gyroCalibrationStart();
    void gyroBiasCalibrationGetSample(UAVObject *obj);

    // Slot for clearing home location
    void clearHomeLocation();

    void disableAllCalibrations();
    void enableAllCalibrations();

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // ConfigRevoWidget_H
