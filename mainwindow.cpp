#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    initSignalSlot();
    setCentralWidget(ui->textEdit);
    setWindowTitle("简易文本编辑器");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    // 当前文件名
    labelFileName_ = new QLabel;
    labelFileName_->setText("当前文件：");
    labelFileName_->setMaximumWidth(180);
    ui->statusbar->addWidget(labelFileName_);
    // 字体大小比例
    progressBar_ = new QProgressBar;
    progressBar_->setMinimum(9);
    progressBar_->setMaximum(60);
    progressBar_->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBar_);
    // 字体大小写设置
    ui->toolBar->addWidget(new QLabel("字体大小"));
    spinBox_ = new QSpinBox;
    spinBox_->setMinimumWidth(30);
    spinBox_->setMinimum(8);
    spinBox_->setMaximum(60);
    spinBox_->setValue(ui->textEdit->font().pointSize());
    ui->toolBar->addWidget(spinBox_);
    // 字体选择
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(new QLabel("字体 "));
    fontComboBox_ = new QFontComboBox;
    fontComboBox_->setMinimumWidth(30);
    ui->toolBar->addWidget(fontComboBox_);
}

void MainWindow::initSignalSlot()
{
    connect(spinBox_,SIGNAL(valueChanged(int)),this,SLOT(on_spinBox_valueChanged(int)));
    connect(fontComboBox_,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_fontComboBox_currentIndexChanged(const QString &)));
}


void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    labelFileName_->setText("当前文件：");
}

void MainWindow::on_actionOpen_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this,"1.打开文件");
    QFile file(FileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
        ui->textEdit->clear();
        labelFileName_->setText(FileName);
        QTextStream stream(&file);
        while (!file.atEnd()){
            ui->textEdit->append(stream.readLine());
        }
        labelFileName_->setText(FileName);
        file.close();
    }
}

void MainWindow::on_actionItalic_toggled(bool checked)
{
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    format.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_actionBold_triggered(bool checked)
{
    auto format = ui->textEdit->currentCharFormat();
    format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_actionUnderLine_triggered(bool checked)
{
    auto format = ui->textEdit->currentCharFormat();
    format.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_spinBox_valueChanged(int value)
{
    QTextCharFormat format;
    format.setFontPointSize(value);
    ui->textEdit->mergeCurrentCharFormat(format);


    progressBar_->setValue(value);
}

void MainWindow::on_fontComboBox_currentIndexChanged(const QString &text)
{
    QTextCharFormat format;
    format.setFontFamily(text);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCut->setEnabled(b);
    ui->actionCopy->setEnabled(b);
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    auto format = ui->textEdit->currentCharFormat();
    ui->actionBold->setChecked(format.font().bold());
    ui->actionItalic->setChecked(format.fontItalic());
    ui->actionUnderLine->setChecked(format.fontUnderline());
}
