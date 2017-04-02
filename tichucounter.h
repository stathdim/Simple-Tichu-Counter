#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

#include <QSpinBox>
#include <QKeyEvent>

class SpinBox : public QSpinBox
{
public:
    SpinBox(QWidget *parent = 0) : QSpinBox(parent) { }

protected:
    // reimplement keyPressEvent
    void keyPressEvent(QKeyEvent *event)
    {
          event->ignore();
    }
};

class TichuCounter : public QWidget
{
    Q_OBJECT

public:
    TichuCounter(QWidget *parent = 0);

private slots:
    void onTichu(int n);
    void onGrandTichu(int n);
    void onSubmit();
    void onOpen();
    void onSave();
    void onEnaDio(int n);

private:
    SpinBox *box1;
    SpinBox *box2;
    QLabel *points1;
    QLabel *points2;
    int isTichu1;
    int isGTichu1;
    QLabel *tichuBonus1;
    QLabel *grandTichuBonus1;
    int isTichu2;
    int isGTichu2;
    QLabel *tichuBonus2;
    QLabel *grandTichuBonus2;
    int tempPoints1;
    int tempPoints2;
    void nullify();
};
