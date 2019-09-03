#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 26;
struct TrieNode
{
    struct TrieNode *child[ALPHABET_SIZE];
    bool isEndOfWord;
    string meaning;
};

struct TrieNode *getNode()
{
    struct TrieNode *nd = new TrieNode;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        nd->child[i] = nullptr;
    }
    nd->isEndOfWord = false;
    nd->meaning = "";
    return nd;
};

struct TrieNode* root;

void insert(struct TrieNode *root, string key, string meaning)
{
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    if (root == nullptr)
        root = getNode();

    struct TrieNode *temp = root;
    //make sure that all characters are in lowercase
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!temp->child[index])
            temp->child[index] = getNode();
        temp = temp->child[index];
    }
    temp->isEndOfWord = true;
    temp->meaning = meaning;
};

QString getMeaning(struct TrieNode *root, string key)
{
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    if (!root)
        return "Not Found in our Dictionary";

    struct TrieNode *temp = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        temp = temp->child[index];
        if (!temp)
        {
            return "Not Found in our Dictionary";
        }
    }
    if (temp->isEndOfWord){
        QString ans=QString::fromStdString(temp->meaning);
        return ans;
    }
    return "Not Found in our Dictionary";
};

void setDictionary(struct TrieNode *root, int num_lines)
{
//    char *path=QCoreApplication::applicationDirPath().append("/dictionary/dictionary.csv").toLocal8Bit().data();
    char *path=":/input.csv";
    ifstream inFile(path, ios::in);
    if (!inFile)
    {
        cout << "Couldn't open the file" << endl;
        return;
    }

    string s[num_lines];
    string h[num_lines];
    string t[num_lines];
    string line;

    int i = 0, p = 0, q = 0, z = 0;
    while (getline(inFile, line))
    {
        int l = line.length();
        // cout<<l<<endl;
        for (i = 0; i < l; i++)
        {
            if (line[i] != ',')
            {
                s[q] = s[q] + line[i];
            }
            if (line[i] == ',')
            {
                for (p = 0; p < l - i - 1; p++)
                {
                    h[q] = h[q] + line[i + p + 1];
                } //cout<<""<<endl;
                break;
            }
        }
        q++;
    }
    for (z = 0; z < num_lines; z++)
    {
        insert(root, s[z], h[z]);
    }
}

void MainWindow::loadFile(){
    //

    QFile file(":/input.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->textEdit->setText("File not found");
    }
         QTextStream in(&file);
         while (!in.atEnd()) {
             QString line = in.readLine();
             int a=0;
             for(int i=0;i<line.size();i++){
             if(line.at(i)==QChar(',')){
                 a=i;
                 break;
             }
             }
              QString str1=line.left(a);

             QString str2=line.mid(a+1);
             string txt=str1.toLocal8Bit().constData();
          string meaning = str2.toLocal8Bit().constData();
          transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
          transform(meaning.begin(), meaning.end(),meaning.begin(), ::tolower);
           insert(root,txt,meaning);
         }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    root=getNode();
    loadFile();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString text=ui->textEdit->toPlainText();
    string txt=text.toUtf8().constData();
    QString output = getMeaning(root,txt);
    ui->textEdit_2->setText(output);

}
