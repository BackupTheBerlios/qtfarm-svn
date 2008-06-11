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


#ifndef QTFARMPLUGININTERFACES_H_
#define QTFARMPLUGININTERFACES_H_

#include <QtPlugin>
#include <QSqlQueryModel>
#include <QMap>


class QString;
class QStringList;
class QSqlQuery;
class QMenu;
class QDockWidget;
class QTreeWidgetItem;
class QTreeWidget;



class QtFarmSoilInterface
{
	Q_ENUMS(Data)
	Q_ENUMS(WidgetType)

public:
	
    
    virtual ~QtFarmSoilInterface() {}
    
	enum Data {
		QueryText,
		SortColumn,
		HiddenColumns,
		FavTable,
		FavColumnTable,
		FavColumnDb,
		ColumnsToJoin,
		DateColumn
	};
	enum WidgetType {
		Tab,
		Menu,
		DockWidget,
		TabContent
	};
		
    virtual QStringList features() const = 0;   
    virtual QMap<QtFarmSoilInterface::Data, QVariant> listMap() = 0;    
    virtual QMap<QtFarmSoilInterface::WidgetType, QWidget*> widgetMap(QWidget *parent = 0) = 0;
};


class QtFarmDairyInterface
{
public:
    virtual ~QtFarmDairyInterface() {}
    
	enum Data {
		QueryText,
		SortColumn,
		HiddenColumns,
		FavTable,
		FavColumnTable,
		FavColumnDb,
		ColumnsToJoin,
		DateColumn
	};
	enum WidgetType {
		Tab,
		Menu,
		DockWidget,
		TabContent
	};
		
    virtual QStringList features() const = 0;   
    virtual QMap<QtFarmDairyInterface::Data, QVariant> listMap() = 0;    
    virtual QMap<QtFarmDairyInterface::WidgetType, QWidget*> widgetMap(QWidget *parent = 0) = 0;
};


class QtFarmStockInterface
{
public:
    virtual ~QtFarmStockInterface() {}

    enum Data {
		QueryText,
		SortColumn,
		HiddenColumns,
		FavTable,
		FavColumnTable,
		FavColumnDb,
		ColumnsToJoin,
		DateColumn
	};
	enum WidgetType {
		Tab,
		Menu,
		DockWidget,
		TabContent
	};
		
    virtual QStringList features() const = 0;   
    virtual QMap<QtFarmStockInterface::Data, QVariant> listMap() = 0;    
    virtual QMap<QtFarmStockInterface::WidgetType, QWidget*> widgetMap(QWidget *parent = 0) = 0;
};



Q_DECLARE_INTERFACE(QtFarmSoilInterface,
                    "qtfarm.Plugin.QtFarmSoilInterface/1.0");
Q_DECLARE_INTERFACE(QtFarmDairyInterface,
                    "qtfarm.Plugin.QtFarmDairyInterface/1.0");
Q_DECLARE_INTERFACE(QtFarmStockInterface,
                    "qtfarm.Plugin.QtFarmStockInterface/1.0");

#endif /*QQTFARMPLUGININTERFACES_H_*/
