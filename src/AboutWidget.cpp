// --------------------------------------------------------------------------------------
// CopyRight © 2022-2022 ZhongChun All rights reserved
// Website : RobbEr.ltd
// Github : github.com/RobbEr929
// Gitee : gitee.com/robber929
// 
// Project : ChunChunGenerator
// File : AboutWidget.cpp
// 
// Create On : 2022-09-04 下午 3:53
// Last Update : 2022-09-04 下午 4:31
// ---------------------------------------------------------------------------------------

#include "AboutWidget.h"

#include <QApplication>
#include <QUrl>
#include <QFile>
#include <QStringBuilder>
#include <QDesktopServices>
#include <qevent.h>
#include <QHBoxLayout>

HelpLabel::HelpLabel(QString text, QWidget *parent)
    : QLabel(text, parent)
{
    QFont font;
    font.setUnderline(true);
    setFont(font);
}

HelpLabel::~HelpLabel()
{
}

void HelpLabel::SetLocalUrl(const QString &url)
{
    localUrl = url;
}

void HelpLabel::SetNetWorkUrl(const QString &url)
{
    networkUrl = url;
}

void HelpLabel::mousePressEvent(QMouseEvent *event)
{
    QFile file(localUrl);
    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(file.fileName()));
        return;
    }
    QDesktopServices::openUrl(QUrl(networkUrl));
}

void HelpLabel::mouseMoveEvent(QMouseEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
}

AboutWidget::AboutWidget(QWidget *parent)
    : QWidget(parent)
    , iconLabel(new QLabel(this))
    , nameLabel(new QLabel(tr("ChunChunGenerator"), this))
    , versionLabel(new QLabel(tr("Version") % " V 0.0.5", this))
    , copyRightLabel(new QLabel(this))
    , helpLabel(new HelpLabel(tr("get help"), this))
{
    iconLabel->setPixmap(QPixmap::fromImage(QImage(":/image/ccg_icon.png")));

    copyRightLabel->setOpenExternalLinks(true);
    auto s = new ushort[2];
    s[0] = 0x00A9;
    s[1] = 0;
    QString copyRightStr = "Copyright" % QString::fromUtf16(s) % " 2022 " % "ZhongChun. All rights reserved.";
    copyRightLabel->setText(QString("<a href = %1>%2</a>").arg("\"https://robber.ltd/\"").arg(copyRightStr));

    helpLabel->SetLocalUrl(QApplication::applicationDirPath() % tr("/../ReadMe.md"));
    helpLabel->SetNetWorkUrl(tr("https://robber.ltd/2022/09/04/chunchungenerator-help/"));

    auto hBoxLayout = new QHBoxLayout;
    hBoxLayout->addStretch(1);
    hBoxLayout->addWidget(iconLabel);
    hBoxLayout->addWidget(nameLabel);
    hBoxLayout->addStretch(1);

    auto vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addStretch(1);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->addWidget(versionLabel, 0, Qt::AlignCenter);
    vBoxLayout->addWidget(copyRightLabel, 0, Qt::AlignCenter);
    vBoxLayout->addWidget(helpLabel, 0, Qt::AlignCenter);
    vBoxLayout->addStretch(1);
}

AboutWidget::~AboutWidget()
{
}

bool AboutWidget::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}
