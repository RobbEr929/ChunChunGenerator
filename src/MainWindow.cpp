#include <QRegExpValidator>
#include <QFile>
#include <QMetaObject>
#include <QClipboard>
#include <QApplication>
#include <QString>
#include <QMenu>
#include <QScreen>
#include <QComboBox>
#include <QMessageBox>
#include <QtWidgets/QHBoxLayout>

#include "MainWindow.h"

#include "easylogging++.h"
#include "InfoDialog.h"

Language MainWindow::nowLanguage = Language::UnInstall;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tabWidget(new QTabWidget(this))
    , workWidget(new WorkWidget(this))
    , optionWidget(new OptionWidget(this))
    , systemTrayIcon(new QSystemTrayIcon(QIcon(":/image/ccg_icon.png"), this))
{
    if (!LoadQss())
    {
        LOG(INFO) << tr("Load Qss Failed");
    }
    InitWindow();
    if (!InitSystemTrayIcon())
    {
        LOG(INFO) << tr("Init System Tray Icon Failed");
    }
    InitConnect();
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    static bool firstClose = true;
    if (firstClose && !optionWidget->minimizeWhenCloseBox->isChecked())
    {
        QMessageBox box(QMessageBox::Information,
            tr("Confirm to quit?"),
            tr(
                "confirm exit? Click \'Yes\' to exit, click \'No\' to minimize to tray, click \'Cancel\' to close the dialog"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        box.setButtonText(QMessageBox::Yes, tr("Yes"));
        box.setButtonText(QMessageBox::No, tr("No"));
        box.setButtonText(QMessageBox::Cancel, tr("Cancel"));

        switch (box.exec())
        {
        case QMessageBox::Yes:
            {
                qApp->exit(0);
                return;
            }
        case QMessageBox::No:
            {
                firstClose = false;
                systemTrayIcon->show();
                optionWidget->minimizeWhenCloseBox->setChecked(true);
                hide();
                return;
            }
            break;
        case QMessageBox::Cancel:
        default:
            {
                event->ignore();
                break;
            }
        }
    }
    else if (optionWidget->minimizeWhenCloseBox->isChecked())
    {
        systemTrayIcon->show();
        optionWidget->minimizeWhenCloseBox->setChecked(true);
        hide();
        return;
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::focusInEvent(QFocusEvent *event)
{
    if(tabWidget->currentIndex() == 0)
    {
        workWidget->focusInEvent(event);
    }
    QMainWindow::focusInEvent(event);
}

inline bool MainWindow::LoadQss()
{
    QFile file;

    file.setFileName(lightPath);
    if (file.open(QFile::ReadOnly))
    {
        themeMap[Theme::Light] = file.readAll();
    }
    file.close();

    file.setFileName(defaultPath);
    if (file.open(QFile::ReadOnly))
    {
        themeMap[Theme::Dark] = file.readAll();
    }
    file.close();

    setStyleSheet(themeMap.first());
    nowTheme = themeMap.firstKey();

    return !themeMap.isEmpty();
}

inline bool MainWindow::InitWindow()
{
    try
    {
        qApp->setQuitOnLastWindowClosed(false);

        setFixedSize(560, 315);
        setWindowIcon(QIcon(":/image/ccg_icon.png"));
        move(QApplication::primaryScreen()->availableGeometry().width() - width(), 0);
        setWindowTitle(tr("ChunChunGenerator"));
        setWindowFlags(Qt::Tool | Qt::X11BypassWindowManagerHint);
        SetWindowTopHint(true);

        tabWidget->setFixedSize(size());
        tabWidget->addTab(workWidget, tr("Generator"));
        tabWidget->addTab(optionWidget, tr("Option"));
        tabWidget->tabBar()->setMinimumWidth(size().width() * 0.5);
    }
    catch (std::bad_alloc)
    {
        LOG(INFO) << tr("bad alloc");
        return false;
    }
    return true;
}

inline bool MainWindow::InitSystemTrayIcon()
{
    try
    {
        auto trayMenu = new QMenu(this);
        trayMenu->addAction(tr("Open the main tab"),
                            [this]()
                            {
                                Show();
                            });
        trayMenu->addAction(tr("Open the Option tab"),
                            [this]()
                            {
                                Show(1);
                            });
        trayMenu->addAction(tr("Exit"),
                            [this]()
                            {
                                qApp->exit(0);
                            });

        systemTrayIcon->show();
        systemTrayIcon->setToolTip(tr("ChunChunGenerator, a improve productivity tool"));
        systemTrayIcon->setContextMenu(trayMenu);

        connect(systemTrayIcon,
                &QSystemTrayIcon::activated,
                this,
                [this, trayMenu](QSystemTrayIcon::ActivationReason reason)
                {
                    switch (reason)
                    {
                    case QSystemTrayIcon::Context:
                        {
                            trayMenu->show();
                            break;
                        }
                    case QSystemTrayIcon::DoubleClick:
                    case QSystemTrayIcon::Trigger:
                    case QSystemTrayIcon::MiddleClick:
                        {
                            Show();
                            break;
                        }
                    case QSystemTrayIcon::Unknown:
                    default:
                        break;
                    }
                });
    }
    catch (std::bad_alloc)
    {
        LOG(INFO) << tr("bad alloc");
        return false;
    }
    return true;
}

bool MainWindow::InitConnect()
{
    connect(optionWidget->pasteWhenGetFocusBox,
            &QCheckBox::stateChanged,
            this,
            [this](int index)
            {
                workWidget->pasteWhenGetFocus = index;
                InfoDialog::Show(this);
            });

    connect(optionWidget->copyWhenWorkOverBox,
            &QCheckBox::stateChanged,
            this,
            [this](int index)
            {
                workWidget->copyWhenWorkOver = index;
                InfoDialog::Show(this);
            });

    connect(optionWidget->windowTopHintBox,
            &QCheckBox::stateChanged,
            this,
            [this](int index)
            {
                SetWindowTopHint(index);
                Show(tabWidget->currentIndex());
                InfoDialog::Show(this);
                return;
            });

    connect(optionWidget->multilineInput,
            &QCheckBox::stateChanged,
            this,
            [this](int index)
            {
                optionWidget->copyWhenClickBox->setEnabled(index);
                workWidget->UpdateInputArea(index);
                update();
                InfoDialog::Show(this);
                return;
            });

    connect(optionWidget->copyWhenClickBox,
            &QCheckBox::stateChanged,
            this,
            [this](int index)
            {
            workWidget->copyWhenClick = index;
            InfoDialog::Show(this);
                return;
            });


    connect(optionWidget->themeBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            [this](int index)
            {
                auto newTheme = static_cast<Theme>(index);
                if (nowTheme != newTheme && themeMap.contains(newTheme))
                {
                    nowTheme = newTheme;
                    setStyleSheet(themeMap[newTheme]);
                    update();
                    InfoDialog::Show(this);
                }
            });

    connect(optionWidget->languageBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            [this](int index)
            {
                auto language = GetLanguage(index);
                if (nowLanguage != language)
                {
                    QMessageBox box(QMessageBox::Information,
                                    tr("Confirm to modify the language?"),
                                    tr("Confirm to modify the language? After modification, it will restart automatically"),
                                    QMessageBox::Yes | QMessageBox::No);
                    box.setButtonText(QMessageBox::Yes, tr("Yes"));
                    box.setButtonText(QMessageBox::No, tr("No"));

                    if (box.exec() == QMessageBox::Yes)
                    {
                        qApp->exit(static_cast<int>(language));
                    }
                    optionWidget->languageBox->setCurrentIndex(index == 0 ? 1 : 0);
                }
            });
    return true;
}

inline void MainWindow::Show(int index)
{
    if (index == 1)
    {
        tabWidget->setCurrentIndex(1);
        if (isVisible())
        {
            activateWindow();
            return;
        }
        show();
        return;
    }
    tabWidget->setCurrentIndex(0);
    if (isVisible())
    {
        activateWindow();
        return;
    }
    show();
}

void MainWindow::SetWindowTopHint(bool top)
{
    if(top && !(windowFlags() & Qt::WindowStaysOnTopHint))
    {
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
        return;
    }
    else if(windowFlags() & Qt::WindowStaysOnTopHint)
    {
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    }
}

inline Language MainWindow::GetLanguage(int index)
{
    if (index == 0)
    {
        return Language::Chinese;
    }
    return Language::English;
}
