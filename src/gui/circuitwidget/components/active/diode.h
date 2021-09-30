/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#ifndef DIODE_H
#define DIODE_H

#include "e-diode.h"
#include "comp2pin.h"

class LibraryItem;

class MAINMODULE_EXPORT Diode : public Comp2Pin, public eDiode
{
    public:
        Diode( QObject* parent, QString type, QString id, bool zener=false );
        ~Diode();

 static Component* construct( QObject* parent, QString type, QString id );
 static LibraryItem *libraryItem();

        virtual bool setPropStr( QString prop, QString val ) override;

        virtual void initialize() override;
        virtual void updateStep() override;

        double zenerV(){ return m_bkDown; }
        void   setZenerV( double zenerV );

        virtual QStringList getEnums( QString ) override { return m_diodes.keys(); }

        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget );

    private:
        bool m_isZener;
};

#endif
