/***************************************************************************
 *   Copyright (C) 2025 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#include "analogclock.h"
#include "simulator.h"

AnalogClock* AnalogClock::m_pSelf = nullptr;

AnalogClock::AnalogClock()
           : eElement("AnalogClock")
{
    m_pSelf = this;
    m_clkElement = nullptr;
}
AnalogClock::~AnalogClock(){}

void AnalogClock::stamp()
{
    m_period = Simulator::self()->reactStep();
    if( m_clkElement ) Simulator::self()->addEvent( m_period, this );
}

void AnalogClock::runEvent()
{
    eElement* clkElement = m_clkElement;
    while( clkElement )
    {
        clkElement->runEvent();
        clkElement = clkElement->nextEvent;
    }
    Simulator::self()->addEvent( m_period, this );
}

void AnalogClock::addClkElement( eElement* e )
{
    e->nextEvent = m_clkElement;
    m_clkElement = e;
}

void AnalogClock::remClkElement( eElement* e )
{
    eElement* clkElement = m_clkElement;
    eElement* lastElement = nullptr;
    eElement* nextElement = nullptr;

    while( clkElement )
    {
        if( clkElement == e )
        {
            nextElement = clkElement->nextEvent;
            if( lastElement ) lastElement->nextEvent = nextElement;
            else              m_clkElement = nextElement;
            clkElement->nextEvent = nullptr;
            return;
        }
        lastElement = clkElement;
        clkElement = clkElement->nextEvent;
    }
}
