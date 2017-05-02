/*------------------------------------------------------------------------------
-- This file is a part of the MakeMyPlaylist Software
--
-- This program is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 2 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program; if not, write to the Free Software
-- Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
-------------------------------------------------------------------------------*/
/*-- Author : Hugo Winter
-- Mail : hugo.winter31@gmail.com
----------------------------------------------------------------------------*/
#ifndef DATABASEVIEWER_H
#define DATABASEVIEWER_H

#include <QDockWidget>
#include "ui_databaseviewer.h"
#include "databaseviewermodel.h"
#include "proxymodel.h"

namespace Ui {
class dataBaseViewer;
}

class DataBaseViewer : public QDockWidget
{
public:
    explicit DataBaseViewer(QWidget *parent = 0);
    ~DataBaseViewer();

private:
    Ui::dataBaseViewer *ui;
    DataBaseViewerModel* m_model;
    ProxyModel *m_proxymodel;

    void filterHasChanged();
};

#endif // DATABASEVIEWER_H
