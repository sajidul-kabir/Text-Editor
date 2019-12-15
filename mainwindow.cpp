#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QtWidgets>
#include "highlighter.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
  //ui->textEdit->setFontPointSize(10);
      highlighter = new Highlighter(ui->textEdit->document());
    this->setWindowTitle(tr("MercuryPad"));

     // ui->textEdit->zoomIn(2);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
     //ui->textEdit->setFontPointSize(10);
    currentFile.clear();                          //clearing the current strings
    ui->textEdit->setText(QString());             //clearing the text edit widget
}

void MainWindow::on_actionOpen_triggered()
{
    // ui->textEdit->setFontPointSize(10);
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
    // ui->textEdit->setFontPointSize(10);
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
/*void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(8);

    //editor = new QTextEdit;
    //editor->setFont(font);

    highlighter = new Highlighter(ui->textEdit->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
*/

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
    /*QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    ui->textEdit->textCursor().mergeCharFormat(format);*/
    ui->textEdit->setFontWeight(QFont::Bold);
}

void MainWindow::on_actionCopy_2_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionItalic_triggered()
{
   /* QTextCharFormat format;
    format.setFontItalic(QFont::Normal);
    ui->textEdit->textCursor().mergeCharFormat(format);*/
    ui->textEdit->setFontItalic(true);
}

void MainWindow::on_actionNormal_triggered()
{
    // ui->textEdit->setFontPointSize(10);
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    format.setFontUnderline(false);
    format.setFontItalic(false);
    ui->textEdit->textCursor().mergeCharFormat(format);
    ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFontUnderline(false);
    ui->textEdit->setFontItalic(false);

}

void MainWindow::on_actionUnderline_triggered()
{
    /*QTextCharFormat format;
    format.setFontUnderline(QFont::Normal);
    ui->textEdit->textCursor().mergeCharFormat(format);*/
    ui->textEdit->setFontUnderline(true);
}

void MainWindow::on_actionHorizontal_line_triggered()
{
   ui->textEdit->insertHtml("<html><head></head><body><hr><br></body></html>");

}

void MainWindow::on_actionLeft_aligmnent_triggered()
{
ui->textEdit->setAlignment(Qt::AlignLeft);

}

void MainWindow::on_actionFonts_triggered()
{
            bool fontSelected;
               QFont font = QFontDialog::getFont(&fontSelected, this);
               if (fontSelected)
                   ui->textEdit->setFont(font);
}

void MainWindow::on_actionright_triggered()
{
        ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionJustified_alignment_triggered()
{
        ui->textEdit->setAlignment(Qt::AlignJustify);
}


void MainWindow::on_actionCenter_alignment_triggered()
{
        ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_actionTitle_triggered()
{
/*QTextCharFormat format;
format.setFontPointSize(15);
 ui->textEdit->textCursor().mergeCharFormat(format);*/
    ui->textEdit->setFontWeight(QFont::Bold);
 ui->textEdit->setFontPointSize(15);

}

void MainWindow::on_actionPlain_text_triggered()
{
     ui->textEdit->setFontWeight(QFont::Normal);
 ui->textEdit->setFontPointSize(8);
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog pdialog(&printer,this);
    if(pdialog.exec()==QDialog::Rejected)
    {
        QMessageBox::warning(this,"warning","cannot access printer");
           return;
    }
    ui->textEdit->print(&printer);
}
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About MercuryPad"),
                tr("<p>This is a simple text editor with the ability to highlight c++ syntaxes. " \
                   "It can perform all the functionalities like a normal texteditor and in addition, it can read codes.</p>"
                   "<p>Developed by Sajidul Kabir and Anindo Sarker</p>"));

}
