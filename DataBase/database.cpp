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
    * @class DataBase
    * @brief The DataBase class is a service.
    * As each service in this project, it is a singleton (see : https://en.wikipedia.org/wiki/Singleton_pattern for further information).
    * Its purpose is to store the music meta-data (MusicContainer instances).
    * It extracts data from a CSV file chosen by the user.
    * Warning : This CSV file must contains headers for music attributes.
*/

#include "database.h"
#include "databaseviewer.h"
#include <QFile>
#include <QTextStream>


DataBase* DataBase::m_self=Q_NULLPTR;
QDockWidget* DataBase::m_gui=Q_NULLPTR;
int  DataBase::m_pid=0;
QMap<int,MusicContainer*> *DataBase::m_dataBase = Q_NULLPTR;
QStringList DataBase::m_headers = QStringList();

/**
  * @brief Constructor.
  * @param parent Parent object for this service.
*/
DataBase::DataBase(QObject *parent) :
    MMPService(parent)
{
    m_dataBase = new QMap<int,MusicContainer*>();
}

/**
  * @brief Destructor.
*/
DataBase::~DataBase()
{
}

/**
  * @brief DataBase::m_init is where the singleton is created.
  * @param parent Parent object for this service.
*/
void DataBase::m_init(QObject *parent)
{
    if(Q_UNLIKELY(m_self==Q_NULLPTR))
        m_self=new DataBase(parent);
}

/**
  * @brief DataBase::getGUI provides MainWindow with the DataBase GUI.
*/
QDockWidget *DataBase::getGUI()
{
    m_init();

    if(m_gui==Q_NULLPTR)
    {
        m_gui=new DataBaseViewer();
        m_gui->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    }
    return m_gui;
}

DataBase *DataBase::self()
{
    m_init();
    return m_self;
}

/**
  * @brief DataBase::count returns the number of musics currently in the database.
*/
int DataBase::count()
{
    m_init();
    return m_dataBase->count();
}

/**
  * @brief DataBase::getMusicContainerByID returns the MusicContainer instance corresponding to the id requested.
  * @param id Requested music ID.
*/
MusicContainer *DataBase::getMusicContainerByID(int id)
{
    m_init();
    if(m_dataBase->contains(id))
        return m_dataBase->value(id);
    return Q_NULLPTR;
}

/**
  * @brief DataBase::getMusicAttributeNames returns the names of the music attributes.
  * These attributes depends on the input CSV file.
*/
QStringList DataBase::getMusicAttributeNames()
{
    m_init();
    return m_headers;
}


/**
  * @brief DataBase::reload reset the current database and load a new one from a CSV file.
  * @param filename CSV file name.
*/
void DataBase::reload(QString filename)
{
    m_init();

    if(!filename.isNull())
    {
        DataBase::m_dataBase->clear();
        m_pid = 0;

        QFile fileToRead(filename);
        if (!fileToRead.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&fileToRead);
        //read first line for headers
        QString line = in.readLine();
        m_headers = line.split(";");
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList tempMusicAttributes = line.split(";");
            MusicContainer *tempMC = new MusicContainer(tempMusicAttributes);
            tempMC->setID(m_pid);
            m_dataBase->insert(m_pid++, tempMC);
        }  
        emit DataBase::self()->DBChanged();
    }

}


/**
    * @class MusicContainer
    * @brief The MusicContainer class represents a music.
    * It stores music attributes.
*/

/**
  * @brief Constructor.
  * @param name
*/
MusicContainer::MusicContainer(QStringList musicAttributes)
    :m_musicAttributes(musicAttributes)
{

}


/**
  * @brief Destructor.
*/
MusicContainer::~MusicContainer()
{
}
