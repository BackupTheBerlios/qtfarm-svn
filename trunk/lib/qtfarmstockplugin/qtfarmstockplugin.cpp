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

#include "qtfarmstockplugin.h"


QStringList QtFarmStockPlugin::features() const
{
    return QStringList() <<  tr("QtFarmStockPlugin") << tr("Version 1.0");
}

QMap<QtFarmStockInterface::WidgetType, QWidget*> QtFarmStockPlugin::widgetMap(QWidget *parent)
{

	QMenu *menu = new QMenu(parent);
	menu->setTitle("&Lager");
	
	QMap<QtFarmStockInterface::WidgetType, QWidget*> map;
	map.insert(QtFarmStockInterface::Menu, menu);
	
	return map;
	
}

QMap<QtFarmStockInterface::Data, QVariant> QtFarmStockPlugin::listMap()
{	

}


Q_EXPORT_PLUGIN2(qtfarmstockplugin, QtFarmStockPlugin);
