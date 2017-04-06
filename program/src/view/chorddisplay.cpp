#include "chorddisplay.h"

#include <iostream>

using namespace std;

ChordDisplay::ChordDisplay(QString note, QString hs) : QGroupBox()
{
    this->setFixedSize(60, 60);
    this->boxLayout = new QGridLayout();
    this->boxLayout->setMargin(0);
    this->boxLayout->setSpacing(0);
    this->boxLayout->setAlignment(Qt::AlignTop);

    QIcon iconDelete("../assets/pictures/delete.png");
    this->deleteButton = new QPushButton();
    this->deleteButton->setIcon(iconDelete);
    this->deleteButton->setFixedSize(20, 20);
    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteButton()));

    QIcon iconView("../assets/pictures/view.png");
    this->viewButton = new QPushButton();
    this->viewButton->setIcon(iconView);
    this->viewButton->setFixedSize(20, 20);
    //QObject::connect(this->viewButton, SIGNAL(pressed()), this, SLOT(slotOpenView()));
    //QObject::connect(this->viewButton, SIGNAL(released()), this, SLOT(slotCloseView()));

    this->note = note;
    this->hs = hs;
    this->chordName = new QLabel(note + ":" + hs);
    this->chordName->setFixedSize(58, 37);
    QFont f( "Arial", 10, QFont::Bold);
    this->chordName->setFont(f);
    this->chordName->setAlignment(Qt::AlignCenter);

    this->boxLayout->addWidget(this->viewButton, 0, 0, 1, 1);
    this->boxLayout->addWidget(this->deleteButton, 0, 2, 1, 1);
    this->boxLayout->addWidget(this->chordName, 1, 0, 1, 3);

    this->setLayout(this->boxLayout);
}

ChordDisplay::ChordDisplay(QString chord) : QGroupBox()
{
    this->setFixedSize(60, 60);
    this->boxLayout = new QGridLayout();
    this->boxLayout->setMargin(0);
    this->boxLayout->setSpacing(0);
    this->boxLayout->setAlignment(Qt::AlignTop);

    QIcon iconDelete("../assets/pictures/delete.png");
    this->deleteButton = new QPushButton();
    this->deleteButton->setIcon(iconDelete);
    this->deleteButton->setFixedSize(20, 20);
    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteButton()));

    QIcon iconView("../assets/pictures/view.png");
    this->viewButton = new QPushButton();
    this->viewButton->setIcon(iconView);
    this->viewButton->setFixedSize(20, 20);
    //QObject::connect(this->viewButton, SIGNAL(pressed()), this, SLOT(slotOpenView()));
    //QObject::connect(this->viewButton, SIGNAL(released()), this, SLOT(slotCloseView()));

    this->note = chord[0];
    this->hs = chord.right(chord.size()-2);
    this->chordName = new QLabel(note + hs);
    this->chordName->setFixedSize(58, 37);
    QFont f( "Arial", 10, QFont::Bold);
    this->chordName->setFont(f);
    this->chordName->setAlignment(Qt::AlignCenter);

    this->boxLayout->addWidget(this->viewButton, 0, 0, 1, 1);
    this->boxLayout->addWidget(this->deleteButton, 0, 2, 1, 1);
    this->boxLayout->addWidget(this->chordName, 1, 0, 1, 3);

    this->setLayout(this->boxLayout);
}

void ChordDisplay::disableDelete()
{
    this->deleteButton->setVisible(false);
}

void ChordDisplay::enableDelete()
{
    this->deleteButton->setVisible(true);
}

QString ChordDisplay::getName()
{
    return this->chordName->text();
}

void ChordDisplay::slotDeleteButton()
{
    emit this->deleteSignal(this);
    delete this;
}

void ChordDisplay::slotOpenView()
{
    //this->view->show();
}
void ChordDisplay::slotCloseView()
{
    //this->view->close();
}
