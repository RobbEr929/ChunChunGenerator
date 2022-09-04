// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef CCG_MAINWINDOW_H
#define CCG_MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "def.h"
#include "WorkWidget.h"
#include "OptionWidget.h"
#include "AboutWidget.h"

class MainWindow final
    : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    static MainWindow *&GetInstance();

    static Language nowLanguage;

protected:
    void closeEvent(QCloseEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;

    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;
private:
    inline bool LoadQss();

    inline bool InitWindow();

    inline bool InitSystemTrayIcon();

    inline bool InitConnect();

    inline bool InitConfig();

    inline void Show(int index = 0);

    inline void SetWindowTopHint(bool top);

    inline Language GetLanguage(int index);

    inline void SaveConfig();

    QMap<Theme, QString> themeMap;
    QTabWidget *tabWidget;
    WorkWidget *workWidget;
    OptionWidget *optionWidget;
    AboutWidget* aboutWidget;
    QSystemTrayIcon *systemTrayIcon;
    Theme nowTheme;
    double defocusValue;

    static MainWindow *mainWindow;
};

#endif // CCG_MAINWINDOW_H
