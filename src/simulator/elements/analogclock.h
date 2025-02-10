/***************************************************************************
 *   Copyright (C) 2025 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#pragma once

#include "e-element.h"

class AnalogClock : public eElement
{
    public:
        AnalogClock();
        ~AnalogClock();

        void stamp() override;
        void runEvent() override;

        void addClkElement( eElement* e );
        void remClkElement( eElement* e );

 static AnalogClock* self() { return m_pSelf; }

    private:
        uint64_t m_period; // in ps

        eElement* m_clkElement;

 static AnalogClock* m_pSelf;
};
