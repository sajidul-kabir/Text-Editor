#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>                 //header files
#include <QPrinter>
#include <QMessageBox>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>
#include <QTextCursor>
#include <QTextDocument>
#include <QFrame>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QSyntaxHighlighter>
#include "highlighter.h"
#include <QTextFormat>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
class QTextEdit;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();



    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSelect_all_triggered();

    void on_actionPaste_triggered();

    void on_actionBold_triggered();

    void on_actionCopy_2_triggered();

    void on_actionItalic_triggered();

    void on_actionNormal_triggered();

    void on_actionUnderline_triggered();

    void on_actionHorizontal_line_triggered();



    void on_actionLeft_aligmnent_triggered();

    void on_actionFonts_triggered();

    void on_actionright_triggered();


    void on_actionJustified_alignment_triggered();



    void on_actionCenter_alignment_triggered();

    void on_actionTitle_triggered();

    void on_actionPlain_text_triggered();

    void on_actionPrint_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile="";
   Highlighter *highlighter;
    //void setupEditor();
    QTextEdit *editor;
 //void setupEditor();
};
#endif // MAINWINDOW_H
