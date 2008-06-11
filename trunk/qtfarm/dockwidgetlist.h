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

#ifndef DOCKWIDGETLIST_H
#define DOCKWIDGETLIST_H

#include <QtGui/QWidget>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QwwClearLineEdit>

#include "ui_dockwidgetlist.h"
#include "qtfarmplugininterfaces.h"
#include "widgetfilter.h"

class SqlQueryModel;
class SortFilterProxyModel;


class DockWidgetList : public QDockWidget
{
    Q_OBJECT

public:
    DockWidgetList(const QString & title, QWidget *parent = 0);
    ~DockWidgetList();
    
	void init(const QMap<QtFarmSoilInterface::Data, QVariant> &listMap, 
			WidgetFilter *filter);

private slots:
	void tableClicked(const QModelIndex &index);
	
	
private:
	SqlQueryModel *qm;
	SortFilterProxyModel *proxyModel;
	QModelIndex lastIndex;
    Ui::DockWidgetListClass ui;
    int favColumnTable;

};


class SqlQueryModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	SqlQueryModel(QObject * parent = 0);
	~SqlQueryModel() {};
		
	bool setData(const QModelIndex &index, const QVariant &value,
	                  int role = Qt::EditRole); 
	void setMapData(int _favColumnTable, int _favColumnDb, 
	    		const QString &_columnsToJoin,
	    		int _dateColumn);

private:
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	int favColumnTable;
	int favColumnDb;
	QString columnsToJoin;
	int dateColumn;

};


class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
	SortFilterProxyModel(QObject *parent = 0);

private:
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

};

#endif // DOCKWIDGETLIST_H
