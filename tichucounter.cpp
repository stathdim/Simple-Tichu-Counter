#include "tichucounter.h"
#include <QGridLayout>
#include <QFont>
#include <QSpinBox>
#include <QPushButton>
#include <QSignalMapper>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVector>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QIcon>

TichuCounter::TichuCounter(QWidget *parent) : QWidget(parent)
{
    //create menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("&File");
    //add open file action
    QAction *openFileMenu = new QAction(tr("&Open"), this);
    openFileMenu->setCheckable(true);
    fileMenu->addAction(openFileMenu);
    connect(openFileMenu, SIGNAL(triggered()), this, SLOT(onOpen()));
    //add save file action
    QAction *saveFileMenu = new QAction(tr("&Save"), this);
    saveFileMenu->setCheckable(true);
    fileMenu->addAction(saveFileMenu);
    connect(saveFileMenu, SIGNAL(triggered()), this, SLOT(onSave()));;
    //add close actio
    QAction *exitMenu = new QAction(tr("&Close"), this);
    fileMenu->addAction(exitMenu);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(close()));

    //create toolbar
    QPixmap openpix("open.png");
    QPixmap savepix("save.png");
    QPixmap quitpix("quit.png");
    QToolBar *toolbar = new QToolBar(this);
    QAction *saveBar = toolbar->addAction(QIcon(savepix), "Save File");
    QAction *openBar = toolbar->addAction(QIcon(openpix), "Open File");
    toolbar->addSeparator();
    QAction *quitBar = toolbar->addAction(QIcon(quitpix), "Quit Application");
    connect(openBar, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(saveBar, SIGNAL(triggered()), this, SLOT(onSave()));
    connect(quitBar, SIGNAL(triggered()), this, SLOT(close()));


    //create the two teams' labels
    QLabel *teamA = new QLabel("Team A", this);
    QLabel *teamB = new QLabel("Team B", this);

    //change team label font
     QFont f("Arial", 12, QFont::Bold);
    teamA->setFont(f);
    teamB->setFont(f);
    //align team label
    teamA->setAlignment(Qt::AlignHCenter);
    teamB->setAlignment(Qt::AlignHCenter);

    //initialize points
    points1 = new QLabel("0", this);
    points2 = new QLabel("0", this);

    //align team points
    points1->setAlignment(Qt::AlignHCenter);
    points2->setAlignment(Qt::AlignHCenter);

    //change points label font
    points1->setFont(f);
    points2->setFont(f);

    //create two spinboxes for point input
    box1 = new SpinBox(this);
    box1->setRange(-25, 125);
    box1->setSingleStep(5);
    box2 = new SpinBox(this);
    box2->setRange(-25, 125);
    box2->setSingleStep(5);
    //create Tichu and Grand Tichu buttons
    QPushButton *tichu1 = new QPushButton("Tichu", this);
    QPushButton *tichu2 = new QPushButton("Tichu", this);
    QPushButton *gTichu1 = new QPushButton("Grand Tichu", this);
    QPushButton *gTichu2 = new QPushButton("Grand Tichu", this);


    //initialize Tichu and Grand Tichu labels
    isTichu1 = 0;
    tichuBonus1 = new QLabel("0", this);
    isTichu2 = 0;
    tichuBonus2 = new QLabel("0", this);
    isGTichu1 = 0;
    isGTichu2 = 0;
    grandTichuBonus1 = new QLabel("0", this);
    grandTichuBonus2 = new QLabel("0", this);



    //create Sumbit button
    QPushButton *submit = new QPushButton("Submit", this);
    connect(submit, SIGNAL(clicked()), this, SLOT(onSubmit()));

    //map the two tichu button to ids and connect them to the the onTichu method
    QSignalMapper *mapper = new QSignalMapper() ;
    mapper->setMapping(tichu1, 1);
    mapper->setMapping(tichu2, 2);
    connect(tichu1, SIGNAL(clicked()), mapper, SLOT(map()));
    connect(tichu2, SIGNAL(clicked()), mapper, SLOT(map()));
    connect( mapper, SIGNAL(mapped(int)), this, SLOT(onTichu(int)) ) ;

    //map the two Grand Tichu button to ids and connect them to the the onGrandTichu method
    QSignalMapper *grandmapper = new QSignalMapper() ;
    grandmapper->setMapping(gTichu1, 1);
    grandmapper->setMapping(gTichu2, 2);
    connect(gTichu1, SIGNAL(clicked()), grandmapper, SLOT(map()));
    connect(gTichu2, SIGNAL(clicked()), grandmapper, SLOT(map()));
    connect(grandmapper, SIGNAL(mapped(int)), this, SLOT(onGrandTichu(int))) ;

    //create two Ena Dyo Buttons and connect them to the enaDyo method after mapping them
    QPushButton *oneTwo1 = new QPushButton("1-2", this);
    QPushButton *oneTwo2 = new QPushButton("1-2", this);
    QSignalMapper *edmapper = new QSignalMapper();
    edmapper->setMapping(oneTwo1, 1);
    edmapper->setMapping(oneTwo2, 2);
    connect(oneTwo1, SIGNAL(clicked()), edmapper, SLOT(map()));
    connect(oneTwo2, SIGNAL(clicked()), edmapper, SLOT(map()));
    connect(edmapper, SIGNAL(mapped(int)), this, SLOT(onEnaDio(int)));


    //Create a grid layout
    QGridLayout *grid = new QGridLayout(this);
    grid->setAlignment(Qt::AlignHCenter);
    grid->setAlignment(Qt::AlignVCenter);
    grid->addWidget(menuBar, 0, 0);
    grid->addWidget(toolbar, 1, 0);
    grid->addWidget(teamA, 2, 0);
    grid->addWidget(teamB, 2, 2);
    grid->addWidget(points1, 2, 1);
    grid->addWidget(points2, 2, 3);
    grid->addWidget(box1, 3, 0);
    grid->addWidget(box2, 3, 2);
    grid->addWidget(tichu1, 4, 0);
    grid->addWidget(tichuBonus1, 4, 1);
    grid->addWidget(tichu2, 4, 2);
    grid->addWidget(tichuBonus2, 4, 3);
    grid->addWidget(gTichu1, 5, 0);
    grid->addWidget(grandTichuBonus1, 5, 1);
    grid->addWidget(gTichu2, 5, 2);
    grid->addWidget(grandTichuBonus2, 5, 3);
    grid->addWidget(oneTwo1, 6, 0);
    grid->addWidget(oneTwo2, 6, 2);
    grid->addWidget(submit, 7, 1);

    setLayout(grid);


}

void TichuCounter::onTichu(int n)
{

    if (n == 1)
    {
        if (isTichu1 == 0)
        {
            isTichu1++;
            tichuBonus1->setText("100");
        }
        else if (isTichu1 == 1)
        {
            isTichu1++;
            tichuBonus1->setText("-100");
        }
        else
        {
            isTichu1 = 0;
            tichuBonus1->setText("0");
        }
    }
    else if (n == 2)
    {
        if (isTichu2 == 0)
        {
            isTichu2++;
            tichuBonus2->setText("100");
        }
        else if (isTichu2 == 1)
        {
            isTichu2++;
            tichuBonus2->setText("-100");
        }
        else
        {
            isTichu2 = 0;
            tichuBonus2->setText("0");
        }
    }

}

void TichuCounter::onGrandTichu(int n)
{
    if (n == 1)
    {
        if (isGTichu1 == 0)
        {
            isGTichu1++;
            grandTichuBonus1->setText("200");
        }
        else if (isGTichu1 == 1)
        {
            isGTichu1++;
            grandTichuBonus1->setText("-200");
        }
        else
        {
            isGTichu1 = 0;
            grandTichuBonus1->setText("0");
        }
    }
    else
    {
        if (isGTichu2 == 0)
        {
            isGTichu2++;
            grandTichuBonus2->setText("200");
        }
        else if (isGTichu2 == 1)
        {
            isGTichu2++;
            grandTichuBonus2->setText("-200");
        }
        else
        {
            isGTichu2 = 0;
            grandTichuBonus2->setText("0");
        }
    }

}

void TichuCounter::onSubmit()
{
    tempPoints1 = box1->value();
    tempPoints2 = box2->value();
    box1->setValue(0);
    box2->setValue(0);
    if (isTichu1 == 1)
    {
        tempPoints1 += 100;
    }
    else if (isTichu1 == 2)
    {
        tempPoints1 -= 100;
    }
    if (isGTichu1 == 1)
    {
        tempPoints1 += 200;
    }
    else if (isGTichu1 == 2)
    {
        tempPoints1 -= 200;
    }
    int val = points1->text().toInt();
    val += tempPoints1;
    points1->setText(QString::number(val));

    if (isTichu2 == 1)
    {
        tempPoints2 += 100;
    }
    else if (isTichu2 == 2)
    {
        tempPoints2 -= 100;
    }
    if (isGTichu2 == 1)
    {
        tempPoints2 += 200;
    }
    else if (isGTichu2 == 2)
    {
        tempPoints2 -= 200;
    }
    val = points2->text().toInt();
    val += tempPoints2;
    points2->setText(QString::number(val));

    nullify();

}

void TichuCounter::onOpen()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Text File (*.txt)");
    QFile fin(filename);
    if(!fin.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", fin.errorString());
    }
    else
    {
        //we use a QVector instead of two QString in order to achieve easier feature adition (e.g. Points at the current round)
        QVector<QString> stringVector;
        //read data from file
        while(!fin.atEnd())
        {
           stringVector.append(fin.readLine());
        }
        //set points
        points1->setText(stringVector[0]);
        points2->setText(stringVector[1]);
    }

    fin.close();
}

void TichuCounter::onSave()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "C://", "Text File (*.txt)");
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QTextStream out(&f);
    //we use a QVector instead of two QString in order to achieve easier feature adition (e.g. Points at the current round)
    QVector<QString> stringVector;

    //convert QLabels to QStrings and add them to stringVector
    stringVector.append(points1->text());
    stringVector.append(points2->text());
    //write data to file
    for (int i = 0; i < stringVector.size(); i++)
    {
        out << stringVector[i] << endl;
    }
    out << filename << endl;
    if(!f.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(0, "error", f.errorString());
    }

    f.close();

}

void TichuCounter::onEnaDio(int n)
{
    if (n == 1)
    {
        int tempPoints1 = 0;
        if (isTichu1 == 1)
        {
            tempPoints1 += 100;
        }
        else if (isTichu1 == 2)
        {
            tempPoints1 -= 100;
        }
        if (isGTichu1 == 1)
        {
            tempPoints1 += 200;
        }
        else if (isGTichu1 == 2)
        {
            tempPoints1 -= 200;
        }
        int val = points1->text().toInt();
        val += tempPoints1 + 200;
        points1->setText(QString::number(val));
    }
    else if (n == 2)
    {
        int tempPoints2 = 0;
        if (isTichu2 == 1)
        {
            tempPoints2 += 100;
        }
        else if (isTichu2 == 2)
        {
            tempPoints2 -= 100;
        }
        if (isGTichu2 == 1)
        {
            tempPoints2 += 200;
        }
        else if (isGTichu2 == 2)
        {
            tempPoints2 -= 200;
        }
        int val = points2->text().toInt();
        val += tempPoints2 + 200;
        points2->setText(QString::number(val));
    }
    nullify();
}

void TichuCounter::nullify()
{
    isTichu1 = 0;
    isGTichu1 = 0;
    tichuBonus1->setText("0");
    grandTichuBonus1->setText("0");
    isTichu2 = 0;
    isGTichu2 = 0;
    tichuBonus2->setText("0");
    grandTichuBonus2->setText("0");
    tempPoints2 = 0;
    tempPoints1 = 0;
}
