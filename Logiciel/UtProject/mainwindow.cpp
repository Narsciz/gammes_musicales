#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Ut");
    //this->setFixedHeight(800);
    //this->setFixedWidth(1200);
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
      this->choicesDisplay = new QGroupBox();
      this->choicesLayout = new QGridLayout();
      this->choicesDisplay->setLayout(choicesLayout);
      constructChoicesLayout();
      this->scalesLayout = new QGridLayout();
      constructScalesLayout();

      this->returnButton = new QPushButton("Retour");
      QObject::connect(this->returnButton, SIGNAL(clicked()), this, SLOT(slotReturnButton()));
      this->returnButton->setVisible(false);

      this->mainLayout->addLayout(this->chordsLayout, 0, 0, 1, 1);
      this->mainLayout->addWidget(this->choicesDisplay, 1, 0, 1, 1);
      this->mainLayout->addLayout(this->scalesLayout, 2, 0, 1, 1);
      this->mainLayout->addWidget(this->returnButton, 3, 0, 1, 1);
  }

  void MainWindow::constructChordsLayout()
  {
      this->clearLayout(this->chordsLayout, true);

      this->cListDisplay = new ChordsListDisplay();
      this->reinitializeButton = new QPushButton("Réinitialiser");
      QObject::connect(this->reinitializeButton, SIGNAL(clicked()), this, SLOT(slotReinitializeButton()));

      this->chordsLayout->addWidget(this->cListDisplay, 0, 0, 1, 6);
      this->chordsLayout->addWidget(this->reinitializeButton, 0, 6, 1, 1);
  }

  void MainWindow::constructChoicesLayout()
  {
      this->clearLayout(this->choicesLayout, true);

      this->choicesDisplay->setFixedHeight(70);

      this->noteLabel = new QLabel("Fondamentale");
      this->noteLabel->setAlignment(Qt::AlignCenter);
      this->hsLabel = new QLabel("Structure harmonique");
      this->hsLabel->setAlignment(Qt::AlignCenter);
      this->parametersLabel = new QLabel("Paramètre");
      this->parametersLabel->setAlignment(Qt::AlignCenter);
      this->noteComboBox = new QComboBox();
      this->noteComboBox->addItem("C");
      this->noteComboBox->addItem("C#");
      this->noteComboBox->addItem("D");
      this->noteComboBox->addItem("D#");
      this->noteComboBox->addItem("E");
      this->noteComboBox->addItem("F");
      this->noteComboBox->addItem("F#");
      this->noteComboBox->addItem("G");
      this->noteComboBox->addItem("G#");
      this->noteComboBox->addItem("A");
      this->noteComboBox->addItem("A#");
      this->noteComboBox->addItem("B");
      this->hsComboBox = new QComboBox();
      this->hsComboBox->addItem("M");
      this->hsComboBox->addItem("m");
      this->hsComboBox->addItem("+");
      this->hsComboBox->addItem("-");
      this->addButton = new QPushButton("Ajouter", this);
      QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(slotAddButton()));
      this->parametersComboBox = new QComboBox();
      this->parametersComboBox->addItem("- de gammes");
      this->parametersComboBox->addItem("- de notes");
      this->generateButton = new QPushButton("Générer");
      QObject::connect(this->generateButton, SIGNAL(clicked()), this, SLOT(slotGenerateButton()));

      this->choicesLayout->addWidget(this->noteLabel, 0, 0, 1, 1);
      this->choicesLayout->addWidget(this->hsLabel, 0, 1, 1, 1);
      this->choicesLayout->addWidget(this->parametersLabel, 0, 4, 1, 1);
      this->choicesLayout->addWidget(this->noteComboBox, 1, 0, 1, 1);
      this->choicesLayout->addWidget(this->hsComboBox, 1, 1, 1, 1);
      this->choicesLayout->addWidget(this->addButton, 1, 2, 1, 1);
      this->choicesLayout->addWidget(new QLabel(), 1, 3, 1, 1);
      this->choicesLayout->addWidget(this->parametersComboBox, 1, 4, 1, 1);
      this->choicesLayout->addWidget(new QLabel(), 1, 5, 1, 1);
      this->choicesLayout->addWidget(this->generateButton, 1, 6, 1, 1);
 }

  void MainWindow::constructScalesLayout()
  {
      this->clearLayout(this->scalesLayout, true);

      this->sListDisplay = new ScalesListDisplay();

      this->scalesLayout->addWidget(this->sListDisplay, 0, 0, 1, 1);

      this->sListDisplay->setVisible(false);
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

  void MainWindow::slotAddButton() //Ajoute lors de l'appuie sur le bouton "Ajouter", les choix d'accords courant au layout d'accords
  {
      this->cListDisplay->addChord(this->noteComboBox->currentText(), this->hsComboBox->currentText());
  }

  void MainWindow::slotGenerateButton()
  {
      if(this->cListDisplay->getListChords().size()>0)
      {
          this->sListDisplay->setVisible(true);
          this->choicesDisplay->setVisible(false);
          this->returnButton->setVisible(true);
          this->reinitializeButton->setDisabled(true);
          this->cListDisplay->disableDeletingChords();
      }
      else
      {
          QMessageBox::warning(this, "Aucun accord spécifié", "Vous n'avez sélectionné aucun accord. Pour générer une suite de gamme, veuillez d'abord entrer une suite d'accord.");
      }
      /*__________________________________Test______________*/
      QVector<QString> test1;
      test1.push_back("1");
      test1.push_back("2");
      test1.push_back("3");
      test1.push_back("4");
      test1.push_back("5");
      test1.push_back("6");
      /*QVector<QString> test2;
      test2.push_back("1");
      test2.push_back("2");
      test2.push_back("3");
      test2.push_back("4");
      test2.push_back("5");*/
      QVector<QVector<QString>> testglob;
      testglob.push_back(test1);
      //testglob.push_back(test2);

      this->sListDisplay->constructScalesFoundList(testglob);
      /*__________________________________FinTest___________*/
  }

  void MainWindow::slotReturnButton()
  {
      constructScalesLayout();
      this->sListDisplay->setVisible(false);
      this->choicesDisplay->setVisible(true);
      this->returnButton->setVisible(false);
      this->reinitializeButton->setDisabled(false);
      this->cListDisplay->enableDeletingChords();
      clearLayout(this->scalesLayout);
      constructScalesLayout();
  }

  void MainWindow::slotReinitializeButton()
  {

      //this->cListDisplay->clear();
      clearLayout(this->chordsLayout);
      constructChordsLayout();
  }
