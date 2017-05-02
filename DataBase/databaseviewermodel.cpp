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

/**
* @class QLopDataBaseViewerModel
* @brief The QLopDataBaseViewerModel class is a custom table model used to display database data into a table widget.
* Like most custom models, the following basic methods are reimplemented : rowCount, columnCount, headerData and data.
*
* Note : The QxtCSVModel (https://wiki.qt.io/LibQxt_in_QtCreator) handle the CSV format better, but this implementation allow
* more format flexibility in the future.
*/

#include "databaseviewermodel.h"
#include "database.h"

/**
  * @brief Constructor.
  * @param parent Parent widget.
*/
DataBaseViewerModel::DataBaseViewerModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    beginResetModel();
    endResetModel();
}
/**
  * @brief Destructor.
*/
DataBaseViewerModel::~DataBaseViewerModel()
{

}

int DataBaseViewerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return DataBase::count();
}

int DataBaseViewerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return DataBase::getMusicAttributeNames().count();
}

QVariant DataBaseViewerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    MusicContainer* mc = DataBase::getMusicContainerByID(index.row());
    if(mc)
        return mc->getAttributes().at(index.column());

    return QVariant();
}

QVariant DataBaseViewerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
    {
        return DataBase::getMusicAttributeNames().at(section);
    }
    else
    {
        return QString("%1").arg(section);
    }
    return QVariant();
}

void DataBaseViewerModel::reset()
{
    beginResetModel();
    endResetModel();
}
