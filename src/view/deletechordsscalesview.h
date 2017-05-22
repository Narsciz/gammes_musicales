#ifndef DELETECHORDSSCALESVIEW_H
#define DELETECHORDSSCALESVIEW_H

//Bibliotheques Qt
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>

//Classes
#include <modele/chord.h>
#include <modele/chorddictionary.h>
#include <modele/hschord.h>
#include <modele/hsscale.h>
#include <modele/scale.h>
#include <modele/scaledictionary.h>
#include <view/chordsview.h>

//fenêtre permettant de supprimer des accords personnalisés si le constructeur est appelé avec true, et des gammes si le constructeur appelé avec false
class DeleteChordsScalesView : public QWidget
{
    Q_OBJECT
private:
    bool isChord;

    QGridLayout *mainLayout;

    QVBoxLayout *namesLayout;
    QVector<QLabel*> HSNames;
    QVector<QString> ScaleName;

    QVBoxLayout *viewLayout;
    QVector<QPushButton*> HSView;

    QVBoxLayout *deleteLayout;
    QVector<QPushButton*> HSDelete;

    QPushButton *returnButton;

    ChordsView *chordView;

public:
    //Constructeur
    DeleteChordsScalesView(bool isChord, QWidget *parent = 0);
    void constructNameLayout();
    void constructViewLayout();
    void constructDeleteLayout();
    void constructLayouts();

    //Méthode
    void clearLayout(QLayout *layout, bool deleteWidgets);

public slots:
    void openViewSlot();
    void closeViewSlot();
    void deleteSlot();

signals:
    void deleteScaleSignal(HSScale* hs);
    void deleteChordSignal(HSChord* hs);
};

#endif // DELETECHORDSSCALESVIEW_H
