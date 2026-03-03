#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSpinBox> // 字体大小
#include<QProgressBar>// 进度条
#include<QLabel> //标签
#include<QFontComboBox> //字体选择

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

    void on_actionItalic_toggled(bool checked);

    void on_actionBold_triggered(bool checked);

    void on_actionUnderLine_triggered(bool checked);

    // 字体大小
    void on_spinBox_valueChanged(int value);
    // 字体选择
    void on_fontComboBox_currentIndexChanged(const QString &text);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

private:
    Ui::MainWindow *ui;

    QLabel* labelFileName_;
    QProgressBar* progressBar_;
    QSpinBox* spinBox_;
    QFontComboBox* fontComboBox_;

    void initUi();

    void initSignalSlot();
};
#endif // MAINWINDOW_H
