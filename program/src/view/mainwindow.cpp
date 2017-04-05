#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Ut");
    this->setMinimumSize(540, 480);
    QIcon icon("./cle.png");
    this->setWindowIcon(icon);

    this->mainLayout = new QGridLayout();
    this->ui->centralWidget->setLayout(this->mainLayout);

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
     connect(newFile, SIGNAL(triggered(bool)), this, SLOT(slotNewFile()));
     QAction *importFile = new QAction("Importer", menuBar);
     connect(importFile, SIGNAL(triggered(bool)), this, SLOT(slotImportFile()));
     QAction *saveFile = new QAction("Enregistrer", menuBar);
     connect(saveFile, SIGNAL(triggered(bool)), this, SLOT(slotSaveFile()));
     QAction *closeFile = new QAction("Quitter", menuBar);
     connect(closeFile, SIGNAL(triggered(bool)), this, SLOT(slotCloseFile()));
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

     QAction *debugTestSize = menuBar->addAction("DebugTestSize");
     connect(debugTestSize, SIGNAL(triggered(bool)), this, SLOT(slotDebugTestFile()));

     this->setMenuBar(menuBar);
 }
  void MainWindow::constructLayout()
  {
      this->mainLayout->setAlignment(Qt::AlignTop);
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
      this->mainLayout->addWidget(this->returnButton, 4, 0, 1, 1);
  }
  void MainWindow::constructChordsLayout()
  {
      this->clearLayout(this->chordsLayout, true);

      this->cListDisplay = new ChordsListDisplay();
      this->reinitializeButton = new QPushButton("Réinitialiser");
      this->reinitializeButton->setFixedWidth(70);
      QObject::connect(this->reinitializeButton, SIGNAL(clicked()), this, SLOT(slotReinitializeButton()));

      this->chordsLayout->addWidget(this->cListDisplay, 0, 0, 2, 6);
      this->chordsLayout->addWidget(this->reinitializeButton, 1, 6, 1, 1);
      this->reinitializeButton->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
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

  QString MainWindow::openExplorer(int i)
  {
      this->explorer = new QFileDialog();
      this->explorer->setFileMode(QFileDialog::ExistingFile);
      switch(i)
      {
        case 1: this->explorer->setNameFilter(tr("Fichiers textes (*.txt)"));
      }
      QStringList fileNameTemp;
      QString fileName = "";
      if(this->explorer->exec())
      {
          fileNameTemp = this->explorer->selectedFiles();
          for(int i=0; i<fileName.size(); i++)
              fileName += fileNameTemp.at(i).toLocal8Bit().constData();
      }
      return fileName;
  }

  QVector<QString> MainWindow::testFile(QString filePath)
  {
      QString fileContent = "";
      QVector<QString> rtn;
      QFile file(filePath);
      if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
          fileContent = file.readAll();
          file.close();
      }

      cout<<fileContent.toStdString();

      int i = 0;
      bool note = true;
      bool hsEnd = false;
      QString temp;
      do
      {
           if(note)
           {
               if(fileContent[i] == 'A' || fileContent[i] == 'B')
               {
                   i++;

                   QString temp2 = ""+fileContent[i];
                   cout<< temp2.toStdString()<<flush;

                   rtn.push_back(""+fileContent[i]);
                   note = false;
               }
               else
               {
                   fileContent = "";
               }
           }
           else
           {
               if(!hsEnd)
               {
                    temp = "";
                    while(fileContent[i] != ' ' && i<fileContent.size())
                    {
                        temp += fileContent[i];
                        i++;
                    }
                    hsEnd = true;
               }
               else
               {
                   if(temp == "M")
                   {
                       cout << temp.toStdString()<<flush;
                       rtn[rtn.size()-1] += temp;
                       i++;
                   }
                   else
                   {
                       fileContent = "";
                   }
               }
           }
      }while(fileContent.size() != 0 && i<fileContent.size());
      return rtn;
  }
  void MainWindow::resizeEvent ( QResizeEvent * event )
  {
    this->cListDisplay->refresh();
  }

  void MainWindow::fillComboBoxHS(QVector<QString> listHS)
  {
      for(int i = 0; i<listHS.size(); i++)
      {
          this->hsComboBox->addItem(listHS[i]);
      }
  }

  void MainWindow::constructScaleFoundView(QVector<QVector<QString>> listFoundScales)
  {
      this->sListDisplay->constructScalesFoundList(listFoundScales);
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
          QMessageBox::information(this, "Aucun accord spécifié", "Vous n'avez sélectionné aucun accord. Pour générer une suite de gamme, veuillez d'abord entrer une suite d'accord.");
      }

      emit generateSignal(cListDisplay->getListChordsName(), this->parametersComboBox->currentIndex());

      //__________________________________Test______________
      /*QVector<QString> test1;
      test1.push_back("1");
      test1.push_back("2");
      test1.push_back("3");
      test1.push_back("4");
      test1.push_back("5");
      test1.push_back("6");
      QVector<QString> test2;
      test2.push_back("1");
      test2.push_back("2");
      test2.push_back("3");
      test2.push_back("4");
      test2.push_back("5");
      QVector<QVector<QString>> testglob;
      testglob.push_back(test1);
      testglob.push_back(test2);

      this->sListDisplay->constructScalesFoundList(testglob);*/
      //__________________________________FinTest___________
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
      clearLayout(this->chordsLayout);
      constructChordsLayout();
  }
  void MainWindow::slotNewFile()
  {
      clearLayout(this->mainLayout);
      constructLayout();
  }
  void MainWindow::slotImportFile()
  {
      QString fileContent = openExplorer(1);
      QVector<QString> listChords = testFile(fileContent);
      if(fileContent.size() != 0)
      {
            for(int i=0; i<listChords.size(); i++)
            {
                this->cListDisplay->addChord(listChords[i]);
            }
      }
      else
      {
          QMessageBox::warning(this, "Fichier erroné", "Le fichier que vous avez sélectionné n'est pas au bon format. Il peut s'agir de l'extension (.txt) ou bien de la convention lors de la rédaction de vos accords qui n'a pas été respéctée. Veuillez vérifier votre fichier et recommencer. \n Pour plus d'informations sur la façon de rédiger vos accords, veuillez vous référer à l'aide.");

      }
  }
  void MainWindow::slotSaveFile()
  {
      openExplorer(1);
  }
  void MainWindow::slotCloseFile()
  {
    this->close();
  }
  void MainWindow::slotDebugTestFile()
{
    int top, bottom, left, right;
    this->getContentsMargins(&left, &top, &right, &bottom);
    cout<<"MainWindowContentsMargins : top = "<<top<<", bottom = "<<bottom<<", left = "<<left<<", right = "<<right<<endl;
    QSize size = this->size();
    cout<<"MainWindowSize : width = "<<size.width()<<", heigth = "<<size.height()<<endl;

    size = this->ui->centralWidget->size();
    cout<<"CentralWidget : width = "<<size.width()<<", heigth = "<<size.height()<<endl;

    this->cListDisplay->getContentsMargins(&left, &top, &right, &bottom);
    cout<<"ChordListDisplayContentsMargins : top = "<<top<<", bottom = "<<bottom<<", left = "<<left<<", right = "<<right<<endl;
    size = this->cListDisplay->size();
    cout<<"ChordListDisplaySize : width = "<<size.width()<<", heigth = "<<size.height()<<endl;

    this->choicesDisplay->getContentsMargins(&left, &top, &right, &bottom);
    cout<<"choicesDisplayContentsMargins : top = "<<top<<", bottom = "<<bottom<<", left = "<<left<<", right = "<<right<<endl;
    size = this->choicesDisplay->size();
    cout<<"choicesDisplaySize : width = "<<size.width()<<", heigth = "<<size.height()<<endl;

    cout<<"-----------------------------------------------------------------------"<<endl;
}
