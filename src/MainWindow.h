#ifndef CCG_MAINWINDOW_H
#define CCG_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
#include <QSystemTrayIcon>

#include "def.h"
#include "WorkWidget.h"
#include "OptionWidget.h"
class MainWindow final
    : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    static Language nowLanguage;

protected:
    void closeEvent(QCloseEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
private:
    inline bool LoadQss();

    inline bool InitWindow();

    inline bool InitSystemTrayIcon();

    inline bool InitConnect();

    inline void Show(int index = 0);

    inline void SetWindowTopHint(bool top);

    inline Language GetLanguage(int index);

    QMap<Theme, QString> themeMap;
    QTabWidget *tabWidget;
    WorkWidget *workWidget;
    OptionWidget *optionWidget;
    QSystemTrayIcon* systemTrayIcon;
    Theme nowTheme;
};


#endif // CCG_MAINWINDOW_H
