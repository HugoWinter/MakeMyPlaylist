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
#include "databaseviewer.h"
#include "database.h"

/**
    * @class DataBaseViewer
    * @brief The DataBaseViewer class is dedicated to the GUI of DataBase service.
*/


/**
  * @brief Constructor.
  * @param parent Parent widget.
*/
DataBaseViewer::DataBaseViewer(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::dataBaseViewer)
{
    ui->setupUi(this);
    m_model = new DataBaseViewerModel();
    m_proxymodel = new ProxyModel();
    m_proxymodel->setSourceModel(m_model);
    ui->dataBaseTableView->setModel(m_proxymodel);
    ui->dataBaseTableView->horizontalHeader()->setSectionsClickable(true);
    ui->dataBaseTableView->setSortingEnabled(true);
    connect(DataBase::self(), &DataBase::DBChanged, this->m_model, &DataBaseViewerModel::reset);
    connect(ui->filterInput, &QLineEdit::textChanged, this, &DataBaseViewer::filterHasChanged);
}

/**
  * @brief Destructor.
*/
DataBaseViewer::~DataBaseViewer()
{
    delete ui;
    delete m_model;
}

/**
  * @brief DataBaseViewer::filterHasChanged is a slot.
  * Its role is to update the filter regular expression.
*/
void DataBaseViewer::filterHasChanged()
{
    //TODO : Might be pro to add further config such as case sensitivity.
    QRegExp regExp(ui->filterInput->text());
    m_proxymodel->setFilterRegExp(regExp);
}
