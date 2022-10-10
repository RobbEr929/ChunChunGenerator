// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef CCG_OPTIONWIDGET_H
#define CCG_OPTIONWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QTabWidget>
#include <QScrollArea>
#include <QPushButton>

#include "def.h"
#include "ConfigReader.h"
#include "TitleWidget.h"

class OptionWidget final
    : public QWidget
{
    Q_OBJECT
public:
    explicit OptionWidget(QWidget *parent = nullptr);

    ~OptionWidget() override;

    void ReadConfig() const;

    void SaveConfig() const;

private:
    QWidget *InitGeneralWidget();

    QWidget *InitIndividuationWidget();

    QWidget *InitShortcutWidget();

    QWidget *InitDictionaryWidget();

    QTabWidget *optionTabWidget;
    QCheckBox *pasteWhenGetFocusBox;
    QCheckBox *copyWhenWorkOverBox;
    QCheckBox *minimizeWhenCloseBox;
    QCheckBox *windowTopHintBox;
    QCheckBox *multilineInput;
    QCheckBox *copyWhenClickBox;
    QScrollArea *shortcutArea;
    TitleWidget* defocusWidget, * themeWidget, * languageWidget, * localWidget, * lccWdiget, * uccWidget, * alWidget, * auWdiget, * fuWidget,
        * aulWidget, * globalWidget, * gWdiget, * dWidget, * qWidget;
    QCheckBox* useDictionaryBox;
    QLabel* awtdLabel;
    QLineEdit* awtdEdit;
    QPushButton* awtdButton;
    QLabel* rwtdLabel;
    QLineEdit* rwtdEdit;
    QPushButton* rwtdButton;
    ConfigReader *configReader;
    friend class MainWindow;
};

#endif // CCG_OPTIONWIDGET_H
