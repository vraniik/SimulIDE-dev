/***************************************************************************
 *   Copyright (C) 2024 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <QDialog>

#include "ui_truthtable.h"

class TestUnit;

class TruthTable : public QDialog, private Ui::TruthTable
{
    Q_OBJECT

    public:
        TruthTable( TestUnit* tu, QWidget* parent=0 );

        bool setup( QString inputs, QString outputs, std::vector<uint>* samples, std::vector<uint>* truthT );

    public slots:
        void on_saveButton_pressed();
        void on_runButton_pressed();
        void on_table_itemChanged( QTableWidgetItem* item );
        void on_table_itemDoubleClicked( QTableWidgetItem* item );

    private:
        TestUnit* m_testUnit;

        bool m_blocked;

        QString m_lastValue;
};
#endif
