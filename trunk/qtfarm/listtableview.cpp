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

#include <QMessageBox>
#include <QFocusEvent>
#include <QHeaderView>
#include <QDebug>
#include "listtableview.h"

ListTableView::ListTableView( QWidget* parent )
:QTableView(parent)
{
}

void ListTableView::setName(const QString &windowTitle)
{
	name = windowTitle;
}

void ListTableView::focusInEvent(QFocusEvent *event)
{
	emit hasFocus(list, sortmodel, name, this);
//	qDebug() << name;
	event->accept();
}

void ListTableView::paintEvent(QPaintEvent *event)
{
	//hier focusRect entfernen
	QTableView::paintEvent(event);
}

void ListTableView::setList(int favcolumn)
{
	sortmodel = qobject_cast<QSortFilterProxyModel *>(this->model());		

	for (int i = 0; i < this->model()->columnCount(QModelIndex()); ++i){
		
		if (!this->horizontalHeader()->isSectionHidden(i) &&
				i != favcolumn)

		list << this->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
	}
}

ListTableView::~ListTableView()
{
}
