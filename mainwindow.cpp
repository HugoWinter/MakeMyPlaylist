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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mmpservice.h"
#include "DataBase/database.h"
#include <QFileDialog>
#include <QDir>
#include <QLabel>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_databaseFile("")
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(this, &MainWindow::newDatabaseFileSelected, this, &MainWindow::updateStatusBar);
    connect(this, &MainWindow::newDatabaseFileSelected, DataBase::self(), &DataBase::reload);

    const QList<MMPService*>ServicesToLoad=QList<MMPService*>()
            << DataBase::self();

    foreach(MMPService *service, ServicesToLoad)
    {
        service->initialize();
        QDockWidget* wdgt=service->getGUI();
        if(wdgt)
        {
            wdgt->setAllowedAreas(Qt::AllDockWidgetAreas);
            this->addDockWidget(Qt::TopDockWidgetArea,wdgt);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString databaseFileStr = QFileDialog::getOpenFileName( this, tr("Open Database File"),  QDir::currentPath(),  tr("CSV files (*.csv)") );


    if(!databaseFileStr.isNull())
    {
        m_databaseFile = databaseFileStr;

        QFileInfo databaseFileInfo (databaseFileStr);
        m_databaseDir = databaseFileInfo.path();

        emit newDatabaseFileSelected(databaseFileStr);
    }
}

void MainWindow::updateStatusBar(QString filename)
{
    QString messageToDisplay = filename + " successfully loaded !";
    ui->statusBar->showMessage(messageToDisplay);
}
