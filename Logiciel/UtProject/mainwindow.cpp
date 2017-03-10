#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Ut");
    this->setFixedHeight(800);
    this->setFixedWidth(1200);
    QIcon icon("./cle.png");
    this->setWindowIcon(icon);

    constructMenuBar();
    constructLayout();
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::constructMenuBar()
 {
     QMenuBar *menuBar = new QMenuBar();

     QMenu *file = menuBar->addMenu("Fichier");
     QAction *newFile = new QAction("Nouveau", menuBar);
     QAction *importFile = new QAction("Importer", menuBar);
     QAction *saveFile = new QAction("Enregistrer", menuBar);
     QAction *closeFile = new QAction("Fermer", menuBar);
     file->addAction(newFile);
     file->addAction(importFile);
     file->addAction(saveFile);
     file->addAction(closeFile);

     QMenu *chords = menuBar->addMenu("Accords");
     QAction *addChords = new QAction("Ajouter", menuBar);
     QAction *deleteChords = new QAction("Supprimer", menuBar);
     chords->addAction(addChords);
     chords->addAction(deleteChords);

     QMenu *scales = menuBar->addMenu("Gammes");
     QAction *addScales = new QAction("Ajouter", menuBar);
     QAction *deleteScales = new QAction("Supprimer", menuBar);
     scales->addAction(addScales);
     scales->addAction(deleteScales);

     QMenu *options = menuBar->addMenu("Options");

     this->setMenuBar(menuBar);
 }

  void MainWindow::constructLayout()
  {
      this->mainLayout = new QGridLayout();
      this->ui->centralWidget->setLayout(this->mainLayout);

      this->chordsLayout = new QGridLayout();
      constructChordsLayout();
      this->choicesLayout = new QGridLayout();
      constructChoicesLayout();
      this->scalesLayout = new QGridLayout();
      constructScalesLayout();

      this->mainLayout->addLayout(this->chordsLayout, 0, 0, 1, 1);
      this->mainLayout->addLayout(this->choicesLayout, 1, 0, 1, 1);
      this->mainLayout->addLayout(this->scalesLayout, 2, 0, 1, 1);
  }

  void MainWindow::constructChordsLayout()
  {
      this->clearLayout(this->chordsLayout, true);

      this->chordsLabel = new QLabel("Accords : ");
      this->cdLayout = new ChordsDisplayLayout();

      this->chordsLayout->addWidget(this->chordsLabel, 0, 0, 1, 1);
      this->chordsLayout->addLayout(this->cdLayout, 1, 0, 1, 1);
  }

  void MainWindow::constructChoicesLayout()
  {
      this->clearLayout(this->choicesLayout, true);

      this->noteComboBox = new QComboBox();
      this->hsComboBox = new QComboBox();
      this->addButton = new QPushButton("Ajouter");
      this->parametersComboBox = new QComboBox();
      this->generateButton = new QPushButton("Générer");

      this->choicesLayout->addWidget(this->noteComboBox, 0, 0, 1, 1);
      this->choicesLayout->addWidget(this->hsComboBox, 0, 1, 1, 1);
      this->choicesLayout->addWidget(this->addButton, 0, 2, 1, 1);
      this->choicesLayout->addItem(new QSpacerItem(100, 2), 0, 3, 1, 1);
      this->choicesLayout->addWidget(this->parametersComboBox, 0, 4, 1, 1);
      this->choicesLayout->addItem(new QSpacerItem(100, 2), 0, 5, 1, 1);
      this->choicesLayout->addWidget(this->generateButton, 0, 6, 1, 1);
  }

  void MainWindow::constructScalesLayout()
  {
      this->clearLayout(this->scalesLayout, true);

      this->scalesLabel = new QLabel("Gammes trouvées : ");
      this->sdLayout = new ScalesDisplayLayout();

      this->scalesLayout->addWidget(this->scalesLabel, 0, 0, 1, 1);
      this->scalesLayout->addLayout(this->sdLayout, 1, 0, 1, 1);
  }


  void MainWindow::clearLayout(QLayout *layout, bool deleteWidgets = true)
  {
      while (QLayoutItem* item = layout->takeAt(0))
      {
          if (deleteWidgets)
          {
              if (QWidget* widget = item->widget())
                  delete widget;
          }
          if (QLayout* childLayout = item->layout())
              clearLayout(childLayout, deleteWidgets);
          delete item;
      }
  }
