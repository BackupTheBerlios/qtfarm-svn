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

#include <QHeaderView>
#include <QFocusEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStatusBar>
#include <QDate>
#include "dockwidgetlist.h"

DockWidgetList::DockWidgetList(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
	ui.setupUi(this);

	setWindowTitle(title);
	ui.tableView->horizontalHeader()->setStretchLastSection(true);
	qm = new SqlQueryModel(this);
	proxyModel = new SortFilterProxyModel(this);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModel->setSortLocaleAware(true);
	proxyModel->setDynamicSortFilter(true);
	ui.tableView->verticalHeader()->setHidden(true);
	ui.tableView->setName(title);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	
    connect(ui.tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(tableClicked(const QModelIndex &)));
	
	connect(proxyModel, SIGNAL(layoutChanged ()), ui.tableView, SLOT(resizeRowsToContents()));	

}


void DockWidgetList::init(const QMap<QtFarmSoilInterface::Data, QVariant> &listMap,
		WidgetFilter *filter)
{
    
	connect(ui.tableView, SIGNAL(hasFocus(QList<QString> &, QSortFilterProxyModel*, QString &, QTableView*)),
				filter, SLOT(setCbList(QList<QString> &, QSortFilterProxyModel*, QString &, QTableView*)));
	
	
	QMap<QtFarmSoilInterface::Data, QVariant>::const_iterator iData = listMap.constBegin();
    while (iData != listMap.constEnd()) {
        	 
        if(iData.key() == QtFarmSoilInterface::QueryText){
        	if(iData.value().type() != QVariant::String){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}
        }
        else if(iData.key() == QtFarmSoilInterface::SortColumn){
        	if(iData.value().type() != QVariant::Int){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}
        }
        else if(iData.key() == QtFarmSoilInterface::HiddenColumns){
        	if(!iData.value().isValid()){
        		qDebug() << "Error: " << iData.value().type() << iData.value();
        		return;
        	}	        	
        }
        else if(iData.key() == QtFarmSoilInterface::FavTable){
        	if(iData.value().type() != QVariant::String){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}
        }
        else if(iData.key() == QtFarmSoilInterface::FavColumnTable){
        	if(iData.value().type() != QVariant::Int){
        		qDebug() << "Error: " << iData.key() << iData.value();
        	}
        }
        else if(iData.key() == QtFarmSoilInterface::FavColumnDb){
        	if(iData.value().type() != QVariant::String){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}
        }
        else if(iData.key() == QtFarmSoilInterface::ColumnsToJoin){
        	if(!iData.value().isValid()){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}	        	
        }
        else if(iData.key() == QtFarmSoilInterface::DateColumn){
        	if(iData.value().type() != QVariant::Int){
        		qDebug() << "Error: " << iData.key() << iData.value();
        		return;
        	}	        	
        }
        ++iData;
	}

	//FavColumnTable, FavColumnDb, ColumnsToJoin
	qm->setMapData(listMap.value(QtFarmSoilInterface::FavColumnTable).toInt(), 
			listMap.value(QtFarmSoilInterface::FavColumnDb).toInt(),
			listMap.value(QtFarmSoilInterface::ColumnsToJoin).toString(),
			listMap.value(QtFarmSoilInterface::DateColumn).toInt());
	favColumnTable = listMap.value(QtFarmSoilInterface::FavColumnTable).toInt();
    
    
    //Query
	qm->setQuery(listMap.value(QtFarmSoilInterface::QueryText).toString());
	while(qm->canFetchMore()){
		qm->fetchMore();
	}

	if(qm->lastError().type() != QSqlError::NoError){
		qDebug() << qm->lastError().type() << qm->lastError().text();
		return;
	}
	
	proxyModel->setSourceModel(qm);
	proxyModel->setSortRole(Qt::EditRole);
	ui.tableView->setModel(proxyModel);

	//HiddenColumns
    for (int i = 0; i < listMap.values(QtFarmSoilInterface::HiddenColumns).size(); ++i) {
    	ui.tableView->horizontalHeader()->setSectionHidden(
    			listMap.values(QtFarmSoilInterface::HiddenColumns).at(i).toInt(), true);
//    	qDebug() << "HiddenColumns: " << map.values("HiddenColumns").at(i).toInt();
    }
	    
    ui.tableView->setList(listMap.value(QtFarmSoilInterface::FavColumnTable).toInt());
	ui.tableView->resizeRowsToContents();
	ui.tableView->resizeColumnsToContents();
	
	//SortColumn
	ui.tableView->setSortingEnabled(true);
	proxyModel->sort(listMap.value(QtFarmSoilInterface::SortColumn).toInt(), Qt::AscendingOrder);
	ui.tableView->horizontalHeader()->setSortIndicator(
			listMap.value(QtFarmSoilInterface::SortColumn).toInt(), Qt::AscendingOrder);
//	qDebug() << "SortColumn: " << map.value("SortColumn").toInt();
	
	ui.tableView->horizontalHeader()->model()->setHeaderData(
			listMap.value(QtFarmSoilInterface::FavColumnTable).toInt(),
			Qt::Horizontal, QVariant(QPixmap(":/bilder/star_blue12.png")),
			Qt::DecorationRole);
	ui.tableView->horizontalHeader()->model()->setHeaderData(
			listMap.value(QtFarmSoilInterface::FavColumnTable).toInt(),
			Qt::Horizontal, QVariant(""), Qt::DisplayRole);
	ui.tableView->horizontalHeader()->setResizeMode(
			listMap.value(QtFarmSoilInterface::FavColumnTable).toInt(),
			QHeaderView::ResizeToContents);
	ui.tableView->horizontalHeader()->setHighlightSections(false);
	
}

void DockWidgetList::tableClicked(const QModelIndex &index)
{	
	
	lastIndex = index;
	qDebug() << index;
	qDebug() << index.data(Qt::EditRole);
	
	if(index.column() == favColumnTable){
		if(index.data(Qt::EditRole).toString() == "0"){
				qm->setData(proxyModel->mapToSource(index), "1", Qt::EditRole);
		}
		else if(index.data(Qt::EditRole).toString() == "1"){
				qm->setData(proxyModel->mapToSource(index), "0", Qt::EditRole);
		}
		ui.tableView->resizeRowsToContents();
		ui.tableView->scrollTo(lastIndex.sibling(lastIndex.row(), 2), QAbstractItemView::EnsureVisible);
		ui.tableView->selectRow(lastIndex.row());

//		qDebug() << lastIndex.row();
	}	
}


DockWidgetList::~DockWidgetList()
{

}




SqlQueryModel::SqlQueryModel(QObject * parent )
	: QSqlQueryModel(parent)
{
}

void SqlQueryModel::setMapData(int _favColumnTable, int _favColumnDb,
		const QString &_columnsToJoin, int _dateColumn)
{
	favColumnTable = _favColumnTable;
	favColumnDb = _favColumnDb;
	columnsToJoin = _columnsToJoin;
	dateColumn = _dateColumn;
}

Qt::ItemFlags SqlQueryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()){
        return Qt::ItemIsEnabled;
    }else if(index.column() == 2){
    	return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }else{
    	return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    
    
}

bool SqlQueryModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

    	if(index.column() == favColumnTable){

    		QSqlQuery q;
    		q.exec("update  psm set psm_fav =" + value.toString() + " where psm_id =" +
    				record(index.row()).value(0).toString());

    		/* setValue() schreibt nicht
    		record(index.row()).field(2).setReadOnly(false);
    		record(index.row()).field(2).setValue(value);
			*/

    		QSqlQueryModel::setQuery(this->query().lastQuery()); // schlechte Lösung
    		while(canFetchMore()){
    			fetchMore();
    		}
    		
//    		emit dataChanged(index, index);
    		 return true;    			
    	}        
    	return false;
    }    
    return false;
}

QVariant SqlQueryModel::data(const QModelIndex & index, int role) const
{
	QString curr(QSqlQueryModel::data(index, Qt::DisplayRole).toString());
	
	if(index.column() == favColumnTable){
		
//		qDebug() << "favColumnTable" << QSqlQueryModel::data(index.sibling(index.row(), favColumnTable), role).toString();
		
		if (QSqlQueryModel::data(index.sibling(index.row(), favColumnTable), Qt::DisplayRole).toString() == "0" 
			&& role == Qt::DecorationRole){
//			qDebug() << "ist0";
			return QVariant(QPixmap(":/bilder/bluedot16.png"));
		}
		else if (QSqlQueryModel::data(index.sibling(index.row(), favColumnTable), Qt::DisplayRole).toString() == "1" 
			&& role == Qt::DecorationRole){
//			qDebug() << "ist1";
			return QVariant(QPixmap(":/bilder/star_blue12.png"));
		}
		else if (role == Qt::DisplayRole){			
			return QVariant();			
		}
		else if (role == Qt::EditRole){			
			return QSqlQueryModel::data(index, Qt::DisplayRole);
		}
		else{
			return QSqlQueryModel::data(index, role);
		}
	}
	
	if(index.column() == dateColumn){
		if (role == Qt::DisplayRole){			
			return QDate::fromString(QSqlQueryModel::data(index, role).toString(), "yyyy-MM-dd");			
		}
		else{
			return QSqlQueryModel::data(index, role);
		}
	}
	else{			
		if(role == Qt::EditRole){
			return QSqlQueryModel::data(index, Qt::DisplayRole);
		}else{
			return QSqlQueryModel::data(index, role);
		}				
	}
}


SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
     : QSortFilterProxyModel(parent)
 {
 }


QVariant SortFilterProxyModel::data(const QModelIndex &index, int role) const
{
	return QSortFilterProxyModel::data(index, role);
}
