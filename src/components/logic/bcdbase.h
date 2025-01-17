/***************************************************************************
 *   Copyright (C) 2018 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#pragma once

#include "logiccomponent.h"

class BcdBase : public LogicComponent
{
    public:
        BcdBase( QString type, QString id );
        ~BcdBase();

        virtual void initialize() override;
        virtual void stamp() override;
        virtual void voltChanged() override;

        QString customChars() { return m_customChars; }
        void setCustomChars( QString chars );

    protected:
        uint8_t m_segments[17];

        uint8_t m_digit;

        QString m_customChars;
};
