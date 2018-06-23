/********************************************************************************
** Form generated from reading UI file 'IndustryDetect.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDUSTRYDETECT_H
#define UI_INDUSTRYDETECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IndustryDetectClass
{
public:

    void setupUi(QWidget *IndustryDetectClass)
    {
        if (IndustryDetectClass->objectName().isEmpty())
            IndustryDetectClass->setObjectName(QStringLiteral("IndustryDetectClass"));
        IndustryDetectClass->resize(600, 400);

        retranslateUi(IndustryDetectClass);

        QMetaObject::connectSlotsByName(IndustryDetectClass);
    } // setupUi

    void retranslateUi(QWidget *IndustryDetectClass)
    {
        IndustryDetectClass->setWindowTitle(QApplication::translate("IndustryDetectClass", "IndustryDetect", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IndustryDetectClass: public Ui_IndustryDetectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDUSTRYDETECT_H
