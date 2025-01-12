/***************************************************************************
 *   Copyright (C) 2024 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#include <math.h>
//#include <QDebug>

#include "truthtable.h"
#include "testunit.h"

TruthTable::TruthTable( TestUnit* tu, QWidget* parent )
          : QDialog( parent )
{
    setupUi( this );

    m_testUnit = tu;

    m_blocked = false;
}

bool TruthTable::setup( QString inputs, QString outputs, std::vector<uint>* samples, std::vector<uint>* truthT )
{
    m_blocked = true;
    m_lastValue = "";

    QStringList inputList = inputs.split(",");
    inputList.removeAll(" ");
    int numInputs = inputList.size();
    int rows = pow( 2, numInputs );

    QStringList outputList = outputs.split(",");
    outputList.removeAll(" ");
    int numOutputs = outputList.size();

    int columns = numInputs+numOutputs+1;

    QStringList header;
    for( QString output : outputList ) header.prepend( output );
    header.prepend("");
    for( QString input : inputList ) header.prepend( input );

    table->clear();
    table->setRowCount( rows );
    table->setColumnCount( columns );
    table->setHorizontalHeaderLabels( header );
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //table->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch ); // QHeaderView::ResizeToContents

    bool testing = !(truthT->size() == 0);
    bool ok = true;

    for( int row=0; row<rows; ++row )
    {
        uint valRow = samples->at( row );
        uint truRow;
        if( testing ) truRow = truthT->at( row );

        for( int col=0; col<columns; ++col )
        {
            QTableWidgetItem* it = new QTableWidgetItem();

            if( col == numInputs ){
                it->setFlags( 0 );
                it->setBackground( QColor( 210, 210, 210 ) );
                it->setFlags( it->flags() & ~Qt::ItemIsEditable );
            }else{
                int value = 0;
                int truth = 0;

                if( col < numInputs )
                {
                    value = ( row & 1<<(numInputs-col-1));
                    it->setFlags( it->flags() & ~Qt::ItemIsEditable );
                }else{
                    int bit = 1<<(numOutputs-(col-numInputs-1)-1);
                    value = (valRow & bit);
                    if( testing ){
                        truth = (truRow & bit);
                        if( value == truth ) it->setBackground( QColor( 100, 240, 100 ) );
                        else{                it->setBackground( QColor( 255, 150,  10 ) );
                            ok = false;
                        }
                    }
                }
                QString valStr = value ? "H" : "L";
                it->setText( valStr );
                it->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
            }
            table->setItem( row, col, it );
        }
    }
    table->setColumnWidth( numInputs, 6 );
    m_blocked = false;
    return ok;
}

void TruthTable::on_saveButton_pressed()
{
    m_testUnit->save();
}

void TruthTable::on_runButton_pressed()
{
    m_testUnit->runTest();
}

void TruthTable::on_table_itemDoubleClicked( QTableWidgetItem* item )
{
    if( m_blocked ) return;

    m_lastValue = item->text();
}

void TruthTable::on_table_itemChanged( QTableWidgetItem* item )
{
    if( m_blocked ) return;

    QString text = item->text().toUpper();
    if     ( text == "0" ) text = "L";
    else if( text == "1" ) text = "H";
    else if( text != "H" && text != "L" ) text = m_lastValue;
    item->setText( text);
}
