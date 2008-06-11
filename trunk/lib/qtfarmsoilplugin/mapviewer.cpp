/****************************************************************************
**
** Trolltech hereby grants a license to use the Qt/Eclipse Integration
** plug-in (the software contained herein), in binary form, solely for the
** purpose of creating code to be used with Trolltech's Qt software.
**
** Qt Designer is licensed under the terms of the GNU General Public
** License versions 2.0 and 3.0 ("GPL License"). Trolltech offers users the
** right to use certain no GPL licensed software under the terms of its GPL
** Exception version 1.2 (http://trolltech.com/products/qt/gplexception).
**
** THIS SOFTWARE IS PROVIDED BY TROLLTECH AND ITS CONTRIBUTORS (IF ANY) "AS
** IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
** PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
** OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** Since we now have the GPL exception I think that the "special exception
** is no longer needed. The license text proposed above (other than the
** special exception portion of it) is the BSD license and we have added
** the BSD license as a permissible license under the exception.
**
****************************************************************************/
#include <QSpacerItem>
#include <QDebug>
#include <QSizePolicy>
#include "mapviewer.h"

MapViewer::MapViewer(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	sa = new QScrollArea;
	sa->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setupMaps();
	createLayout();

//    ui.verticalLayout->addWidget(scrollArea);
	mc->moveTo(QPointF(8.25865,50.001297));
	
	
//	QList<QPointF> startCoords;
//	startCoords.append(QPointF(55.36237, 6.90905));
//	startCoords.append(QPointF(49.96777, 17.34029));
//	mc->setViewAndZoomIn(startCoords);
	mc->setZoom(2);
	
	
	mc2->setView(QPointF(8.25865,50.001297));
	mc2->setZoom(0);
	sa->setBackgroundRole(QPalette::Window);
//	sa->show();
//	QSize initSize = QSize(650, 500);
	mc->resize(initSize);

	sa->show();
//	sa->setMaximumWidth(initSize.width()+5);
//	ui.scrollArea->setMinimumWidth(initSize.width()+5);
//	ui.scrollArea->setMinimumHeight(initSize.height()+5);
//	sa->setMaximumHeight(initSize.height()+5);
//	ui.groupBox->setHidden(false);
//	ui.groupBox->setMaximumHeight(initSize.height()+5);
//	ui.groupBox->setMaximumWidth(initSize.height()+5);
//	sa->resize(600, 600);
	resize(800, 800);
	


}


void MapViewer::setupMaps()
{
	initSize = QSize(800, 600);

	// main map control
	mc = new MapControl(initSize);
//	mc->setParent(ui.scrollArea);
//	MapAdapter* mapadapter = new WMSMapAdapter("www2.demis.nl", "/wms/wms.asp?wms=WorldMap&LAYERS=Countries,Borders,Cities,Rivers,Settlements,Hillshading,Waterbodies,Railroads,Highways,Roads&FORMAT=image/png&VERSION=1.1.1&SERVICE=WMS&REQUEST=GetMap&STYLES=&EXCEPTIONS=application/vnd.ogc.se_inimage&SRS=EPSG:4326&TRANSPARENT=FALSE", 256);
	MapAdapter* mapadapter = new OSMMapAdapter();
	// maplayer
	Layer* l = new MapLayer("Custom Layer", mapadapter);
	mc->addLayer(l);
	// Geometry layer
	Layer* l2 = new GeometryLayer("Geom Layer", mapadapter);
	mc->addLayer(l2);


	// "minimap" control
	mc2 = new MapControl(QSize(145,145)/*, MapControl::None*/);
	MapAdapter* mapadapter_mini = new OSMMapAdapter();
	Layer* layer_mini = new MapLayer("Custom Layer", mapadapter_mini);
	mc2->addLayer(layer_mini);
	mc2->setParent(mc);
	
	
//	 create points
	QPen* pen = new QPen(QColor(0, 0, 0, 0));
	pen->setWidth(5);
	QList<Point*> points;
	points.append(new CirclePoint(13.5717, 52.7625,	"Acker, Punkt 1", Point::Middle, pen));
	points.append(new CirclePoint(13.5715, 52.764,	"Acker, Punkt 2", Point::Middle, pen));
	points.append(new CirclePoint(13.5716, 52.766,	"Acker, Punkt 3", Point::Middle, pen));
	points.append(new CirclePoint(13.5781, 52.7661,	"Acker, Punkt 4", Point::Middle, pen));
	points.append(new CirclePoint(13.5785, 52.7675,	"Acker, Punkt 5", Point::Middle, pen));
	points.append(new CirclePoint(13.5818, 52.7676,	"Acker, Punkt 6", Point::Middle, pen));
	points.append(new CirclePoint(13.5836, 52.7689,	"Acker, Punkt 7", Point::Middle, pen));
	points.append(new CirclePoint(13.589, 52.7686,	"Acker, Punkt 8", Point::Middle, pen));
	points.append(new CirclePoint(13.5902, 52.7672,	"Acker, Punkt 9", Point::Middle, pen));
	points.append(new CirclePoint(13.5849, 52.7653,	"Acker, Punkt 10", Point::Middle, pen));
	points.append(new CirclePoint(13.5841, 52.7646,	"Acker, Punkt 11", Point::Middle, pen));
	points.append(new CirclePoint(13.584, 52.7636,	"Acker, Punkt 12", Point::Middle, pen));
	points.append(new CirclePoint(13.5802, 52.7633,	"Acker, Punkt 13", Point::Middle, pen));
	points.append(new CirclePoint(13.5717, 52.7625,	"Acker, Punkt 14", Point::Middle, pen));
	// add points to linestring
	pen = new QPen(QColor(215, 46, 46, 255));
	pen->setWidth(3);
	LineString* ls = new LineString(points, "Lanke", pen);
	// the linestring is added to the MapLayer l, since it doenst change its points
	l->addGeometry(ls);
	

	// this point receives position changes from the "gps modul"
//	ip = new ImagePoint(0,0, QCoreApplication::applicationDirPath() + "/images/marker1.png", "image point", Point::TopRight);

	// so if have to be added to the GeometryLayer l2
//	l2->addGeometry(ip);
//	QPushButton* pb = new QPushButton("test button", mc);

	// widget example
//	Point* wpoint = new  Point(-20,-20, pb, ".", Point::TopLeft);
//	wpoint->setBaselevel(3);
// 	l->addGeometry(wpoint);
//	pb->setGeometry(0,0,100,50);

	connect(l, SIGNAL(geometryClicked(Geometry*, QPoint)),
			  this, SLOT(geometryClickEvent(Geometry*, QPoint)));
	connect(l2, SIGNAL(geometryClicked(Geometry*, QPoint)),
			  this, SLOT(geometryClickEvent(Geometry*, QPoint)));
	connect(mc, SIGNAL(boxDragged(const QRectF)),
			  this, SLOT(draggedRect(QRectF)));
	connect(mc, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
			  this, SLOT(mouseEventCoordinate(const QMouseEvent*, const QPointF)));
	connect(mc, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
			  this, SLOT(coordinateClicked(const QMouseEvent*, const QPointF)));
	connect(mc2, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
			  this, SLOT(coordinateClicked_mc2(const QMouseEvent*, const QPointF)));
}


void MapViewer::createLayout()
{
	
	sa->setWidget(mc);
	
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Horizontal);

    splitter->addWidget(ui.toolBox);
    splitter->addWidget(sa);
	this->layout()->addWidget(splitter);
//	this->layout()->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//	this->layout()->setAlignment(ui.groupBox, Qt::AlignTop | Qt::AlignLeft);
//	ui.verticalLayout_2->addWidget(mc);

	
	connect(ui.RectRadioButton, SIGNAL(toggled( bool )),
			  this, SLOT(buttonToggled(bool)));
//	connect(ui.MoveRadioButton, SIGNAL(toggled( bool )),
//			  this, SLOT(buttonToggled(bool)));
	
	mc->setMouseMode(MapControl::Dragging);

}

//void MapViewer::coordinateClicked(const QMouseEvent* evnt, const QPointF coord)
//{
//	if (btn1->isChecked() && evnt->type()==QEvent::MouseButtonPress)
//	{
//		mc->layer("Geom Layer")->addGeometry(new CirclePoint(coord.x(), coord.y(), 10, "added point"));
//		mc->updateRequestNew();
//	}
//}

//void MapViewer::geometryClickEvent(Geometry* geom, QPoint)
//{
//	if (geom->hasClickedPoints())
//	{
//		QList<Geometry*> pp = geom->clickedPoints();
//		for (int i=0; i<pp.size(); i++)
//		{
//			QMessageBox::information(this, geom->name(), pp.at(i)->name());
//		}
//	}
//	else if (geom->GeometryType == "Point")
//	{
//		QMessageBox::information(this, geom->name(), QString("Position: ").append(QString().setNum(((Point*)geom)->longitude())).append(QString("/")).append(QString().setNum(((Point*)geom)->latitude())));
//	}
//
//}



void MapViewer::buttonToggled(bool active)
{
	if (active)
		mc->setMouseMode(MapControl::Dragging);
//	else
//		mc->setMouseMode(MapControl::Panning);
}

void MapViewer::on_MoveRadioButton_toggled(bool active)
{
	if (active)
		mc->setMouseMode(MapControl::Panning);
}

void MapViewer::on_ZoomRadioButton_toggled(bool active)
{
	if(active)
		mc->setMouseMode(MapControl::None);
		mc2->setMouseMode(MapControl::None);
}

void MapViewer::on_InfoRadioButton_toggled(bool active)
{
	if(active)
		mc->setMouseMode(MapControl::None);
		mc2->setMouseMode(MapControl::None);
}

void MapViewer::draggedRect(QRectF rect)
{
	QList<QPointF> coords;
	coords.append(rect.topLeft());
	coords.append(rect.bottomRight());
	mc->setViewAndZoomIn(coords);
}

void MapViewer::on_MiniMapCheckBox_stateChanged(int state)
{
	if(state == Qt::Unchecked)
		mc2->setHidden(true);
	else
		mc2->setVisible(true);
}

void MapViewer::mouseEventCoordinate(const QMouseEvent* evnt, const QPointF coordinate)
{
	if (evnt->type() == QEvent::MouseButtonPress && ui.MoveRadioButton->isChecked()){
		mc->moveTo(coordinate);
	}
	//update mini-window
	else if(evnt->type() == QEvent::MouseButtonRelease){
		mc2->setView(coordinate);
	}
	else if(evnt->type() == QEvent::MouseButtonPress &&
			evnt->button() == Qt::LeftButton && ui.ZoomRadioButton->isChecked()){
		mc->zoomIn();
		qDebug() << "mc zoom: " << mc->currentZoom();
		mc2->setZoom(mc->currentZoom() -3);
		qDebug() << "mc2 zoom: " << mc2->currentZoom();
	}
	else if(evnt->type() == QEvent::MouseButtonPress &&
			evnt->button() == Qt::RightButton && ui.ZoomRadioButton->isChecked()){
		mc->zoomOut();
		mc2->setZoom(mc->currentZoom() -3);
	}
}
void MapViewer::coordinateClicked_mc2(const QMouseEvent* evnt, const QPointF coordinate)
{
	if (evnt->type() == QEvent::MouseButtonPress)
	{
		mc2->moveTo(coordinate);
		mc->setView(coordinate);
	}
}



void MapViewer::coordinateClicked(const QMouseEvent* evnt, const QPointF coord)
{
	if (ui.radioButton_2->isChecked() && evnt->type()==QEvent::MouseButtonPress)
	{
		mc->layer("Geom Layer")->addGeometry(new CirclePoint(coord.x(), coord.y(), 10, "added point"));
		mc->updateRequestNew();
	}
}

void MapViewer::geometryClickEvent(Geometry* geom, QPoint)
{
	if(ui.InfoRadioButton->isChecked() == true){
	
		if (geom->hasClickedPoints())
		{
			QList<Geometry*> pp = geom->clickedPoints();
			for (int i=0; i<pp.size(); i++)
			{
				QMessageBox::information(this, geom->name(), pp.at(i)->name());
			}
		}
		else if (geom->GeometryType == "Point")
		{
			QMessageBox::information(this, geom->name(), QString("Position: ").append(QString().setNum(((Point*)geom)->longitude())).append(QString("/")).append(QString().setNum(((Point*)geom)->latitude())));
		}
	}

}

MapViewer::~MapViewer()
{

}

