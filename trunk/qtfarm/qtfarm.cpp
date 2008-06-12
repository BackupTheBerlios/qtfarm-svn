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


#include <QSqlQuery>
#include <QtGui>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QSizePolicy>

#include "qtfarm.h"


QtFarm::QtFarm(QWidget *parent)
    : QMainWindow(parent)
{
	
	QApplication::setStyle("plastique");
	setWindowTitle("QtFarm");
	
	readPluginSettings();
    
	menubar = new QMenuBar(this);
    statusbar = new QStatusBar(this);
    exportToolBar = new QToolBar(this);
    exportToolBar->setWindowTitle(tr("Export"));
    exportToolBar->setObjectName(QString::fromUtf8("tbExport"));
    newFileToolBar = new QToolBar(this);
    newFileToolBar->setWindowTitle(tr("Neu"));
    newFileToolBar->setObjectName(QString::fromUtf8("tbNewFile"));
    filterToolBar = new QToolBar(this);
    filterToolBar->setWindowTitle(tr("Filter"));
    filterToolBar->setObjectName(QString::fromUtf8("tbFilter"));
    setMenuBar(menubar);
    setStatusBar(statusbar);
    addToolBar(exportToolBar);
    addToolBar(newFileToolBar);
    addToolBar(filterToolBar);
    
    setupWidgets();
    setupToolBar();
	setCentralWidget(centralTabWidget);
	toolTreeIndex = 0;
	
    folderIcon.addPixmap(QPixmap(":/bilder/folder_open.png"),
                            QIcon::Normal, QIcon::On);
    folderIcon.addPixmap(QPixmap(":/bilder/folder.png"),
                            QIcon::Normal, QIcon::Off);
    fileIcon.addPixmap(QPixmap(":/bilder/shellscript.png"));
	
	dbDirectory = QDir(qApp->applicationDirPath());
	dbDirectory.cdUp();
	dbDirectory.cd("db");
	
	path = dbDirectory.path();
	QDir DbLib = QDir(qApp->applicationDirPath());
	DbLib.cdUp();
	DbLib.cd("lib");
	

    db = QSqlDatabase::addDatabase("QSQLITE");                                            
    db.setDatabaseName(path + "/qtfarm.sqlite3");
    
//    qDebug() << "db Path: " << path;
//    qDebug() << "DbLib.path(): " << DbLib.path();
//    qDebug() << "QLibraryInfo::PluginsPath: " << QLibraryInfo::location(QLibraryInfo::PluginsPath);
   
    if(db.open()){
	    QSqlQuery q;
	    //nur ein Test für 'ATTACH'
	    q.exec("ATTACH '" + path + "/soil.sqlite3'" + " AS soil");
	    q.exec("ATTACH '" + path + "/dairy.sqlite3'" + " AS dairy");
	    q.exec("ATTACH '" + path + "/stock.sqlite3'" + " AS stock");	    
	    q.clear();

    }else{
    	QMessageBox::information(this, tr("Datenbank"), tr("Keine Verbindung zur \n"
    			"Datenbank."));
    }
    

    loadPlugin();
    setupToolTree();
    setupMenu();
    
    connect(toolTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(toolTreeClicked(QTreeWidgetItem *, int)));
    
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
    readSettings();    
}


void QtFarm::setupMenu()
{      
    QMenu *menuExtras = new QMenu(menubar);
    menuExtras->setTitle(tr("E&xtras"));
    menubar->addAction(menuExtras->menuAction());

    QMenu *menuHelp = new QMenu(menubar);
    menuHelp->setTitle(tr("&Hilfe"));
    menubar->addAction(menuHelp->menuAction());
    
	QAction *acHelp = new QAction(this);
	acHelp->setIcon(QIcon(":/bilder/help.png"));
	acHelp->setText(tr("QtFarm Hilfe"));
	menuHelp->addAction(acHelp);	
}

void QtFarm::setupToolBar()
{	
	acPrint = new QAction(this);
	acPrint->setIcon(QIcon(":/bilder/printer22.png"));
	acPrint->setToolTip(tr("Drucken ..."));
	acPrint->setText(tr("Drucken ..."));
	exportToolBar->addAction(acPrint);
    
	acCSV = new QAction(this);
	acCSV->setIcon(QIcon(":/bilder/ooo_calc22.png"));
	acCSV->setToolTip(tr("CSV Export ..."));
	acCSV->setText(tr("CSV Export ..."));
	exportToolBar->addAction(acCSV);
	
	
	acNewQuery = new QAction(this);
	acNewQuery->setIcon(QIcon(":/bilder/empty_query22.png"));
	acNewQuery->setToolTip(tr("Neue Abfrage"));
	acNewQuery->setText(tr("Neue Abfrage"));
	newFileToolBar->addAction(acNewQuery);
	connect(acNewQuery, SIGNAL(triggered()), this, SLOT(newQuery()));
    
	acNewAction = new QAction(this);
	acNewAction->setIcon(QIcon(":/bilder/empty_action22.png"));
	acNewAction->setToolTip(tr("Neue Aktionsvorlage"));
	acNewAction->setText(tr("Neue Aktionsvorlage"));
	newFileToolBar->addAction(acNewAction);
	
	acFolderInfo = new QAction(this);
	acFolderInfo->setIcon(QIcon(":/bilder/file_info22.png"));
	acFolderInfo->setToolTip(tr("Datei Information"));
	acFolderInfo->setText(tr("Datei Information"));
	newFileToolBar->addAction(acFolderInfo);
	
	acDelete = new QAction(this);
	acDelete->setIcon(QIcon(":/bilder/file_delete22.png"));
	acDelete->setToolTip(tr("Datei Löschen"));
	acDelete->setText(tr("Datei Löschen"));
	newFileToolBar->addAction(acDelete);
	
	acNewFolder = new QAction(this);
	acNewFolder->setIcon(QIcon(":/bilder/folder22.png"));
	acNewFolder->setToolTip(tr("Neuer Ordner"));
	acNewFolder->setText(tr("Neuen Ordner"));
	newFileToolBar->addAction(acNewFolder);
	
	//damit das FileMenu als erstes Menu erscheint
	QMenu *menuFile = new QMenu(menubar);
	menuFile->setTitle(tr("&Datei"));
	menubar->addAction(menuFile->menuAction());
	
    QMenu *menuNewFile = new QMenu(menuFile);
    menuNewFile->setTitle(tr("Neu ..."));
    menuNewFile->setIcon(QIcon(":/bilder/empty.png"));
    menuNewFile->addAction(acNewQuery);
    menuNewFile->addAction(acNewAction);
    menuNewFile->addSeparator();
    menuNewFile->addAction(acNewFolder);
	
	menuFile->addMenu(menuNewFile);
    menuFile->addAction(menuNewFile->menuAction());
    menuFile->addAction(acFolderInfo);
    menuFile->addSeparator();
    menuFile->addAction(acPrint);
    menuFile->addAction(acCSV);
    
	//damit das EditMenu als zweites Menu erscheint
	QMenu *menuEdit = new QMenu(menubar);
	menuEdit->setTitle(tr("&Bearbeiten"));
	menubar->addAction(menuEdit->menuAction());
	
	QMenu *menuSettings = new QMenu(menubar);
	menuSettings->setTitle(tr("Einstellungen"));
	menuSettings->setIcon(QIcon(":/bilder/options.png"));
	menuEdit->addAction(menuSettings->menuAction());
	
    QMenu *menuPlugins = new QMenu(menuSettings);
    menuPlugins->setTitle(tr("Plugins"));
    menuPlugins->setIcon(QIcon(":/bilder/services.png"));
    menuSettings->addMenu(menuPlugins);
    menuSettings->addAction(menuPlugins->menuAction());
    
	QAction *acDia = new QAction(this);
	acDia->setIcon(QIcon(":/bilder/services_info16.png"));
	acDia->setText(tr("Plugin Informationen"));
	menuPlugins->addAction(acDia);
	connect(acDia, SIGNAL(triggered()),this, SLOT(aboutPlugins()));
	QAction *acDiaPluginSettings = new QAction(this);
	acDiaPluginSettings->setIcon(QIcon(":/bilder/services_edit16.png"));
	acDiaPluginSettings->setText(tr("Plugin Einstellungen"));
	menuPlugins->addAction(acDiaPluginSettings);
	
    QMenu *menuDB = new QMenu(menuSettings);
    menuDB->setTitle(tr("Datenbank"));
    menuDB->setIcon(QIcon(":/bilder/database16.png"));
    menuSettings->addMenu(menuDB);
    menuSettings->addAction(menuDB->menuAction());
	QAction *acDbInfo = new QAction(this);
	acDbInfo->setIcon(QIcon(":/bilder/database_info16.png"));
	acDbInfo->setText(tr("Datenbank Informationen"));
	menuDB->addAction(acDbInfo);

	QAction *acDbSettings = new QAction(this);
	acDbSettings->setIcon(QIcon(":/bilder/database_edit16.png"));
	acDbSettings->setText(tr("Datenbank Einstellungen"));
	menuDB->addAction(acDbSettings);
	connect(acDiaPluginSettings, SIGNAL(triggered()),this, SLOT(setPlugins()));        
}

void QtFarm::setupToolTree()
{
	QSqlQuery q;

	q.exec("select id, name, parent_id, type from menu order by parent_id asc");
	while(q.next()){
		if(q.value(2) == 0){
			QTreeWidgetItem *topItem = new QTreeWidgetItem(toolTree);
			topItem->setData(0, Qt::DisplayRole, q.value(1).toString());
			topItem->setData(0, Qt::UserRole+1, q.value(0).toString());
			if(q.value(3).toString() == "folder"){
				topItem->setData(0, Qt::UserRole, q.value(3).toString());
				topItem->setIcon(0, folderIcon);
				topItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			}else if(q.value(3).toString() == "file"){
				topItem->setData(0, Qt::UserRole, q.value(3).toString());
				topItem->setIcon(0, fileIcon);
				topItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsDragEnabled |  Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			}
		}else{
		     QTreeWidgetItemIterator it(toolTree);
		     while (*it) {
		         if ((*it)->data(0, Qt::UserRole+1) == q.value(2).toString()){
		 			QTreeWidgetItem *item = new QTreeWidgetItem((*it));
		 			item->setData(0, Qt::DisplayRole, q.value(1).toString());
		 			item->setData(0, Qt::UserRole+1, q.value(0).toString());
					if(q.value(3).toString() == "folder"){
						item->setData(0, Qt::UserRole, q.value(3).toString());
						item->setIcon(0, folderIcon);
						item->setFlags(Qt::ItemIsEditable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
					}else if(q.value(3).toString() == "file"){
						item->setData(0, Qt::UserRole, q.value(3).toString());
						item->setIcon(0, fileIcon);
						item->setFlags(Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
					}
		         }		             
		         	++it;		     	 
	         }
		}
	}
		

}

void QtFarm::saveToolTree()
{
	QSqlQuery q;
	QString id;
	QString parent;
	QString name;
	QString sql;

	q.exec("Begin");
    QTreeWidgetItemIterator it(toolTree);
    while (*it) {
    	if((*it)->data(0, Qt::UserRole).toString() == "folder" ||
    			(*it)->data(0, Qt::UserRole).toString() == "file"){

    	if((*it)->parent() == 0){
    		parent = "0";
    	}else{
    		parent = (*it)->parent()->data(0, Qt::UserRole+1).toString();
    	}
    		id = (*it)->data(0, Qt::UserRole+1).toString();
    		name = (*it)->data(0, Qt::DisplayRole).toString();
    	q.exec("Update menu set parent_id =" + parent 
    			+ ", name ='" + name + "' where id=" + id);
//    	qDebug() << q.lastQuery();
		     	 
    	}
    	++it;
    }
	q.exec("Commit");
}

void QtFarm::setPlugins()
{
//    qDebug()  << "slPluginSettings: " << slPluginSettings;
//    qDebug()  << "slAllPlugins: " << slAllPlugins;
	
	DialogPluginSettings dialogPluginSettings(slPluginSettings, slAllPlugins, this);
	if (dialogPluginSettings.exec() == QDialog::Accepted){
		slPluginSettings = dialogPluginSettings.getPluginSettings();
	}
	
}

void QtFarm::readPluginSettings()
{
    
	//Alle Settings in eine Klasse auslagern
	//mit QwwConfigWidget
	
	QSettings settings("QtFarm", "QtFarm1.0");
    
    settings.beginGroup("Plugins");
    
        if (settings.contains("QtFarmSoilPlugin") == true){
        	if (settings.value("QtFarmSoilPlugin") == true){
        		slPluginSettings << "*qtfarmsoilplugin*";
        	}
        }
        if (settings.contains("QtFarmDairyPlugin") == true){
        	if (settings.value("QtFarmDairyPlugin") == true){
        		slPluginSettings << "*qtfarmdairyplugin*";
        	}
        }
        if (settings.contains("QtFarmStockPlugin") == true){
        	if (settings.value("QtFarmStockPlugin") == true){
        		slPluginSettings << "*qtfarmstockplugin*";
        	}
        }

        
        if (slPluginSettings.isEmpty() == true || settings.value("showPluginDialogatStart") == true){

        	pluginDirectory = QDir(qApp->applicationDirPath());
        	pluginDirectory.cdUp();
        	pluginDirectory.cd("lib");
        	
        	slAllPlugins = pluginDirectory.entryList(QStringList() << "*qtfarm*plugin*", QDir::Files);
        	
//        	qDebug()  << "1: " << slAllPlugins;
        	
        	DialogPluginSettings dialogPluginSettings(slPluginSettings, slAllPlugins, this);
        	if (dialogPluginSettings.exec() == QDialog::Accepted){
        		slPluginSettings = dialogPluginSettings.getPluginSettings();
        	}else{
        		slPluginSettings.clear();
        	}
        }
        
        settings.endGroup();
    
//    qDebug()  << "2: " << slPluginSettings;
    
}


void QtFarm::readSettings()
{
    QSettings settings("QtFarm", "QtFarm1.0");
   
    settings.beginGroup("Session");
    QSize size = settings.value("size", QSize(500, 350)).toSize();
    resize(size);
    if (settings.contains("Layout") == true){
   	 restoreState(settings.value("Layout").toByteArray());
    }   
    settings.endGroup();
     		
}

void QtFarm::writeSettings()
{
     QSettings settings("QtFarm", "QtFarm1.0");
     
     settings.beginGroup("Session");
     settings.setValue("Layout",saveState());
     settings.setValue("Size", size());
     settings.endGroup();     		
}

void QtFarm::loadPlugin()
{

	QString fileName;
	
	pluginDirectory = QDir(qApp->applicationDirPath());
	pluginDirectory.cdUp();
	pluginDirectory.cd("lib");
	
//    qDebug() << "lib Path: " << pluginDirectory.path();
	
	if (slPluginSettings.isEmpty() == true){
		return;
	}

		foreach (fileName, pluginDirectory.entryList(slPluginSettings, QDir::Files)) {	 
	    	 QPluginLoader loader(pluginDirectory.absoluteFilePath(fileName));
	         QObject *plugin = loader.instance();
	         
//	         qDebug() << "1";
	         
	         if (plugin) {
	         	 
//	        	 qDebug() << "?" << fileName;
	        	 
	        	 castPlugin(plugin);
	             pluginFileNames += fileName;

	         }else{
	        	 
	        	 QMessageBox::information(this, tr("Plugin"), tr("Kann das Plugin nicht laden.\n")
	        			 + loader.errorString());
	         }
	     }
		
		slPluginSettings = pluginFileNames;
		
		slAllPlugins = pluginDirectory.entryList(QStringList() << "*qtfarm*plugin*", QDir::Files);
 
}

void QtFarm::castPlugin(QObject *plugin)
{
	qtFarmDairyInterface = qobject_cast<QtFarmDairyInterface *>(plugin);
	qtFarmSoilInterface = qobject_cast<QtFarmSoilInterface *>(plugin);
	qtFarmStockInterface = qobject_cast<QtFarmStockInterface *>(plugin);
	
	if(qtFarmDairyInterface){
		
		qDebug() << "qtFarmDairyInterface: OK";
		
		QMap<QtFarmDairyInterface::WidgetType, QWidget*> widgetMap = qtFarmDairyInterface->widgetMap(this);			
	    QMap<QtFarmDairyInterface::WidgetType, QWidget*>::const_iterator iWidget = widgetMap.constBegin();
	    while (iWidget != widgetMap.constEnd()) {
	        	 
	        if(iWidget.key() == QtFarmDairyInterface::Tab){
	        	dairyTab = new CentralTab(centralTabWidget);
	        	centralTabWidget->addTab(dairyTab, tr("Milchvieh"));
	        }
	        else if(iWidget.key() == QtFarmDairyInterface::Menu){
	        	dairyMenu = qobject_cast<QMenu *>(iWidget.value());
	        	if(dairyMenu)
	        		menubar->addAction(dairyMenu->menuAction());	            		 
	        }
	        else if(iWidget.key() == QtFarmDairyInterface::DockWidget){
	            //beliebige DockWidgets	 
	        }
	        else if(iWidget.key() == QtFarmDairyInterface::TabContent){
	        	//alle Contens in ein QStackedLayout/Widget packen?
	        	QWidget *tabContent = iWidget.value();
	        	dairyTab->addWidget(tabContent);
	        }
	        ++iWidget;
		}

		return;
	}
			
	if(qtFarmSoilInterface){		
		
		qDebug() << "qtFarmSoilInterface: OK";
			
		QMap<QtFarmSoilInterface::WidgetType, QWidget*> widgetMap = qtFarmSoilInterface->widgetMap(this);			
	    QMap<QtFarmSoilInterface::WidgetType, QWidget*>::const_iterator iWidget = widgetMap.constBegin();
	    while (iWidget != widgetMap.constEnd()) {
	        	 
	        if(iWidget.key() == QtFarmSoilInterface::Tab){
	        	soilTab = new CentralTab(centralTabWidget);
	        	centralTabWidget->addTab(soilTab, tr("Schlagkartei"));
	        }
	        else if(iWidget.key() == QtFarmSoilInterface::Menu){
	        	soilMenu = qobject_cast<QMenu *>(iWidget.value());
	        	if(soilMenu)
	        		menubar->addAction(soilMenu->menuAction());	            		 
	        }
	        else if(iWidget.key() == QtFarmSoilInterface::DockWidget){
	            //beliebige DockWidgets	 
	        }
	        else if(iWidget.key() == QtFarmSoilInterface::TabContent){
	        	//alle Contens in ein QStackedLayout/Widget packen?
	        	if(soilTab){
	        	QWidget *tabContent = iWidget.value();
	        	soilTab->addWidget(tabContent);
	        	}
	        }
	        ++iWidget;
		}

	    // DockWidgets mit Daten .. Maps verschachteln QMap<QString, QMap<QtFarmSoilInterface::Data, QVariant> >
	    QMap<QtFarmSoilInterface::Data, QVariant> listMap = qtFarmSoilInterface->listMap();
		DockWidgetList *dwTest = new DockWidgetList("Pflanzenschutzmittel", this);
		dwTest->init(listMap, filter);
		if(soilMenu){
			soilMenu->addAction(dwTest->toggleViewAction());
		}
				    	
		return;
	}
	
	if(qtFarmStockInterface){
		
		qDebug() << "qtFarmStockInterface: OK";
		
		QMap<QtFarmStockInterface::WidgetType, QWidget*> widgetMap = qtFarmStockInterface->widgetMap(this);			
	    QMap<QtFarmStockInterface::WidgetType, QWidget*>::const_iterator iWidget = widgetMap.constBegin();
	    while (iWidget != widgetMap.constEnd()) {
	        	 
	        if(iWidget.key() == QtFarmStockInterface::Tab){
	        	stockTab = new CentralTab(centralTabWidget);
	        	centralTabWidget->addTab(stockTab, tr("Lager"));
	        }
	        else if(iWidget.key() == QtFarmStockInterface::Menu){
	        	stockMenu = qobject_cast<QMenu *>(iWidget.value());
	        	if(stockMenu)
	        		menubar->addAction(stockMenu->menuAction());	            		 
	        }
	        else if(iWidget.key() == QtFarmStockInterface::DockWidget){
	            //beliebige DockWidgets	 
	        }
	        else if(iWidget.key() == QtFarmStockInterface::TabContent){
	        	//alle Contens in ein QStackedLayout/Widget packen?
	        	QWidget *tabContent = iWidget.value();
	        	stockTab->addWidget(tabContent);
	        }
	        ++iWidget;
		}
		
		return;
			
	}
}

void QtFarm::aboutPlugins()
{
    
	pluginDirectory = QDir(qApp->applicationDirPath());
	pluginDirectory.cdUp();
	pluginDirectory.cd("lib");
	
	PluginDialog dialog(pluginDirectory.path(), pluginFileNames, this);
    dialog.exec();
}

void QtFarm::setupWidgets()
{
    
    toolDockWidget = new QDockWidget(tr("Werkzeug"), this);
    toolDockWidget->setObjectName(QString::fromUtf8("leftW"));
    toolDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, toolDockWidget);
    
    toolTree = new QTreeWidget(toolDockWidget);
    toolTree->setAnimated(true);
    toolTree->headerItem()->setText(0, tr(""));
    toolTree->headerItem()->setIcon(0, QIcon(":/bilder/folder-home.png"));
    toolTree->setDropIndicatorShown(true);
    toolTree->setDragDropMode(QAbstractItemView::InternalMove);   
    toolTree->setExpandsOnDoubleClick(false);
    toolTree->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    toolTree->setSortingEnabled(true);
    toolTree->sortByColumn(0, Qt::AscendingOrder);
    toolDockWidget->setWidget(toolTree);
    
    centralTabWidget = new QTabWidget(this);
    cornerWidget = new CornerWidget(centralTabWidget);
    centralTabWidget->setCornerWidget(cornerWidget, Qt::TopRightCorner); 
    connect(centralTabWidget, SIGNAL(currentChanged(int)), cornerWidget, SLOT(currentTab(int)));
       

    listEditorItem = new QTreeWidgetItem(toolTree);
    listEditorItem->setIcon(0, QIcon(":/bilder/folder_txt.png"));
    listEditorItem->setText(0, tr("Listeneditor"));
    listEditorItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    listEditorItem->setData(0, Qt::UserRole+1, false);

    actionsItem = new QTreeWidgetItem(toolTree);
    actionsItem->setIcon(0, QIcon(":/bilder/folder_action16.png"));
    actionsItem->setText(0, tr("Aktionen"));
    actionsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    actionsItem->setData(0, Qt::UserRole+1, false);
    
    queriesItem = new QTreeWidgetItem(toolTree);
    queriesItem->setIcon(0, QIcon(":/bilder/folder_query16.png"));
    queriesItem->setText(0, tr("Abfragen"));
    queriesItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    queriesItem->setData(0, Qt::UserRole+1, false);
    
	trashItem = new QTreeWidgetItem(toolTree);
	trashItem->setText(0, tr("Müll"));
	trashItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled);
	trashItem->setData(0, Qt::UserRole+1, false);
	trashItem->setIcon(0, QIcon(":/bilder/edittrash.png"));
	
	filter = new WidgetFilter;
	filterToolBar->addWidget(filter);
	connect(filter, SIGNAL(statusMessage(const QString&)), statusbar, SLOT(showMessage(const QString&)));
    
}


void QtFarm::toolTreeClicked(QTreeWidgetItem *item, int)
{
	
	if(item->data(0, Qt::UserRole).toString() == "folder"){
		
	    acNewQuery->setEnabled(true);
	    acNewAction->setEnabled(true);
	    acNewFolder->setEnabled(true);
	    acFolderInfo->setDisabled(true);
	    acDelete->setEnabled(true);
		
	}else if(item->data(0, Qt::UserRole).toString() == "bookmark"){
		
	    acNewQuery->setEnabled(true);
	    acNewAction->setEnabled(true);
	    acNewFolder->setEnabled(true);
	    acFolderInfo->setEnabled(true);
	    acDelete->setEnabled(true);
		
	}else if(item->data(0, Qt::UserRole+1).toBool() == false){
		
	    acNewQuery->setEnabled(true);
	    acNewAction->setEnabled(true);
	    acNewFolder->setEnabled(true);
	    acFolderInfo->setEnabled(true);
	    acDelete->setDisabled(true);
	}		

	QList<QDockWidget *> DockWidget = this->findChildren<QDockWidget *>();
	QList<QString> names;
    for (int i = 0; i < DockWidget.size(); ++i) {
        
    	names << DockWidget.at(i)->windowTitle();
    }
//	qDebug() << names;
}


void QtFarm::newQuery()
{
	
	if(acNewQuery == QObject::sender() && toolTree->currentItem()->data(0, Qt::UserRole).toString().isEmpty() != true){
		QMessageBox::information(0, "acNewQuery", "acNewQuery");
		QTreeWidgetItem *item;
		if(toolTree->currentItem()->data(0, Qt::UserRole).toString() == "folder"){
			item = new QTreeWidgetItem(toolTree->currentItem());
		}else if(toolTree->currentItem()->data(0, Qt::UserRole).toString() == "bookmark"){
			item = new QTreeWidgetItem(toolTree->currentItem()->parent());
		}else{
			return;
		}
		
		item->setText(0, "myItem");
		item->setText(1, "myItem");
		item->setIcon(0, QIcon(":/bilder/shellscript.png"));
		item->setData(0, Qt::UserRole, "bookmark");
		
	}else{
		QMessageBox::information(0, "test", "test");
	}
		

		
//	}else if(item->data(0, Qt::UserRole).toString() == "bookmark"){
//		
//
//		
//	}else if(item->data(0, Qt::UserRole+1).toBool() == false){
//		
//
//	}	
}


void QtFarm::closeEvent(QCloseEvent *event)
{
	saveToolTree();
	writeSettings();
	event->accept();
}


QtFarm::~QtFarm()
{

}
