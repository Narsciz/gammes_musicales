#include "chorddisplay.h"

#include <iostream>

using namespace std;

ChordDisplay::ChordDisplay(QString note, QString sh) : QGroupBox()
{
    this->setFixedSize(60, 60);
    this->boxLayout = new QGridLayout();
    this->boxLayout->setMargin(0);
    this->boxLayout->setSpacing(0);
    this->boxLayout->setAlignment(Qt::AlignTop);

    QIcon iconDelete("./delete.png");
    this->deleteButton = new QPushButton();
    this->deleteButton->setIcon(iconDelete);
    this->deleteButton->setFixedSize(20, 20);
    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteButton()));

    QIcon iconView("./view.png");
    this->viewButton = new QPushButton();
    this->viewButton->setIcon(iconView);
    this->viewButton->setFixedSize(20, 20);

    this->chordName = new QLabel(note + sh);
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

void ChordDisplay::slotDeleteButton()
{
    emit this->deleteSignal(this);
    delete this;
}
