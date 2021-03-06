/***************************************************************************
 *   Copyright (C) 2007 by Kai Winter   *
 *   kaiwinter@gmx.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mapadapter.h"
namespace qmapcontrol
{
	MapAdapter::MapAdapter(const QString& host, const QString& serverPath, int tilesize, int minZoom, int maxZoom)
	:myhost(host), serverPath(serverPath), mytilesize(tilesize), min_zoom(minZoom), max_zoom(maxZoom)
	{	
		current_zoom = min_zoom;
		loc = QLocale(QLocale::English);
	}

	MapAdapter::~MapAdapter()
	{
	}

	QString MapAdapter::host() const
	{
		return myhost;
	}

	int MapAdapter::tilesize() const
	{
		return mytilesize;
	}

	int MapAdapter::minZoom() const
	{
		return min_zoom;
	}

	int MapAdapter::maxZoom() const
	{
		return max_zoom;
	}

	int MapAdapter::currentZoom() const
	{
		return current_zoom;
	}

	int MapAdapter::adaptedZoom() const
	{
		return max_zoom < min_zoom ? min_zoom - current_zoom : current_zoom;
	}
}
