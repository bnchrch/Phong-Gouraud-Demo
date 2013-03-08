/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Mar 8 11:02:43 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "basicopenglview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Model;
    QAction *actionRemove_Selected;
    QAction *actionLoad_Shader;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    BasicOpenGLView *oglwidget;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QSlider *translateY;
    QSlider *translateZ;
    QSlider *translateX;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QSlider *rotateY;
    QSlider *rotateX;
    QSlider *rotateZ;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QSlider *scaleX;
    QSlider *scaleZ;
    QSlider *scaleY;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(972, 714);
        MainWindow->setMinimumSize(QSize(255, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        actionAdd_Model = new QAction(MainWindow);
        actionAdd_Model->setObjectName(QString::fromUtf8("actionAdd_Model"));
        actionRemove_Selected = new QAction(MainWindow);
        actionRemove_Selected->setObjectName(QString::fromUtf8("actionRemove_Selected"));
        actionLoad_Shader = new QAction(MainWindow);
        actionLoad_Shader->setObjectName(QString::fromUtf8("actionLoad_Shader"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setMinimumSize(QSize(500, 300));

        horizontalLayout->addWidget(oglwidget);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(255, 0));
        frame->setMaximumSize(QSize(255, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(230, 0));
        groupBox->setMaximumSize(QSize(230, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(200, 20));
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setAlternatingRowColors(true);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setSelectionRectVisible(true);

        verticalLayout->addWidget(listWidget);

        addButton = new QPushButton(groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        removeButton = new QPushButton(groupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);


        verticalLayout_2->addWidget(groupBox);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_2->addWidget(checkBox);

        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout_2->addWidget(checkBox_2);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        translateY = new QSlider(groupBox_2);
        translateY->setObjectName(QString::fromUtf8("translateY"));
        translateY->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(translateY, 1, 1, 1, 1);

        translateZ = new QSlider(groupBox_2);
        translateZ->setObjectName(QString::fromUtf8("translateZ"));
        translateZ->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(translateZ, 2, 1, 1, 1);

        translateX = new QSlider(groupBox_2);
        translateX->setObjectName(QString::fromUtf8("translateX"));
        translateX->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(translateX, 0, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rotateY = new QSlider(groupBox_3);
        rotateY->setObjectName(QString::fromUtf8("rotateY"));
        rotateY->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(rotateY, 1, 1, 1, 1);

        rotateX = new QSlider(groupBox_3);
        rotateX->setObjectName(QString::fromUtf8("rotateX"));
        rotateX->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(rotateX, 0, 1, 1, 1);

        rotateZ = new QSlider(groupBox_3);
        rotateZ->setObjectName(QString::fromUtf8("rotateZ"));
        rotateZ->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(rotateZ, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        scaleX = new QSlider(groupBox_4);
        scaleX->setObjectName(QString::fromUtf8("scaleX"));
        scaleX->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(scaleX, 0, 1, 1, 1);

        scaleZ = new QSlider(groupBox_4);
        scaleZ->setObjectName(QString::fromUtf8("scaleZ"));
        scaleZ->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(scaleZ, 2, 1, 1, 1);

        scaleY = new QSlider(groupBox_4);
        scaleY->setObjectName(QString::fromUtf8("scaleY"));
        scaleY->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(scaleY, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 2, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 972, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionAdd_Model);
        menuFile->addAction(actionLoad_Shader);
        menuEdit->addAction(actionRemove_Selected);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAdd_Model->setText(QApplication::translate("MainWindow", "Add Model...", 0, QApplication::UnicodeUTF8));
        actionRemove_Selected->setText(QApplication::translate("MainWindow", "Remove Selected", 0, QApplication::UnicodeUTF8));
        actionLoad_Shader->setText(QApplication::translate("MainWindow", "Load Shader...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Models", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("MainWindow", "Add...", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Orthographic Projection", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("MainWindow", "Use Post Multiply", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Translation", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Rotation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
