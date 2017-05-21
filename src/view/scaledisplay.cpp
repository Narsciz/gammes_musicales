#include "scaledisplay.h"

ScaleDisplay::ScaleDisplay(QString name)
    : QGroupBox()
{
    this->setFixedSize(60, 60);
    this->boxLayout = new QGridLayout();
    this->boxLayout->setMargin(0);
    this->boxLayout->setSpacing(0);
    this->boxLayout->setAlignment(Qt::AlignTop);

    QIcon iconView("../assets/pictures/view.png");
    this->viewButton = new QPushButton();
    this->viewButton->setIcon(iconView);
    this->viewButton->setFixedSize(20, 20);
    QObject::connect(this->viewButton, SIGNAL(pressed()), this, SLOT(slotOpenView()));
    QObject::connect(this->viewButton, SIGNAL(released()), this, SLOT(slotCloseView()));

    this->scaleName = new QLabel(name);
    this->scaleName->setFixedSize(58, 37);
    QFont f("Arial", 10, QFont::Bold);
    this->scaleName->setFont(f);
    this->scaleName->setAlignment(Qt::AlignCenter);

    this->boxLayout->addWidget(this->viewButton, 0, 0, 1, 1);
    this->boxLayout->addWidget(this->scaleName, 1, 0, 1, 3);

    this->setLayout(this->boxLayout);
}

QString ScaleDisplay::getName()
{
    return this->scaleName->text();
}

QString ScaleDisplay::getAlias()
{
    return this->scaleAlias->text();
}

void ScaleDisplay::slotOpenView()
{
    scaleView = new ChordsView(scaleName->text(), false);
    scaleView->show();
}
void ScaleDisplay::slotCloseView()
{
    scaleView->close();
}
