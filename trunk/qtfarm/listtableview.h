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

#ifndef LISTTABLEVIEW_H_
#define LISTTABLEVIEW_H_

#include <QtGui/QTableView>
#include <QList>
#include <QSortFilterProxyModel>


class ListTableView : public QTableView
{	
	Q_OBJECT
	
public:
	ListTableView(QWidget *parent = 0);
	~ListTableView();
	
	void setList(int favcolumn);
	void setName(const QString &windowTitle);
	
protected:
    void focusInEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    
private:
	QList<QString> list;
	QSortFilterProxyModel *sortmodel;
	QString name;

   
signals:
	void hasFocus(QList<QString> &list, QSortFilterProxyModel *sortmodel,
			QString &name, QTableView *_view);
	

};

#endif /*LISTTABLEVIEW_H_*/
