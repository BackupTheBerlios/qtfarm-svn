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

#include <QtGui>
#include <QSqlQueryModel>
#include <QMap>

#include "qtfarmsoilplugin.h"

QStringList QtFarmSoilPlugin::features() const
{
    return QStringList() <<  tr("QtFarmSoilPlugin") << tr("Version 1.0");
}


QMap<QtFarmSoilInterface::WidgetType, QWidget*> QtFarmSoilPlugin::widgetMap(QWidget *parent)
{
	QWidget *tab = new QWidget(parent);
	tab->setWindowTitle(tr("Schlagkartei"));
	tab->setObjectName(QString::fromUtf8("tabSoil"));

	QMenu *menu = new QMenu(parent);
	menu->setTitle("&Schlagkartei");
	
	MapViewer *mapviewer = new MapViewer(parent);
	
	QMap<QtFarmSoilInterface::WidgetType, QWidget*> map;
	map.insert(QtFarmSoilInterface::Tab, tab);
	map.insert(QtFarmSoilInterface::Menu, menu);
	map.insert(QtFarmSoilInterface::TabContent, mapviewer);
	
	return map;
	
}

QMap<QtFarmSoilInterface::Data, QVariant> QtFarmSoilPlugin::listMap()
{	
	QMap<QtFarmSoilInterface::Data, QVariant> map;
	map.insert(QtFarmSoilInterface::QueryText, "SELECT psm_id, "
												"psm_fav, "
												"Name, "
												"Wirkungsbereich, "
												"Wirkstoff, "
												"Zulassungsnummer AS 'Zul-Nr', "
												"Zulassungsende AS 'Zul-Ende' "
												"FROM v_psm");
	map.insert(QtFarmSoilInterface::SortColumn, 2);
	map.insertMulti(QtFarmSoilInterface::HiddenColumns, 0);
	map.insert(QtFarmSoilInterface::FavTable, "psm");
	map.insert(QtFarmSoilInterface::FavColumnTable, 1);
	map.insert(QtFarmSoilInterface::FavColumnDb, "psm_fav");
	map.insertMulti(QtFarmSoilInterface::ColumnsToJoin, "4,5");
	map.insert(QtFarmSoilInterface::DateColumn, 6);
	
	return map;
}


Q_EXPORT_PLUGIN2(qtfarmsoilplugin, QtFarmSoilPlugin);
