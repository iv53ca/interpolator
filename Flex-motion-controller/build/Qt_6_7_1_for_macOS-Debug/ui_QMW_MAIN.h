/********************************************************************************
** Form generated from reading UI file 'QMW_MAIN.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMW_MAIN_H
#define UI_QMW_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "Plots/QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_QMW_MAIN
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_13;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *TE_LINES;
    QTextBrowser *TB_MOVE_TABLE;
    QCheckBox *CB_IGNORE_SUCCESS_QMB;
    QPushButton *PB_CALC_MOTION;
    QPushButton *PB_CLEAR;
    QGridLayout *gridLayout_12;
    QFrame *frame_2;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_5;
    QLabel *L_X0_POLYGON;
    QLabel *L_Y0_POLYGON;
    QLabel *L_ANGLE_POLYGON;
    QLabel *L_SEG_COUNT_POLYGON;
    QLineEdit *LE_ANGLE_POLYGON;
    QLabel *L_SEG_LENGTH_POLYGON;
    QLineEdit *LE_SEG_COUNT_POLYGON;
    QLineEdit *LE_Y0_POLYGON;
    QLineEdit *LE_X0_POLYGON;
    QLineEdit *LE_SEG_LENGTH_POLYGON;
    QPushButton *PB_GENERATE_POLYGON;
    QLabel *L_POLYGON;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QPushButton *PB_GENERATE_TURN;
    QGridLayout *gridLayout_4;
    QRadioButton *RB_SEGC_COUNT_3_TURN;
    QLabel *L_X0_TURN;
    QLabel *L_Y0_TURN;
    QRadioButton *RB_SEGC_COUNT_2_TURN;
    QLabel *L_SEG3_LENGTH_TURN;
    QLineEdit *LE_SEG2_LENGTH_TURN;
    QLabel *L_ANGLE_DIV_TURN;
    QLineEdit *LE_ANGLE_DIV_TURN;
    QLineEdit *LE_Y0_TURN;
    QLabel *L_SEG2_LENGTH_TURN;
    QLineEdit *LE_SEG3_LENGTH_TURN;
    QLabel *L_SEG1_LENGTH_TURN;
    QLineEdit *LE_X0_TURN;
    QLineEdit *LE_SEG1_LENGTH_TURN;
    QLabel *L_CIRCLE_DIV_TURN;
    QLineEdit *LE_CIRCLE_DIV_TURN;
    QLabel *L_TURN;
    QSpacerItem *verticalSpacer;
    QFrame *frame_3;
    QGridLayout *gridLayout_9;
    QLabel *L_POLYGON_2;
    QPushButton *PB_GENERATE_NINJA;
    QGridLayout *gridLayout_8;
    QLabel *L_OUTER_RADIUS_NINJA;
    QLabel *L_SEG_COUNT_NINJA;
    QLineEdit *LE_OUTER_RADIUS_NINJA;
    QLineEdit *LE_X0_NINJA;
    QLineEdit *LE_INNEAR_RADIUS_NINJA;
    QLabel *L_X0_NINJA;
    QLineEdit *LE_SEG_COUNT_NINJA;
    QLabel *L_INNEAR_RADIUS_NINJA;
    QLabel *L_Y0_NINJA;
    QLineEdit *LE_Y0_NINJA;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame_4;
    QGridLayout *gridLayout_11;
    QPushButton *PB_GENERATE_SAW;
    QLabel *L_POLYGON_3;
    QGridLayout *gridLayout_10;
    QLineEdit *LE_STEP_SAW;
    QLabel *L_STEP_SAW;
    QLineEdit *LE_A_SAW;
    QLabel *L_A_SAW;
    QLabel *L_COUNT_SAW;
    QLineEdit *LE_COUNT_SAW;
    QSpacerItem *verticalSpacer_4;
    QPushButton *PB_TEST;
    QLineEdit *LE_TEST_FILENAME;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QCustomPlot *CP_TRAJECTORY;
    QLabel *L_TRAJECTORY_COORD;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QGridLayout *gridLayout_2;
    QCustomPlot *CP_VELOCITY_X;
    QTextBrowser *TB_LOG_X;
    QCustomPlot *CP_VELOCITY_Y;
    QTextBrowser *TB_LOG_Y;
    QLabel *L_VELOCITY_COORD;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QMW_MAIN)
    {
        if (QMW_MAIN->objectName().isEmpty())
            QMW_MAIN->setObjectName("QMW_MAIN");
        QMW_MAIN->resize(1655, 1011);
        centralwidget = new QWidget(QMW_MAIN);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName("gridLayout_14");
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName("gridLayout_13");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_2, 0, 1, 1, 1);

        TE_LINES = new QTextEdit(centralwidget);
        TE_LINES->setObjectName("TE_LINES");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TE_LINES->sizePolicy().hasHeightForWidth());
        TE_LINES->setSizePolicy(sizePolicy);
        TE_LINES->setMaximumSize(QSize(227, 16777215));
        TE_LINES->setFont(font);

        gridLayout_13->addWidget(TE_LINES, 1, 0, 1, 1);

        TB_MOVE_TABLE = new QTextBrowser(centralwidget);
        TB_MOVE_TABLE->setObjectName("TB_MOVE_TABLE");
        sizePolicy.setHeightForWidth(TB_MOVE_TABLE->sizePolicy().hasHeightForWidth());
        TB_MOVE_TABLE->setSizePolicy(sizePolicy);
        TB_MOVE_TABLE->setMaximumSize(QSize(137, 16777215));

        gridLayout_13->addWidget(TB_MOVE_TABLE, 1, 1, 1, 1);


        gridLayout_14->addLayout(gridLayout_13, 0, 0, 1, 1);

        CB_IGNORE_SUCCESS_QMB = new QCheckBox(centralwidget);
        CB_IGNORE_SUCCESS_QMB->setObjectName("CB_IGNORE_SUCCESS_QMB");
        CB_IGNORE_SUCCESS_QMB->setChecked(true);

        gridLayout_14->addWidget(CB_IGNORE_SUCCESS_QMB, 1, 0, 1, 1);

        PB_CALC_MOTION = new QPushButton(centralwidget);
        PB_CALC_MOTION->setObjectName("PB_CALC_MOTION");

        gridLayout_14->addWidget(PB_CALC_MOTION, 2, 0, 1, 1);

        PB_CLEAR = new QPushButton(centralwidget);
        PB_CLEAR->setObjectName("PB_CLEAR");

        gridLayout_14->addWidget(PB_CLEAR, 3, 0, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName("gridLayout_12");
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background-color: rgb(255, 250, 237);\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_2);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        L_X0_POLYGON = new QLabel(frame_2);
        L_X0_POLYGON->setObjectName("L_X0_POLYGON");

        gridLayout_5->addWidget(L_X0_POLYGON, 3, 0, 1, 1);

        L_Y0_POLYGON = new QLabel(frame_2);
        L_Y0_POLYGON->setObjectName("L_Y0_POLYGON");

        gridLayout_5->addWidget(L_Y0_POLYGON, 4, 0, 1, 1);

        L_ANGLE_POLYGON = new QLabel(frame_2);
        L_ANGLE_POLYGON->setObjectName("L_ANGLE_POLYGON");

        gridLayout_5->addWidget(L_ANGLE_POLYGON, 2, 0, 1, 1);

        L_SEG_COUNT_POLYGON = new QLabel(frame_2);
        L_SEG_COUNT_POLYGON->setObjectName("L_SEG_COUNT_POLYGON");

        gridLayout_5->addWidget(L_SEG_COUNT_POLYGON, 0, 0, 1, 1);

        LE_ANGLE_POLYGON = new QLineEdit(frame_2);
        LE_ANGLE_POLYGON->setObjectName("LE_ANGLE_POLYGON");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LE_ANGLE_POLYGON->sizePolicy().hasHeightForWidth());
        LE_ANGLE_POLYGON->setSizePolicy(sizePolicy1);
        LE_ANGLE_POLYGON->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(LE_ANGLE_POLYGON, 2, 1, 1, 1);

        L_SEG_LENGTH_POLYGON = new QLabel(frame_2);
        L_SEG_LENGTH_POLYGON->setObjectName("L_SEG_LENGTH_POLYGON");

        gridLayout_5->addWidget(L_SEG_LENGTH_POLYGON, 1, 0, 1, 1);

        LE_SEG_COUNT_POLYGON = new QLineEdit(frame_2);
        LE_SEG_COUNT_POLYGON->setObjectName("LE_SEG_COUNT_POLYGON");
        sizePolicy1.setHeightForWidth(LE_SEG_COUNT_POLYGON->sizePolicy().hasHeightForWidth());
        LE_SEG_COUNT_POLYGON->setSizePolicy(sizePolicy1);
        LE_SEG_COUNT_POLYGON->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(LE_SEG_COUNT_POLYGON, 0, 1, 1, 1);

        LE_Y0_POLYGON = new QLineEdit(frame_2);
        LE_Y0_POLYGON->setObjectName("LE_Y0_POLYGON");
        LE_Y0_POLYGON->setEnabled(true);
        sizePolicy1.setHeightForWidth(LE_Y0_POLYGON->sizePolicy().hasHeightForWidth());
        LE_Y0_POLYGON->setSizePolicy(sizePolicy1);
        LE_Y0_POLYGON->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(LE_Y0_POLYGON, 4, 1, 1, 1);

        LE_X0_POLYGON = new QLineEdit(frame_2);
        LE_X0_POLYGON->setObjectName("LE_X0_POLYGON");
        LE_X0_POLYGON->setEnabled(true);
        sizePolicy1.setHeightForWidth(LE_X0_POLYGON->sizePolicy().hasHeightForWidth());
        LE_X0_POLYGON->setSizePolicy(sizePolicy1);
        LE_X0_POLYGON->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(LE_X0_POLYGON, 3, 1, 1, 1);

        LE_SEG_LENGTH_POLYGON = new QLineEdit(frame_2);
        LE_SEG_LENGTH_POLYGON->setObjectName("LE_SEG_LENGTH_POLYGON");
        sizePolicy1.setHeightForWidth(LE_SEG_LENGTH_POLYGON->sizePolicy().hasHeightForWidth());
        LE_SEG_LENGTH_POLYGON->setSizePolicy(sizePolicy1);
        LE_SEG_LENGTH_POLYGON->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(LE_SEG_LENGTH_POLYGON, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 1, 0, 1, 1);

        PB_GENERATE_POLYGON = new QPushButton(frame_2);
        PB_GENERATE_POLYGON->setObjectName("PB_GENERATE_POLYGON");

        gridLayout_7->addWidget(PB_GENERATE_POLYGON, 3, 0, 1, 1);

        L_POLYGON = new QLabel(frame_2);
        L_POLYGON->setObjectName("L_POLYGON");
        L_POLYGON->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(L_POLYGON, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_12->addWidget(frame_2, 0, 1, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background-color: rgb(255, 250, 237);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setObjectName("gridLayout_6");
        PB_GENERATE_TURN = new QPushButton(frame);
        PB_GENERATE_TURN->setObjectName("PB_GENERATE_TURN");

        gridLayout_6->addWidget(PB_GENERATE_TURN, 3, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        RB_SEGC_COUNT_3_TURN = new QRadioButton(frame);
        RB_SEGC_COUNT_3_TURN->setObjectName("RB_SEGC_COUNT_3_TURN");

        gridLayout_4->addWidget(RB_SEGC_COUNT_3_TURN, 2, 1, 1, 1);

        L_X0_TURN = new QLabel(frame);
        L_X0_TURN->setObjectName("L_X0_TURN");

        gridLayout_4->addWidget(L_X0_TURN, 0, 0, 1, 1);

        L_Y0_TURN = new QLabel(frame);
        L_Y0_TURN->setObjectName("L_Y0_TURN");

        gridLayout_4->addWidget(L_Y0_TURN, 1, 0, 1, 1);

        RB_SEGC_COUNT_2_TURN = new QRadioButton(frame);
        RB_SEGC_COUNT_2_TURN->setObjectName("RB_SEGC_COUNT_2_TURN");
        RB_SEGC_COUNT_2_TURN->setChecked(true);

        gridLayout_4->addWidget(RB_SEGC_COUNT_2_TURN, 2, 0, 1, 1);

        L_SEG3_LENGTH_TURN = new QLabel(frame);
        L_SEG3_LENGTH_TURN->setObjectName("L_SEG3_LENGTH_TURN");

        gridLayout_4->addWidget(L_SEG3_LENGTH_TURN, 5, 0, 1, 1);

        LE_SEG2_LENGTH_TURN = new QLineEdit(frame);
        LE_SEG2_LENGTH_TURN->setObjectName("LE_SEG2_LENGTH_TURN");
        sizePolicy1.setHeightForWidth(LE_SEG2_LENGTH_TURN->sizePolicy().hasHeightForWidth());
        LE_SEG2_LENGTH_TURN->setSizePolicy(sizePolicy1);
        LE_SEG2_LENGTH_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_SEG2_LENGTH_TURN, 4, 1, 1, 1);

        L_ANGLE_DIV_TURN = new QLabel(frame);
        L_ANGLE_DIV_TURN->setObjectName("L_ANGLE_DIV_TURN");

        gridLayout_4->addWidget(L_ANGLE_DIV_TURN, 6, 0, 1, 1);

        LE_ANGLE_DIV_TURN = new QLineEdit(frame);
        LE_ANGLE_DIV_TURN->setObjectName("LE_ANGLE_DIV_TURN");
        sizePolicy1.setHeightForWidth(LE_ANGLE_DIV_TURN->sizePolicy().hasHeightForWidth());
        LE_ANGLE_DIV_TURN->setSizePolicy(sizePolicy1);
        LE_ANGLE_DIV_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_ANGLE_DIV_TURN, 6, 1, 1, 1);

        LE_Y0_TURN = new QLineEdit(frame);
        LE_Y0_TURN->setObjectName("LE_Y0_TURN");
        LE_Y0_TURN->setEnabled(false);
        sizePolicy1.setHeightForWidth(LE_Y0_TURN->sizePolicy().hasHeightForWidth());
        LE_Y0_TURN->setSizePolicy(sizePolicy1);
        LE_Y0_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_Y0_TURN, 1, 1, 1, 1);

        L_SEG2_LENGTH_TURN = new QLabel(frame);
        L_SEG2_LENGTH_TURN->setObjectName("L_SEG2_LENGTH_TURN");

        gridLayout_4->addWidget(L_SEG2_LENGTH_TURN, 4, 0, 1, 1);

        LE_SEG3_LENGTH_TURN = new QLineEdit(frame);
        LE_SEG3_LENGTH_TURN->setObjectName("LE_SEG3_LENGTH_TURN");
        LE_SEG3_LENGTH_TURN->setEnabled(false);
        sizePolicy1.setHeightForWidth(LE_SEG3_LENGTH_TURN->sizePolicy().hasHeightForWidth());
        LE_SEG3_LENGTH_TURN->setSizePolicy(sizePolicy1);
        LE_SEG3_LENGTH_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_SEG3_LENGTH_TURN, 5, 1, 1, 1);

        L_SEG1_LENGTH_TURN = new QLabel(frame);
        L_SEG1_LENGTH_TURN->setObjectName("L_SEG1_LENGTH_TURN");

        gridLayout_4->addWidget(L_SEG1_LENGTH_TURN, 3, 0, 1, 1);

        LE_X0_TURN = new QLineEdit(frame);
        LE_X0_TURN->setObjectName("LE_X0_TURN");
        LE_X0_TURN->setEnabled(false);
        sizePolicy1.setHeightForWidth(LE_X0_TURN->sizePolicy().hasHeightForWidth());
        LE_X0_TURN->setSizePolicy(sizePolicy1);
        LE_X0_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_X0_TURN, 0, 1, 1, 1);

        LE_SEG1_LENGTH_TURN = new QLineEdit(frame);
        LE_SEG1_LENGTH_TURN->setObjectName("LE_SEG1_LENGTH_TURN");
        sizePolicy1.setHeightForWidth(LE_SEG1_LENGTH_TURN->sizePolicy().hasHeightForWidth());
        LE_SEG1_LENGTH_TURN->setSizePolicy(sizePolicy1);
        LE_SEG1_LENGTH_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_SEG1_LENGTH_TURN, 3, 1, 1, 1);

        L_CIRCLE_DIV_TURN = new QLabel(frame);
        L_CIRCLE_DIV_TURN->setObjectName("L_CIRCLE_DIV_TURN");

        gridLayout_4->addWidget(L_CIRCLE_DIV_TURN, 7, 0, 1, 1);

        LE_CIRCLE_DIV_TURN = new QLineEdit(frame);
        LE_CIRCLE_DIV_TURN->setObjectName("LE_CIRCLE_DIV_TURN");
        sizePolicy1.setHeightForWidth(LE_CIRCLE_DIV_TURN->sizePolicy().hasHeightForWidth());
        LE_CIRCLE_DIV_TURN->setSizePolicy(sizePolicy1);
        LE_CIRCLE_DIV_TURN->setMaximumSize(QSize(60, 16777215));

        gridLayout_4->addWidget(LE_CIRCLE_DIV_TURN, 7, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 1, 0, 1, 1);

        L_TURN = new QLabel(frame);
        L_TURN->setObjectName("L_TURN");
        L_TURN->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(L_TURN, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 2, 0, 1, 1);


        gridLayout_12->addWidget(frame, 0, 0, 1, 1);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName("frame_3");
        frame_3->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background-color: rgb(255, 250, 237);\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_3);
        gridLayout_9->setObjectName("gridLayout_9");
        L_POLYGON_2 = new QLabel(frame_3);
        L_POLYGON_2->setObjectName("L_POLYGON_2");
        L_POLYGON_2->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(L_POLYGON_2, 0, 0, 1, 1);

        PB_GENERATE_NINJA = new QPushButton(frame_3);
        PB_GENERATE_NINJA->setObjectName("PB_GENERATE_NINJA");

        gridLayout_9->addWidget(PB_GENERATE_NINJA, 3, 0, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        L_OUTER_RADIUS_NINJA = new QLabel(frame_3);
        L_OUTER_RADIUS_NINJA->setObjectName("L_OUTER_RADIUS_NINJA");

        gridLayout_8->addWidget(L_OUTER_RADIUS_NINJA, 1, 0, 1, 1);

        L_SEG_COUNT_NINJA = new QLabel(frame_3);
        L_SEG_COUNT_NINJA->setObjectName("L_SEG_COUNT_NINJA");

        gridLayout_8->addWidget(L_SEG_COUNT_NINJA, 0, 0, 1, 1);

        LE_OUTER_RADIUS_NINJA = new QLineEdit(frame_3);
        LE_OUTER_RADIUS_NINJA->setObjectName("LE_OUTER_RADIUS_NINJA");
        sizePolicy1.setHeightForWidth(LE_OUTER_RADIUS_NINJA->sizePolicy().hasHeightForWidth());
        LE_OUTER_RADIUS_NINJA->setSizePolicy(sizePolicy1);
        LE_OUTER_RADIUS_NINJA->setMaximumSize(QSize(60, 16777215));

        gridLayout_8->addWidget(LE_OUTER_RADIUS_NINJA, 1, 1, 1, 1);

        LE_X0_NINJA = new QLineEdit(frame_3);
        LE_X0_NINJA->setObjectName("LE_X0_NINJA");
        LE_X0_NINJA->setEnabled(true);
        sizePolicy1.setHeightForWidth(LE_X0_NINJA->sizePolicy().hasHeightForWidth());
        LE_X0_NINJA->setSizePolicy(sizePolicy1);
        LE_X0_NINJA->setMaximumSize(QSize(60, 16777215));

        gridLayout_8->addWidget(LE_X0_NINJA, 3, 1, 1, 1);

        LE_INNEAR_RADIUS_NINJA = new QLineEdit(frame_3);
        LE_INNEAR_RADIUS_NINJA->setObjectName("LE_INNEAR_RADIUS_NINJA");
        sizePolicy1.setHeightForWidth(LE_INNEAR_RADIUS_NINJA->sizePolicy().hasHeightForWidth());
        LE_INNEAR_RADIUS_NINJA->setSizePolicy(sizePolicy1);
        LE_INNEAR_RADIUS_NINJA->setMaximumSize(QSize(60, 16777215));

        gridLayout_8->addWidget(LE_INNEAR_RADIUS_NINJA, 2, 1, 1, 1);

        L_X0_NINJA = new QLabel(frame_3);
        L_X0_NINJA->setObjectName("L_X0_NINJA");

        gridLayout_8->addWidget(L_X0_NINJA, 3, 0, 1, 1);

        LE_SEG_COUNT_NINJA = new QLineEdit(frame_3);
        LE_SEG_COUNT_NINJA->setObjectName("LE_SEG_COUNT_NINJA");
        sizePolicy1.setHeightForWidth(LE_SEG_COUNT_NINJA->sizePolicy().hasHeightForWidth());
        LE_SEG_COUNT_NINJA->setSizePolicy(sizePolicy1);
        LE_SEG_COUNT_NINJA->setMaximumSize(QSize(60, 16777215));

        gridLayout_8->addWidget(LE_SEG_COUNT_NINJA, 0, 1, 1, 1);

        L_INNEAR_RADIUS_NINJA = new QLabel(frame_3);
        L_INNEAR_RADIUS_NINJA->setObjectName("L_INNEAR_RADIUS_NINJA");

        gridLayout_8->addWidget(L_INNEAR_RADIUS_NINJA, 2, 0, 1, 1);

        L_Y0_NINJA = new QLabel(frame_3);
        L_Y0_NINJA->setObjectName("L_Y0_NINJA");

        gridLayout_8->addWidget(L_Y0_NINJA, 4, 0, 1, 1);

        LE_Y0_NINJA = new QLineEdit(frame_3);
        LE_Y0_NINJA->setObjectName("LE_Y0_NINJA");
        LE_Y0_NINJA->setEnabled(true);
        sizePolicy1.setHeightForWidth(LE_Y0_NINJA->sizePolicy().hasHeightForWidth());
        LE_Y0_NINJA->setSizePolicy(sizePolicy1);
        LE_Y0_NINJA->setMaximumSize(QSize(60, 16777215));

        gridLayout_8->addWidget(LE_Y0_NINJA, 4, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer_3, 2, 0, 1, 1);


        gridLayout_12->addWidget(frame_3, 1, 0, 1, 1);

        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName("frame_4");
        frame_4->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	background-color: rgb(255, 250, 237);\n"
"}"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_11 = new QGridLayout(frame_4);
        gridLayout_11->setObjectName("gridLayout_11");
        PB_GENERATE_SAW = new QPushButton(frame_4);
        PB_GENERATE_SAW->setObjectName("PB_GENERATE_SAW");

        gridLayout_11->addWidget(PB_GENERATE_SAW, 4, 0, 1, 1);

        L_POLYGON_3 = new QLabel(frame_4);
        L_POLYGON_3->setObjectName("L_POLYGON_3");
        L_POLYGON_3->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(L_POLYGON_3, 0, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName("gridLayout_10");
        LE_STEP_SAW = new QLineEdit(frame_4);
        LE_STEP_SAW->setObjectName("LE_STEP_SAW");
        sizePolicy1.setHeightForWidth(LE_STEP_SAW->sizePolicy().hasHeightForWidth());
        LE_STEP_SAW->setSizePolicy(sizePolicy1);
        LE_STEP_SAW->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(LE_STEP_SAW, 1, 1, 1, 1);

        L_STEP_SAW = new QLabel(frame_4);
        L_STEP_SAW->setObjectName("L_STEP_SAW");

        gridLayout_10->addWidget(L_STEP_SAW, 1, 0, 1, 1);

        LE_A_SAW = new QLineEdit(frame_4);
        LE_A_SAW->setObjectName("LE_A_SAW");
        sizePolicy1.setHeightForWidth(LE_A_SAW->sizePolicy().hasHeightForWidth());
        LE_A_SAW->setSizePolicy(sizePolicy1);
        LE_A_SAW->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(LE_A_SAW, 0, 1, 1, 1);

        L_A_SAW = new QLabel(frame_4);
        L_A_SAW->setObjectName("L_A_SAW");

        gridLayout_10->addWidget(L_A_SAW, 0, 0, 1, 1);

        L_COUNT_SAW = new QLabel(frame_4);
        L_COUNT_SAW->setObjectName("L_COUNT_SAW");

        gridLayout_10->addWidget(L_COUNT_SAW, 2, 0, 1, 1);

        LE_COUNT_SAW = new QLineEdit(frame_4);
        LE_COUNT_SAW->setObjectName("LE_COUNT_SAW");
        sizePolicy1.setHeightForWidth(LE_COUNT_SAW->sizePolicy().hasHeightForWidth());
        LE_COUNT_SAW->setSizePolicy(sizePolicy1);
        LE_COUNT_SAW->setMaximumSize(QSize(60, 16777215));

        gridLayout_10->addWidget(LE_COUNT_SAW, 2, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_10, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_11->addItem(verticalSpacer_4, 3, 0, 1, 1);


        gridLayout_12->addWidget(frame_4, 1, 1, 1, 1);


        gridLayout_14->addLayout(gridLayout_12, 4, 0, 1, 1);

        PB_TEST = new QPushButton(centralwidget);
        PB_TEST->setObjectName("PB_TEST");

        gridLayout_14->addWidget(PB_TEST, 5, 0, 1, 1);

        LE_TEST_FILENAME = new QLineEdit(centralwidget);
        LE_TEST_FILENAME->setObjectName("LE_TEST_FILENAME");
        LE_TEST_FILENAME->setEnabled(false);
        sizePolicy1.setHeightForWidth(LE_TEST_FILENAME->sizePolicy().hasHeightForWidth());
        LE_TEST_FILENAME->setSizePolicy(sizePolicy1);

        gridLayout_14->addWidget(LE_TEST_FILENAME, 6, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_14);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        CP_TRAJECTORY = new QCustomPlot(centralwidget);
        CP_TRAJECTORY->setObjectName("CP_TRAJECTORY");
        sizePolicy.setHeightForWidth(CP_TRAJECTORY->sizePolicy().hasHeightForWidth());
        CP_TRAJECTORY->setSizePolicy(sizePolicy);
        CP_TRAJECTORY->setMinimumSize(QSize(341, 0));
        CP_TRAJECTORY->setStyleSheet(QString::fromUtf8("border: 1px solid #000;"));

        gridLayout->addWidget(CP_TRAJECTORY, 1, 0, 1, 1);

        L_TRAJECTORY_COORD = new QLabel(centralwidget);
        L_TRAJECTORY_COORD->setObjectName("L_TRAJECTORY_COORD");
        L_TRAJECTORY_COORD->setFont(font);

        gridLayout->addWidget(L_TRAJECTORY_COORD, 2, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        CP_VELOCITY_X = new QCustomPlot(centralwidget);
        CP_VELOCITY_X->setObjectName("CP_VELOCITY_X");
        CP_VELOCITY_X->setStyleSheet(QString::fromUtf8("border: 1px solid #000;"));

        gridLayout_2->addWidget(CP_VELOCITY_X, 0, 0, 1, 1);

        TB_LOG_X = new QTextBrowser(centralwidget);
        TB_LOG_X->setObjectName("TB_LOG_X");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(TB_LOG_X->sizePolicy().hasHeightForWidth());
        TB_LOG_X->setSizePolicy(sizePolicy2);
        TB_LOG_X->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(TB_LOG_X, 0, 1, 1, 1);

        CP_VELOCITY_Y = new QCustomPlot(centralwidget);
        CP_VELOCITY_Y->setObjectName("CP_VELOCITY_Y");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(CP_VELOCITY_Y->sizePolicy().hasHeightForWidth());
        CP_VELOCITY_Y->setSizePolicy(sizePolicy3);
        CP_VELOCITY_Y->setStyleSheet(QString::fromUtf8("border: 1px solid #000;"));

        gridLayout_2->addWidget(CP_VELOCITY_Y, 1, 0, 1, 1);

        TB_LOG_Y = new QTextBrowser(centralwidget);
        TB_LOG_Y->setObjectName("TB_LOG_Y");
        sizePolicy2.setHeightForWidth(TB_LOG_Y->sizePolicy().hasHeightForWidth());
        TB_LOG_Y->setSizePolicy(sizePolicy2);
        TB_LOG_Y->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(TB_LOG_Y, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        L_VELOCITY_COORD = new QLabel(centralwidget);
        L_VELOCITY_COORD->setObjectName("L_VELOCITY_COORD");
        L_VELOCITY_COORD->setFont(font);

        gridLayout_3->addWidget(L_VELOCITY_COORD, 2, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        QMW_MAIN->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QMW_MAIN);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1655, 24));
        QMW_MAIN->setMenuBar(menubar);
        statusbar = new QStatusBar(QMW_MAIN);
        statusbar->setObjectName("statusbar");
        QMW_MAIN->setStatusBar(statusbar);

        retranslateUi(QMW_MAIN);

        QMetaObject::connectSlotsByName(QMW_MAIN);
    } // setupUi

    void retranslateUi(QMainWindow *QMW_MAIN)
    {
        QMW_MAIN->setWindowTitle(QCoreApplication::translate("QMW_MAIN", "QMW_MAIN", nullptr));
        label->setText(QCoreApplication::translate("QMW_MAIN", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("QMW_MAIN", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \320\264\320\262\320\270\320\266\320\265\320\275\320\270\320\271", nullptr));
        CB_IGNORE_SUCCESS_QMB->setText(QCoreApplication::translate("QMW_MAIN", "\320\230\320\263\320\275\320\276\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265\n"
"\320\276\320\261 \321\203\321\201\320\277\320\265\321\205\320\265", nullptr));
        PB_CALC_MOTION->setText(QCoreApplication::translate("QMW_MAIN", "\320\240\320\260\320\267\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\264\320\262\320\270\320\266\320\265\320\275\320\270\321\217", nullptr));
        PB_CLEAR->setText(QCoreApplication::translate("QMW_MAIN", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        L_X0_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "X0", nullptr));
        L_Y0_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "Y0", nullptr));
        L_ANGLE_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        L_SEG_COUNT_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\320\276\321\200\320\276\320\275", nullptr));
        L_SEG_LENGTH_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "\320\240\320\260\320\264\320\270\321\203\321\201", nullptr));
        PB_GENERATE_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "\320\223\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        L_POLYGON->setText(QCoreApplication::translate("QMW_MAIN", "\320\237\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\320\265 n-\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\270", nullptr));
        PB_GENERATE_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\223\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        RB_SEGC_COUNT_3_TURN->setText(QCoreApplication::translate("QMW_MAIN", "3", nullptr));
        L_X0_TURN->setText(QCoreApplication::translate("QMW_MAIN", "X0", nullptr));
        L_Y0_TURN->setText(QCoreApplication::translate("QMW_MAIN", "Y0", nullptr));
        RB_SEGC_COUNT_2_TURN->setText(QCoreApplication::translate("QMW_MAIN", "2", nullptr));
        L_SEG3_LENGTH_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\224\320\273\320\270\320\275\320\260 \320\276\321\202\321\200\320\265\320\267\320\272\320\260 3", nullptr));
        L_ANGLE_DIV_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\240\320\260\320\267\320\261\320\270\320\265\320\275\320\270\320\265 \321\203\320\263\320\273\320\276\320\262", nullptr));
        L_SEG2_LENGTH_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\224\320\273\320\270\320\275\320\260 \320\276\321\202\321\200\320\265\320\267\320\272\320\260 2", nullptr));
        L_SEG1_LENGTH_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\224\320\273\320\270\320\275\320\260 \320\276\321\202\321\200\320\265\320\267\320\272\320\260 1", nullptr));
        L_CIRCLE_DIV_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\240\320\260\320\267\320\261\320\270\320\265\320\275\320\270\320\265\n"
"\320\276\320\272\321\200\321\203\320\266\320\275\320\276\321\201\321\202\320\270", nullptr));
        L_TURN->setText(QCoreApplication::translate("QMW_MAIN", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202\321\213", nullptr));
        L_POLYGON_2->setText(QCoreApplication::translate("QMW_MAIN", "\320\241\321\216\321\200\320\270\320\272\320\265\320\275\321\213", nullptr));
        PB_GENERATE_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "\320\223\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        L_OUTER_RADIUS_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "\320\222\320\275\320\265\321\210\320\275\320\270\320\271 \321\200\320\260\320\264\320\270\321\203\321\201", nullptr));
        L_SEG_COUNT_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\320\276\321\200\320\276\320\275", nullptr));
        L_X0_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "X0", nullptr));
        L_INNEAR_RADIUS_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "\320\222\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\320\271 \321\200\320\260\320\264\320\270\321\203\321\201", nullptr));
        L_Y0_NINJA->setText(QCoreApplication::translate("QMW_MAIN", "Y0", nullptr));
        PB_GENERATE_SAW->setText(QCoreApplication::translate("QMW_MAIN", "\320\223\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        L_POLYGON_3->setText(QCoreApplication::translate("QMW_MAIN", "\320\237\320\270\320\273\320\276\320\276\320\261\321\200\320\260\320\267\320\275\321\213\320\271 \321\201\320\270\320\263\320\275\320\260\320\273", nullptr));
        L_STEP_SAW->setText(QCoreApplication::translate("QMW_MAIN", "\320\250\320\260\320\263", nullptr));
        L_A_SAW->setText(QCoreApplication::translate("QMW_MAIN", "\320\220\320\274\320\277\320\273\320\270\321\202\321\203\320\264\320\260", nullptr));
        L_COUNT_SAW->setText(QCoreApplication::translate("QMW_MAIN", "\320\232\320\276\320\273-\320\262\320\276", nullptr));
        PB_TEST->setText(QCoreApplication::translate("QMW_MAIN", "\320\242\320\265\321\201\321\202", nullptr));
        label_3->setText(QCoreApplication::translate("QMW_MAIN", "\320\226\320\265\320\273\320\260\320\265\320\274\320\260\321\217 \321\202\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        L_TRAJECTORY_COORD->setText(QCoreApplication::translate("QMW_MAIN", "X: 0 Y: 0", nullptr));
        label_4->setText(QCoreApplication::translate("QMW_MAIN", "TextLabel", nullptr));
        L_VELOCITY_COORD->setText(QCoreApplication::translate("QMW_MAIN", "X: 0 Y: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QMW_MAIN: public Ui_QMW_MAIN {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMW_MAIN_H
