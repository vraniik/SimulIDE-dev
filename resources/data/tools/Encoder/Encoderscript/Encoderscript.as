
// PinModes: undef_mode=0, input, openCo, output, source

IoPort@  outputPort = component.getPort("PORTA");

uint m_value;
bool m_isHex;
bool m_changed;

void setup()
{
    //print("ENCODER_script init");
    m_value = 0;
    m_isHex = true;
}

void reset()
{
    //print("resetting ENCODER_script"); 
    
    outputPort.setPinMode( 3 );  // Output
    outputPort.setOutState( m_value ); 
}

void updateStep()
{
    if( !m_changed ) return;
    m_changed = false;
    
    outputPort.setOutState( m_value );
}

void setLinkedValue( double val, int i )
{
    // val = 0 to 
    m_value = uint(val);
    m_changed = true;
    //print("ENCODER_script setLinkedValue "+val);
}

void setHEX( bool s )
{
    if( m_isHex == s ) return;
    m_isHex = s;
    
    uint bits = m_isHex ? 16 : 10;
    
    string stepsStr = formatUInt( bits );
    component.setPropStr( 0, "Steps", stepsStr );
    
    string maxValStr = formatUInt( bits-1 );
    component.setPropStr( 0, "Max_Val", maxValStr );

    if( s ) component.setLinkedString( 1, "15", 0 );
    else    component.setLinkedString( 1, "09", 0 );
}

bool getHEX()
{
    return m_isHex;
}

void setValue( uint v )
{
    m_value = v;
    
    string valueStr = formatUInt( m_value );
    component.setPropStr( 0, "Value", valueStr );
    
    m_changed = true;
    //print("ENCODER_script setValue "+v);
}

uint getValue()
{
    //print("ENCODER_script getValue "+m_value);
    return m_value;
}
