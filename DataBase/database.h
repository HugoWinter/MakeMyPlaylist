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
#ifndef DATABASE_H
#define DATABASE_H

#include <mmpservice.h>
#include <QObject>

class DataBaseViewer;
class MusicContainer;

class DataBase : public MMPService
{
    Q_OBJECT
public:
    friend class DataBaseViewer;
    friend class DataBaseViewerModel;
    QDockWidget* getGUI();
    static DataBase* self();
    static int count();
    static MusicContainer *getMusicContainerByID(int id);
    static QStringList getMusicAttributeNames();

private:
    static int m_pid;
    static QDockWidget* m_gui;
    static QMap<int,MusicContainer*> *m_dataBase;
    static QStringList m_headers;
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    static DataBase* m_self;
    static void m_init(QObject *parent = 0);

public slots:
    static void reload(QString filename);
signals:
    void DBChanged();
};

class MusicContainer : public QObject
{
    Q_OBJECT
public:
    MusicContainer(QStringList musicAttributes = QStringList());
    ~MusicContainer();
    inline void setID(int id){m_id = id;}
    inline int ID(){return m_id;}
    inline QStringList getAttributes(){return m_musicAttributes;}
private:
    QStringList m_musicAttributes;
    int m_id;

};

#endif // DATABASE_H
