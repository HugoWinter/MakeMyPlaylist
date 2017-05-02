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
#include "proxymodel.h"

/**
* @class ProxyModel
* @brief The ProxyModel class is a custom QSortFilterProxyModel.
* lessThan method has been reimplemented to be more plateform and locale aware when sorting.
* filterAcceptsRow has been reimplemented to filter on every column.
*/


ProxyModel::ProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{

}

bool ProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0 ;
}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    for(int i =0; i<sourceModel()->columnCount();i++)
    {
        QModelIndex index =  sourceModel()->index(source_row, i, source_parent);

        if(sourceModel()->data(index).toString().contains(this->filterRegExp()))
            return true;
    }

    return false;
}


