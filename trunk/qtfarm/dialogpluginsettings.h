/**************************************************************************
** 	Copyright (C) 2008 by Jan Vaillant 									 **
* 	jvail@gmx.de														  *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License version 3        *
* 	as published by the Free Software Foundation.                         *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 			  *
**                                                                       **
**************************************************************************/


#ifndef DIALOGPLUGINSETTINGS_H
#define DIALOGPLUGINSETTINGS_H

#include <QtGui/QDialog>
#include "ui_dialogpluginsettings.h"

class QStringList;

class DialogPluginSettings : public QDialog
{
    Q_OBJECT

public:
    DialogPluginSettings(const QStringList &slPluginSettings, const QStringList &slAllPlugins, QWidget *parent = 0);
    ~DialogPluginSettings();
    
    QStringList getPluginSettings();

private slots:
	void updatePluginSettings();
    
private:
	QStringList _slPluginSettings;
	QStringList _slAllPlugins;
    Ui::DialogPluginSettingsClass ui;
};

#endif // DIALOGPLUGINSETTINGS_H
