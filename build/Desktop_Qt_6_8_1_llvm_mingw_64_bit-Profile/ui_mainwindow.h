/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSpinBox *curvedPipeSpinBox;
    QSpinBox *tSplitterSpinBox;
    QSpinBox *crossPipeSpinBox;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *solveButton;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *crossPipeSpinBox_2;
    QSpinBox *straightPipeSpinBox_2;
    QSpinBox *tSplitterSpinBox_2;
    QSpinBox *curvedPipeSpinBox_2;
    QSpinBox *crossPipeSpinBox_3;
    QLabel *label_9;
    QTableWidget *tableWidget;
    QLabel *label_10;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QLabel *label_11;
    QLabel *label_12;
    QTextEdit *SourceTextLabel;
    QLabel *label_13;
    QComboBox *SourceColorComboBox;
    QComboBox *SourceShapeComboBox;
    QPushButton *addSourcePushButton;
    QLabel *label_14;
    QSpinBox *straightPipeSpinBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 678);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        curvedPipeSpinBox = new QSpinBox(centralwidget);
        curvedPipeSpinBox->setObjectName("curvedPipeSpinBox");
        curvedPipeSpinBox->setGeometry(QRect(70, 200, 31, 22));
        tSplitterSpinBox = new QSpinBox(centralwidget);
        tSplitterSpinBox->setObjectName("tSplitterSpinBox");
        tSplitterSpinBox->setGeometry(QRect(70, 250, 31, 22));
        crossPipeSpinBox = new QSpinBox(centralwidget);
        crossPipeSpinBox->setObjectName("crossPipeSpinBox");
        crossPipeSpinBox->setGeometry(QRect(70, 300, 31, 22));
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName("label_1");
        label_1->setGeometry(QRect(20, 140, 41, 41));
        label_1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	image: url(:/images/egyenescso0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 190, 41, 41));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/kanyar0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 240, 41, 41));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/tcso0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 290, 41, 41));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/kereszt0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        solveButton = new QPushButton(centralwidget);
        solveButton->setObjectName("solveButton");
        solveButton->setGeometry(QRect(60, 600, 221, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tw Cen MT")});
        font.setPointSize(11);
        font.setBold(true);
        solveButton->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(340, 270, 441, 361));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Fira Mono")});
        font1.setPointSize(20);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 228, 167);\n"
"background-color: rgb(199, 199, 199);"));
        label->setMargin(10);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(180, 140, 41, 41));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/egyenescsap1.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 190, 41, 41));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/kanyarcsap0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(180, 240, 41, 41));
        label_7->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/tcsap.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(180, 290, 41, 41));
        label_8->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/keresztcsap.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        crossPipeSpinBox_2 = new QSpinBox(centralwidget);
        crossPipeSpinBox_2->setObjectName("crossPipeSpinBox_2");
        crossPipeSpinBox_2->setGeometry(QRect(230, 300, 31, 22));
        straightPipeSpinBox_2 = new QSpinBox(centralwidget);
        straightPipeSpinBox_2->setObjectName("straightPipeSpinBox_2");
        straightPipeSpinBox_2->setGeometry(QRect(230, 150, 31, 22));
        tSplitterSpinBox_2 = new QSpinBox(centralwidget);
        tSplitterSpinBox_2->setObjectName("tSplitterSpinBox_2");
        tSplitterSpinBox_2->setGeometry(QRect(230, 250, 31, 22));
        curvedPipeSpinBox_2 = new QSpinBox(centralwidget);
        curvedPipeSpinBox_2->setObjectName("curvedPipeSpinBox_2");
        curvedPipeSpinBox_2->setGeometry(QRect(230, 200, 31, 22));
        crossPipeSpinBox_3 = new QSpinBox(centralwidget);
        crossPipeSpinBox_3->setObjectName("crossPipeSpinBox_3");
        crossPipeSpinBox_3->setGeometry(QRect(70, 350, 31, 22));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 340, 41, 41));
        label_9->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    image: url(:/images/zsakutca0.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(40, 450, 261, 141));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Tw Cen MT")});
        font2.setPointSize(11);
        tableWidget->setFont(font2);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(40, 390, 201, 16));
        label_10->setFont(font2);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(230, 410, 71, 31));
        pushButton->setFont(font);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 410, 181, 31));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(60, 110, 51, 20));
        label_11->setFont(font2);
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(220, 110, 51, 20));
        label_12->setFont(font2);
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);
        SourceTextLabel = new QTextEdit(centralwidget);
        SourceTextLabel->setObjectName("SourceTextLabel");
        SourceTextLabel->setGeometry(QRect(40, 30, 171, 31));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(40, 10, 211, 16));
        label_13->setFont(font2);
        SourceColorComboBox = new QComboBox(centralwidget);
        SourceColorComboBox->setObjectName("SourceColorComboBox");
        SourceColorComboBox->setGeometry(QRect(220, 30, 81, 31));
        SourceShapeComboBox = new QComboBox(centralwidget);
        SourceShapeComboBox->setObjectName("SourceShapeComboBox");
        SourceShapeComboBox->setGeometry(QRect(40, 70, 211, 31));
        addSourcePushButton = new QPushButton(centralwidget);
        addSourcePushButton->setObjectName("addSourcePushButton");
        addSourcePushButton->setGeometry(QRect(260, 70, 41, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Tw Cen MT")});
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        addSourcePushButton->setFont(font3);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(340, 10, 441, 251));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Tw Cen MT")});
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        label_14->setFont(font4);
        label_14->setAutoFillBackground(false);
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(199, 199, 199);\n"
"font: 10pt \"Tw Cen MT\";\n"
"color: rgb(0, 0, 0);\n"
"alternate-background-color: rgb(0, 0, 0);"));
        label_14->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_14->setMargin(10);
        straightPipeSpinBox = new QSpinBox(centralwidget);
        straightPipeSpinBox->setObjectName("straightPipeSpinBox");
        straightPipeSpinBox->setGeometry(QRect(70, 150, 31, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_1->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        solveButton->setText(QCoreApplication::translate("MainWindow", "Add meg a megold\303\241st!", nullptr));
#if QT_CONFIG(tooltip)
        label->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        label->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        label_8->setText(QString());
        label_9->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Akt\303\255v sz\303\255nek f\303\241zisonk\303\251nt", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Sz\303\255n megad\303\241sa egy f\303\241zisban:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "+ F\303\201ZIS", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Cs\303\266vek", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Csapok", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Forr\303\241sok \303\251s fogyaszt\303\263k megad\303\241sa:", nullptr));
        addSourcePushButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        label_14->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        label_14->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_14->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
