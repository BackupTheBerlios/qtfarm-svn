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


#ifndef QTFARM_H
#define QTFARM_H

#include <QtGui/QMainWindow>
#include <QSqlDatabase>
#include <QDir>
#include <QTabWidget>
#include <QTableView>
#include <QTreeWidget>

#include "qtfarmplugininterfaces.h"
#include "plugindialog.h"
#include "dialogpluginsettings.h"
#include "dockwidgetlist.h"
#include "widgetfilter.h"
#include "cornerwidget.h"
#include "centraltab.h"




class QtFarm : public QMainWindow
{
    Q_OBJECT

public:
    QtFarm(QWidget *parent = 0);
    ~QtFarm();
    
    QSqlDatabase db;
    WidgetFilter *filter;

protected:
    void closeEvent(QCloseEvent *event);      
    
private:
    void loadPlugin();
    void setupWidgets();
    void setupToolBar();
    void setupMenu();
    void castPlugin(QObject *plugin);
    void readPluginSettings();
    void readSettings();
    void writeSettings();
    void setupToolTree();
    void saveToolTree();
    
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *exportToolBar;
    QToolBar *newFileToolBar;
    QToolBar *filterToolBar;
    QStringList slPluginSettings;
    QStringList slAllPlugins;
    
    QMenu *soilMenu;
    QMenu *dairyMenu;
    QMenu *stockMenu;
    
    QAction *acPrint;
    QAction *acCSV;
    QAction *acNewQuery;
    QAction *acNewAction;
    QAction *acNewFolder;
    QAction *acFolderInfo;
    QAction *acDelete;
    
    QString path;    
    QDir pluginDirectory;
    QDir dbDirectory;
    QStringList pluginFileNames;
	
	QtFarmSoilInterface *qtFarmSoilInterface;
	QtFarmDairyInterface *qtFarmDairyInterface;
	QtFarmStockInterface *qtFarmStockInterface;

	QDockWidget *toolDockWidget;
    QTreeWidget *toolTree;   
    QTreeWidgetItem *listEditorItem;
    QTreeWidgetItem *actionsItem;
    QTreeWidgetItem *queriesItem;
    QTreeWidgetItem *trashItem;
    QIcon folderIcon;
    QIcon fileIcon;
    int toolTreeIndex;


    QTabWidget *centralTabWidget;
    CornerWidget *cornerWidget;    
    CentralTab *dairyTab;   
    CentralTab *soilTab;   
    CentralTab *stockTab;
    
signals:
    void statusMessage(const QString &message, int);  
    
private slots:
	void aboutPlugins();
	void setPlugins();
    void toolTreeClicked(QTreeWidgetItem *item, int);
    void newQuery();

};

#endif // QTFARM_H
