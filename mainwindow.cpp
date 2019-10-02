#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();                          //clearing the current strings
    ui->textEdit->setText(QString());             //clearing the text edit widget
}

void MainWindow::on_actionOpen_triggered()
{
    QString nameofthenewfile=QFileDialog::getOpenFileName(this, "Open File");     //opening a file
    QFile file(nameofthenewfile);                              //creating an object for reading and wrting files
    currentFile=nameofthenewfile;                             //storing the new file onto our current file
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning","cannot open file :"+file.errorString());
        return;
    }

    setWindowTitle(nameofthenewfile);                         //setting a title for the new file
    QTextStream read(&file);                             //creating interface for reading file
    QString text=read.readAll();                         //copying the text in the string
    ui->textEdit->setText(text);                             //putting the text onto our text edit widget
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString nameofthenewfile=QFileDialog::getSaveFileName(this, "Save as");        //saving the file
    QFile file(nameofthenewfile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "warning","cannot save file :"+file.errorString());
        return;
    }
     currentFile=nameofthenewfile;
    setWindowTitle(nameofthenewfile);
    QTextStream write(&file);
    QString text=ui->textEdit->toPlainText();       //copy the text from the text widget and convert it back to plaintext
     write << text;                                  //printing the text that was copied
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();                       //exit the text editor
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
     ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}

void MainWindow::on_actionSelect_all_triggered()
{
     ui->textEdit->selectAll();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionBold_triggered()
{
   QPainter mytext(this);
   mytext.setFont(QFont("Times",16,QFont::Bold));
    ui->textEdit->setText(QString());

}
