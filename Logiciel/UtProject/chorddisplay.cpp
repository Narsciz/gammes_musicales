#include "chorddisplay.h"

#include <iostream>

using namespace std;

ChordDisplay::ChordDisplay(QString note, QString sh) : QGroupBox()
{
    this->setFixedSize(60, 60);
    this->boxLayout = new QGridLayout();
    this->boxLayout->setMargin(0);

    QIcon icon("./close.png");
    this->closeButton = new QPushButton();
    closeButton->setIcon(icon);
    closeButton->setFixedSize(20, 20);
    this->chordName = new QLabel(note + sh);

    chordName->setFixedSize(30, 10);

    this->boxLayout->addWidget(this->closeButton, 0, 2, 1, 1);
    this->boxLayout->addItem(new QSpacerItem(20, 20), 1, 0, 1, 1);
    this->boxLayout->addWidget(this->chordName, 1, 1, 1, 1);
    this->boxLayout->addItem(new QSpacerItem(10, 10), 2, 0, 1, 1);

    this->setLayout(this->boxLayout);
}
