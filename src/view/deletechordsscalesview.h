#ifndef DELETECHORDSSCALESVIEW_H
#define DELETECHORDSSCALESVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <QVBoxLayout>
#include <modele/scaledictionary.h>
#include <modele/chorddictionary.h>
#include <view/chordsview.h>
#include <modele/chord.h>
#include <modele/scale.h>
#include <modele/hschord.h>
#include <modele/hsscale.h>

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
    DeleteChordsScalesView(bool isChord, QWidget *parent = 0);

    void clearLayout(QLayout *layout, bool deleteWidgets);
    void constructNameLayout();
    void constructViewLayout();
    void constructDeleteLayout();
    void constructLayouts();

public slots:
    void openViewSlot();
    void closeViewSlot();
    void deleteSlot();

signals:
    void deleteScaleSignal(HSScale* hs);
    void deleteChordSignal(HSChord* hs);
};

#endif // DELETECHORDSSCALESVIEW_H
