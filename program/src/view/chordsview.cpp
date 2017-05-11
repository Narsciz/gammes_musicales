#include "chordsview.h"

ChordsView::ChordsView(QString chordName) : QFrame()
{
    cout<<"Begining constructing ChordsView"<<endl<<flush;
    this->setWindowFlags(Qt::ToolTip);
    this->setFixedSize(210, 170);
    //this->setFixedSize(500, 500);
    this->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("border: 1px solid black; border-radius:15px;");

    QPoint p = this->mapFromGlobal(QCursor::pos());
    p.setX(p.x()-210);
    p.setY(p.y()-170);
    this->move(p);

    cout<<"Constructing Chords"<<endl<<flush;
    Chord chord(chordName);

    this->name = new QLabel("Accord " + chord.getName());
    this->name->setStyleSheet("border: 0px solid black;");
    this->name->setAlignment(Qt::AlignHCenter);
    this->name->setFixedHeight(15);

    this->line = new QFrame();
    this->line->setFrameShape(QFrame::HLine);
    this->line->setStyleSheet("border: 1px solid black;");

    this->pictureDisplayBase = new QLabel();
    this->pictureDisplayBase->setPixmap(QPixmap("../assets/pictures/notes/Base.png"));
    this->pictureDisplayBase->setStyleSheet("border: 0px solid black;");

    this->notesName = new QLabel();
    this->notesName->setStyleSheet("border: 0px solid black;");
    this->notesName->setAlignment(Qt::AlignHCenter);

    this->mainLayout = new QGridLayout();
    this->mainLayout->addWidget(this->name, 0, 0, 1, 1);
    this->mainLayout->addWidget(this->line, 1, 0, 1, 1);
    this->mainLayout->addWidget(notesName, 2, 0, 1, 1);
    this->mainLayout->addWidget(pictureDisplayBase, 3, 0, 1, 1);

    cout<<"Getting Chords' notes"<<endl<<flush;
    vector<Note> notesList = chord.getNotes();
    cout<<"Displaying Chords' notes indice : "<<endl<<flush;
    for(int i = 0; i<notesList.size(); i++)
        cout<<notesList[i]<<endl<<flush;

    cout<<"Sorting Chords' notes"<<endl<<flush;
    QVector<Note> sortedNotes = notesSort(notesList);
    cout<<"Displaying Sorted Chords' notes indice : "<<endl<<flush;
    for(int i = 0; i<sortedNotes.size(); i++)
        cout<<sortedNotes[i]<<endl<<flush;

    cout<<"Converting Chords' notes"<<endl<<flush;
    QStringList debug = noteToString(sortedNotes);
    cout<<"Displaying Sorted Converted Chords' notes : "<<endl<<flush;
    for(int i = 0; i<debug.size(); i++)
        cout<<debug[i].toStdString()<<endl<<flush;

    constructPictureDisplay(debug);

    this->setLayout(this->mainLayout);
}

void ChordsView::constructPictureDisplay(QStringList listNote)
{
    bool previousIsBis(false);
    for(int i = 0; i<listNote.size(); i++)
    {
        this->notesName->setText(this->notesName->text() + listNote[i] + " ");
        if(listNote[i] == "E")
        {
            this->picturesDisplay.push_back(new QLabel());
            this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/E.png"));
            this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
            this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
        }
        else if(listNote[i] == "F" || listNote[i] == "F#")
        {
            if(i>0 && listNote[i-1] == "E")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/FBis.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = true;
                cout<<"previousIsBis"<<previousIsBis<<endl<<flush;
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/F.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = false;
            }
            if(listNote[i] == "F#")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/FDiese.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
        }
        else if(listNote[i] == "G" || listNote[i] == "G#")
        {
            if(i>0 && (listNote[i-1] == "F"||listNote[i-1] == "F#"))
            {
                if(i>1 && listNote[i-2] == "E" && previousIsBis)
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/G.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = false;
                }
                else
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/GBis.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = true;
                }
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/G.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = false;
            }
            if(listNote[i] == "G#")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/GDiese.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
        }
        else if(listNote[i] == "A" || listNote[i] == "A#")
        {
            if(i>0 && (listNote[i-1] == "G"||listNote[i-1] == "G#"))
            {
                if(i>1 && previousIsBis && (listNote[i-2] == "F" || listNote[i-2] == "F#"))
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/A.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = false;
                }
                else
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/ABis.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = true;
                }
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/A.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = false;
            }
            if(listNote[i] == "A#")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/ADiese.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
        }
        else if(listNote[i] == "B")
        {
            if(i>0 && (listNote[i-1] == "A"||listNote[i-1] == "A#"))
            {
                if(i>1 && previousIsBis && (listNote[i-2] == "G" || listNote[i-2] == "G#"))
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/B.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = false;
                }
                else
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/BBis.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = true;
                }
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/B.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = false;
            }
        }
        else if(listNote[i] == "C" || listNote[i] == "C#")
        {
            if(i>0 && listNote[i-1] == "B")
            {
                if(i>1 && previousIsBis && (listNote[i-2] == "A" || listNote[i-2] == "A#"))
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/C.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = false;
                }
                else
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/CBis.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                    previousIsBis = true;
                }
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/C.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                previousIsBis = false;
            }
            if(listNote[i] == "C#")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/CDiese.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
        }
        else if(listNote[i] == "D" || listNote[i] == "D#")
        {
            if(i>0 && (listNote[i-1] == "C"||listNote[i-1] == "C#"))
            {
                if(i>1 && listNote[i-2] == "B" && previousIsBis)
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/D.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                }
                else
                {
                    this->picturesDisplay.push_back(new QLabel());
                    this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/DBis.png"));
                    this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                    this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
                }
            }
            else
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/D.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
            if(listNote[i] == "D#")
            {
                this->picturesDisplay.push_back(new QLabel());
                this->picturesDisplay.last()->setPixmap(QPixmap("../assets/pictures/notes/DDiese.png"));
                this->picturesDisplay.last()->setStyleSheet("border: 0px solid black;");
                this->mainLayout->addWidget(this->picturesDisplay.last(), 3, 0, 1, 1);
            }
        }
    }
}

QVector<Note> ChordsView::notesSort(vector<Note> notesList)
{
    cout<<"     notesList.size() = "<<notesList.size()<<endl<<flush;
    QVector<Note> res;
    res.push_back(notesList[0]);
    for(int i = 1; i<notesList.size(); i++)
    {
        cout<<"          boucle for "<<i<<endl<<flush;
        int  j = 0;
        bool end = false;
        cout<<"          beginning while"<<endl<<flush;
        while(j < res.size() && !end)
        {
            cout<<"               while "<<j+1<<endl<<flush;
            if(notesList[i] > 3)
            {
                cout<<"notesList[i] > 3"<<endl<<flush;
                if(notesList[i] < res[j] || res[j] < 4)
                {
                    cout<<"                    inserting"<<endl<<flush;
                    res.insert(j, notesList[i]);
                    end = true;
                }
            }
            else
            {
                cout<<"notesList[i] < 4"<<endl<<flush;
                if(res[j] < 4 && notesList[i] < res[j])
                {
                    cout<<"                    inserting"<<endl<<flush;
                    res.insert(j, notesList[i]);
                    end = true;
                }
            }
            j++;
        }
        if(!end)
            res.push_back(notesList[i]);
    }
    cout<<"     res.size() = "<<res.size()<<endl<<flush;
    return res;
}

QStringList ChordsView::noteToString(QVector<Note> notesList)
{
    cout<<"     beginning for"<<endl<<flush;
    QStringList res;
    for(int i = 0; i<notesList.size(); i++)
    {
        cout<<"          boucle for "<<i<<endl<<flush;
        switch(notesList[i])
        {
            case 0: res.push_back("C");
                    break;
            case 1: res.push_back("C#");
                    break;
            case 2: res.push_back("D");
                    break;
            case 3: res.push_back("D#");
                    break;
            case 4: res.push_back("E");
                    break;
            case 5: res.push_back("F");
                    break;
            case 6: res.push_back("F#");
                    break;
            case 7: res.push_back("G");
                    break;
            case 8: res.push_back("G#");
                    break;
            case 9: res.push_back("A");
                    break;
            case 10: res.push_back("A#");
                     break;
            case 11: res.push_back("B");
                     break;
        }
    }
    return res;
}
