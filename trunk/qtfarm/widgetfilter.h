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

#ifndef WIDGETFILTER_H
#define WIDGETFILTER_H

#include <QtGui/QWidget>
#include <QSortFilterProxyModel>
#include <QTableView>
#include "ui_widgetfilter.h"

class WidgetFilter : public QWidget
{
    Q_OBJECT

public:
    WidgetFilter(QWidget *parent = 0);
    ~WidgetFilter();

public slots:    
    void setCbList(QList<QString> &list, QSortFilterProxyModel *sortmodel,
    		QString &name, QTableView *_view);

signals:

    void statusMessage(const QString &message);	
    
private:
	int filterKeyColumn(int index);
	QSortFilterProxyModel *model;
	QString _name;
	QTableView *view;
    Ui::WidgetFilterClass ui;


private slots:
	void on_lineEdit_textChanged();
	void on_comboBox_currentIndexChanged(int index);

    
};

#endif // WIDGETFILTER_H
