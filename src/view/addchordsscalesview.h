#ifndef ADDCHORDSSCALESVIEW_H
#define ADDCHORDSSCALESVIEW_H

#include <QWidget>
#include <QCheckBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <view/chordsview.h>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QStringList>
#include "modele/note.h"
#include <vector>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class AddChordsScalesView : public QWidget
{
    Q_OBJECT
private :
    bool isChord;

    QVBoxLayout *mainLayout;

    QVector<QCheckBox*> listCheckBox;

    QLabel *lineEditFullNameLabel;
    QLineEdit *fullNameLineEdit;

    QLabel *lineEditLabel;
    QLineEdit *lineEdit;

    QGroupBox *intervalleBox;
    QGridLayout *intervalleLayout;

    QCheckBox *seconde_m; // 1/2t
    QCheckBox *seconde_M; // 1t

    QCheckBox *tierce_m; // 1t+1/2t
    QCheckBox *tierce_M; // 2t ou quarte_d

    QCheckBox *quarte; // 2t+1/2t ou tierce_M
    QCheckBox *quarte_a; // 3t ou quinte_d

    QCheckBox *quinte; // 3t+1/2t

    QCheckBox *sixte_m; //4t ou quinte_a
    QCheckBox *sixte_M; //4t+1/2t

    QCheckBox *septieme_m; //5t
    QCheckBox *septieme_M; //5t+1/2t

    QLabel *fundamentalLabel;
    QComboBox *fundamentalExemple;
    ChordsView *exempleDisplay;

    vector<Note> notesList;

    QHBoxLayout *buttonLayout;
    QPushButton *createButton;
    QPushButton *returnButton;
public:
    AddChordsScalesView(bool isChord);
    Note getFundamental();
    vector<Note> getNotesList();
    Note convertIntToNote(int i);
    vector<int> getHS();
    QString getName();
    QString getAlias();

public slots:
    void checkedSlot();
    void createSlot();

signals:
    void createChordSignal(QString name, vector<int> hs);
    void createScaleSignal(QString name, vector<int> hs, QString alias);
};

#endif // ADDCHORDSSCALESVIEW_H
