#include "scaleslistdisplay.h"

ScalesListDisplay::ScalesListDisplay() : QGroupBox()
{
    this->setTitle("Gammes trouvées : ");
    this->scalesFoundLayout = new QVBoxLayout();
    this->setLayout(this->scalesFoundLayout);
}
