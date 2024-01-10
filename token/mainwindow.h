#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QString>
#include <QLineEdit>
#include <C:\Users\pc\Desktop\c++token\token\include\jwt-cpp\jwt.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAlgorithmSelected(int index);
    void onHeadPaySTextChanged();
    void onSaveButtonClicked();
    void onTokenChanged();
    void colorAndDisplayToken(const std::string& token);
private:
    Ui::MainWindow *ui;

    QTextEdit *tokenTextEdit;
    QTextEdit *headerTextEdit;
    QTextEdit *payloadTextEdit;
    QTextEdit *signatureTextEdit;

    QLabel *headerLabel;
    QLabel *payloadLabel;
    QLabel *signatureLabel;
    QLabel *encodedLabel;
    QLabel *decodedLabel;
    QLabel *algo;
    QComboBox *algorithmComboBox;
    QPushButton *saveButton;
    QTextEdit* signatureInput;
    QLabel *verification;
};


#endif // MAINWINDOW_H
