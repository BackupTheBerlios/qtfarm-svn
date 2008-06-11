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

#include <QDebug>
#include <QToolButton>
#include <QStatusBar>

#include "widgetfilter.h"

WidgetFilter::WidgetFilter(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setDisabled(true);
	ui.comboBox->setDisabled(true);
//	ui.lineEdit->button()->setToolTip(tr("Filter löschen"));

}

void WidgetFilter::setCbList(QList<QString> &list, QSortFilterProxyModel *sortmodel,
		QString &name, QTableView *_view)
{	
	
	if(_name == name){
		return;
	}else{
		ui.lineEdit->setEnabled(true);
		ui.comboBox->setEnabled(true);
		
		ui.comboBox->clear();
		ui.lineEdit->clear();
		model = sortmodel;
        view = _view;
		ui.comboBox->addItems(list);
		emit statusMessage(tr("Anzahl Datensätze: ") + QString::number(model->rowCount(QModelIndex())) + tr(" (von ") +
			QString::number(model->sourceModel()->rowCount(QModelIndex())) + ")");
	}

	_name = name;
}

void WidgetFilter::on_lineEdit_textChanged()
{
	model->setFilterKeyColumn(filterKeyColumn(ui.comboBox->currentIndex()));
	model->setFilterWildcard(ui.lineEdit->text().replace(",","."));
	view->resizeRowsToContents();
	emit statusMessage(tr("Anzahl Datensätze: ") + QString::number(model->rowCount(QModelIndex())) + tr(" (von ") +
		QString::number(model->sourceModel()->rowCount(QModelIndex())) + ")");
	

}

void WidgetFilter::on_comboBox_currentIndexChanged(int index)
{
	model->setFilterKeyColumn(filterKeyColumn(index));
	model->setFilterWildcard(ui.lineEdit->text().replace(",","."));
	if(!ui.lineEdit->text().isEmpty()){
		view->resizeRowsToContents();
		emit statusMessage(tr("Anzahl Datensätze: ") + QString::number(model->rowCount(QModelIndex())) + tr(" (von ") +
			QString::number(model->sourceModel()->rowCount(QModelIndex())) + ")");
	}

}

int WidgetFilter::filterKeyColumn(int index)
{
	if (ui.comboBox->currentText() == 
		model->headerData(index, Qt::Horizontal, Qt::DisplayRole).toString()){
		return index;
	}else{
		for (int i = 0; i < model->columnCount(QModelIndex()); ++i){
			if(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() ==
				ui.comboBox->currentText())
				return i;
		}
	}
}


WidgetFilter::~WidgetFilter()
{

}
