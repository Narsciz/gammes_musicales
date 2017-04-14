#ifndef SCALEDISPLAY_H
#define SCALEDISPLAY_H

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QIcon>
#include <QString>

//
class ScaleDisplay : public QGroupBox
{
    Q_OBJECT

private:
    QGridLayout *boxLayout;
    QPushButton *viewButton;
    QLabel *scaleName;
public:
    ScaleDisplay(QString name);
    QString getName();
};

#endif // SCALEDISPLAY_H
