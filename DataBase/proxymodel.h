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
#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QRegExp>

class ProxyModel : public QSortFilterProxyModel
{
public:
    explicit ProxyModel(QObject *parent = 0);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
public slots:
    void filterHasChanged(const QString &filter);

};

#endif // PROXYMODEL_H
