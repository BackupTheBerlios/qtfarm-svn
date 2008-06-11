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


#ifndef QTFARMSTOCKPLUGIN_H_
#define QTFARMSTOCKPLUGIN_H_

#include <QObject>
#include <QAction>
#include <QMap>

#include "qtfarmplugininterfaces.h"


class QtFarmStockPlugin : public QObject, QtFarmStockInterface
{
    Q_OBJECT
    Q_INTERFACES(QtFarmStockInterface)

public:
    QStringList features() const;    
    QMap<QtFarmStockInterface::Data, QVariant> listMap();
    QMap<enum WidgetType, QWidget*> widgetMap(QWidget *parent = 0);

};

#endif /*QTFARMSTOCKPLUGIN_H_*/
