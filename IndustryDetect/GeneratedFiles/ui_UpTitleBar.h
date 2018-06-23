/********************************************************************************
** Form generated from reading UI file 'UpTitleBar.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPTITLEBAR_H
#define UI_UPTITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UpTitleBar
{
public:

    void setupUi(QWidget *UpTitleBar)
    {
        if (UpTitleBar->objectName().isEmpty())
            UpTitleBar->setObjectName(QStringLiteral("UpTitleBar"));
        UpTitleBar->resize(400, 300);

        retranslateUi(UpTitleBar);

        QMetaObject::connectSlotsByName(UpTitleBar);
    } // setupUi

    void retranslateUi(QWidget *UpTitleBar)
    {
        UpTitleBar->setWindowTitle(QApplication::translate("UpTitleBar", "UpTitleBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UpTitleBar: public Ui_UpTitleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPTITLEBAR_H
