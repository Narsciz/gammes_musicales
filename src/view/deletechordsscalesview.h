#ifndef DELETECHORDSSCALESVIEW_H
#define DELETECHORDSSCALESVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QVector>

class DeleteChordsScalesView : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *mainLayout;

    QVector<QLabel*> HSNames;
    QVector<QPushButton*> HSView;
    QVector<QPushButton*> HSDelete;

    QPushButton *returnButton;

public:
    explicit DeleteChordsScalesView(QWidget *parent = 0);

signals:

public slots:
};

#endif // DELETECHORDSSCALESVIEW_H
