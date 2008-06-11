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

#include <QLabel>
#include <QDebug>
#include <QStringList>
#include <QSettings>
#include <QHeaderView>

#include "dialogpluginsettings.h"

DialogPluginSettings::DialogPluginSettings(const QStringList &slPluginSettings, const QStringList &slAllPlugins, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);

	_slPluginSettings = slPluginSettings;
	_slAllPlugins = slAllPlugins;
	
	ui.twPlugins->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	ui.twPlugins->verticalHeader()->setHidden(true);
	ui.twPlugins->setRowCount(_slAllPlugins.size());
	ui.twPlugins->horizontalHeader()->setHidden(true);
	
	QSettings settings("QtFarm", "QtFarm1.0");
	settings.beginGroup("Plugins");
	ui.cbPlugins->setChecked(settings.value("showPluginDialogatStart").toBool());
	settings.endGroup();
	
	if(_slPluginSettings.isEmpty() == true){
	
		for(int i = 0; i < _slAllPlugins.size(); ++i){
			
			QTableWidgetItem *newItem = new QTableWidgetItem(_slAllPlugins.at(i));
			ui.twPlugins->setItem(i, 0, newItem);
			newItem->setCheckState(Qt::Checked);
			
			 if (_slAllPlugins.at(i).contains("dairy") == true) {
					QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Milchvieh"));
					ui.twPlugins->setItem(i, 1, newItem);
			 }else if (_slAllPlugins.at(i).contains("soil") == true) {
					QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Schlagkartei"));
					ui.twPlugins->setItem(i, 1, newItem);
			 }else if (_slAllPlugins.at(i).contains("stock") == true) {
					QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Lagerhaltung"));
					ui.twPlugins->setItem(i, 1, newItem);
			 }

			}
		
		_slPluginSettings = _slAllPlugins;	
		
	}else{
		
		for(int i = 0; i < _slAllPlugins.size(); ++i){
			
			QTableWidgetItem *newItem = new QTableWidgetItem(_slAllPlugins.at(i));
			ui.twPlugins->setItem(i, 0, newItem);
				
				if(_slPluginSettings.filter(ui.twPlugins->item(i, 0)->text()).isEmpty() == false){
					ui.twPlugins->item(i, 0)->setCheckState(Qt::Checked);
					
				}else{
					ui.twPlugins->item(i, 0)->setCheckState(Qt::Unchecked);
				}				

				 if (_slAllPlugins.at(i).contains("dairy") == true) {
						QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Milchvieh"));
						ui.twPlugins->setItem(i, 1, newItem);
				 }else if (_slAllPlugins.at(i).contains("soil") == true) {
						QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Schlagkartei"));
						ui.twPlugins->setItem(i, 1, newItem);
				 }else if (_slAllPlugins.at(i).contains("stock") == true) {
						QTableWidgetItem *newItem = new QTableWidgetItem(tr("Modul Lagerhaltung"));
						ui.twPlugins->setItem(i, 1, newItem);	 
				 }
		}
		
	}
	connect(ui.pbOK, SIGNAL(clicked()), this, SLOT(updatePluginSettings()));
	ui.pbOK->setFocus();
	
}

void DialogPluginSettings::updatePluginSettings()
{
	int iSize = _slAllPlugins.size();
	
//	qDebug() << "iSize: " << iSize;
 	
	for(int i = 0; i < iSize; ++i){
			
			if (ui.twPlugins->item(i, 0)->checkState() == Qt::Unchecked){
				_slAllPlugins.removeOne(ui.twPlugins->item(i, 0)->text());
				
				qDebug() << "i: " << i;
				qDebug() << "ui.twPlugins->item(i, 0): " << ui.twPlugins->item(i, 0)->text();
			}

		}
//	qDebug() << "_slAllPlugins: " << _slAllPlugins;
	
	
    QSettings settings("QtFarm", "QtFarm1.0");    
	    settings.beginGroup("Plugins");
	    if (_slAllPlugins.filter("soil").isEmpty() == false){
	    	settings.setValue("QtFarmSoilPlugin", true);
	    }else{
	    	settings.setValue("QtFarmSoilPlugin", false);
	    }
	    if (_slAllPlugins.filter("dairy").isEmpty() == false){
	    	settings.setValue("QtFarmDairyPlugin", true);
	    }else{
	    	settings.setValue("QtFarmDairyPlugin", false);
	    }
	    if (_slAllPlugins.filter("stock").isEmpty() == false){
	    	settings.setValue("QtFarmStockPlugin", true);
	    }else{
	    	settings.setValue("QtFarmStockPlugin", false);
	    }
	    
	    settings.setValue("showPluginDialogatStart", ui.cbPlugins->isChecked());
	    settings.endGroup();
}

QStringList DialogPluginSettings::getPluginSettings()
{
	return _slAllPlugins;
}

DialogPluginSettings::~DialogPluginSettings()
{

}
