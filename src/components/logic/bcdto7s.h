/***************************************************************************
 *   Copyright (C) 2018 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef BCDTO7S_H
#define BCDTO7S_H

#include "bcdbase.h"

class LibraryItem;

class BcdTo7S : public BcdBase
{
    public:
        BcdTo7S( QString type, QString id );
        ~BcdTo7S();

 static Component* construct( QString type, QString id );
 static LibraryItem* libraryItem();

        virtual void stamp() override;
        virtual void updateStep() override;
        virtual void voltChanged() override;
        virtual void runEvent() override { IoComponent::runOutputs(); }

        bool pinReset() { return m_useReset; }
        void setPinReset( bool r );

        bool resetInv() { return m_resetInv; }
        void setResetInv( bool inv );

    private:

        bool m_useReset;
        bool m_resetInv;

        IoPin* m_resetPin;
};

#endif
