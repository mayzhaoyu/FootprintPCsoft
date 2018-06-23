/********************************************************************************
** Form generated from reading UI file 'CorrectWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORRECTWIDGET_H
#define UI_CORRECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CorrectWidget
{
public:

    void setupUi(QWidget *CorrectWidget)
    {
        if (CorrectWidget->objectName().isEmpty())
            CorrectWidget->setObjectName(QStringLiteral("CorrectWidget"));
        CorrectWidget->resize(400, 300);

        retranslateUi(CorrectWidget);

        QMetaObject::connectSlotsByName(CorrectWidget);
    } // setupUi

    void retranslateUi(QWidget *CorrectWidget)
    {
        CorrectWidget->setWindowTitle(QApplication::translate("CorrectWidget", "CorrectWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CorrectWidget: public Ui_CorrectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORRECTWIDGET_H
