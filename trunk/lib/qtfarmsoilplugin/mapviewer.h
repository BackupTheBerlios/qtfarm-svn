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

#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include <QtGui/QWidget>
#include <QScrollArea>
#include "ui_mapviewer.h"

/* Der QMapControl source soll nach "../../3dParty/QMapControl"
 * hab ich aber ohne "symbol lookup error" nicht hingekriegt
 */
#include "circlepoint.h"
#include "curve.h"
#include "geometry.h"
#include "geometrylayer.h"
#include "googlemapadapter.h"
#include "googlesatmapadapter.h"
#include "gps_position.h"
#include "imagemanager.h"
#include "imagepoint.h"
#include "layer.h"
#include "layermanager.h"
#include "linestring.h"
#include "mapadapter.h"
#include "mapcontrol.h"
#include "maplayer.h"
#include "mapnetwork.h"
#include "osmmapadapter.h"
#include "point.h"
#include "tilemapadapter.h"
#include "wmsmapadapter.h"
#include "yahoomapadapter.h"


using namespace qmapcontrol;


class MapViewer : public QWidget
{
    Q_OBJECT

public:
    MapViewer(QWidget *parent = 0);
    ~MapViewer();

private:
	MapControl* mc;
	MapControl* mc2;
	QScrollArea *sa;
	QSize initSize;
	
	void setupMaps();
	void createLayout();
	Layer* l;
	
    Ui::MapViewerClass ui;

public slots:
	void draggedRect(QRectF);
	void mouseEventCoordinate(const QMouseEvent*, const QPointF);
	void geometryClickEvent(Geometry* geom, QPoint coord_px);
	void coordinateClicked(const QMouseEvent*, const QPointF);
	void coordinateClicked_mc2(const QMouseEvent*, const QPointF);
	void buttonToggled(bool);
	void on_MoveRadioButton_toggled(bool);
	void on_ZoomRadioButton_toggled(bool);
	void on_InfoRadioButton_toggled(bool);
	void on_MiniMapCheckBox_stateChanged(int state);

	
	
signals:
	void setX(int);
	void setY(int);
	void zoomIn();
	void zoomOut();
	

	

};

#endif // MAPVIEWER_H
