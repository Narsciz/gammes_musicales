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

    void constructNameLayout();
    void constructViewLayout();
    void constructDeleteLayout();
    void constructLayouts();

signals:

public slots:
    void openViewSlot();
    void closeViewSlot();
    void deleteSlot();
};

#endif // DELETECHORDSSCALESVIEW_H
