#ifndef SCALESDISPLAYLAYOUT_H
#define SCALESDISPLAYLAYOUT_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>

//Layout affichant les gammes générées, "hidden" avant lancement de l'algorithme, "visible" après lancement
class ScalesListDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QVBoxLayout *scalesFoundLayout;

public:
    ScalesListDisplay();
};

#endif // SCALESDISPLAYLAYOUT_H
