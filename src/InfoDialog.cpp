#include <QTimer>
#include <QHBoxLayout>
#include <QScreen>
#include <QPainter>
#include <QApplication>

#include "InfoDialog.h"

void InfoDialog::Show(QWidget* parent, int sec, QString info)
{
    InfoDialog* dlg = new InfoDialog(parent);
    dlg->infoLabel->clear();
    dlg->infoLabel->setText(info);
    dlg->infoLabel->adjustSize();

    QPoint positon = QPoint(0, 0);
    QSize size = QApplication::primaryScreen()->availableGeometry().size();
    if(parent)
    {
        if(dlg->parent() == nullptr)
        {
            dlg->setParent(parent);
        }
        positon = parent->pos();
        size = parent->size();
    }
    positon.setX(positon.x() + (size.width() - dlg->width()) / 2);
    positon.setY(positon.y() + (size.height() - dlg->height() - 20));
    dlg->move(positon);
    dlg->show();
    dlg->raise();
    QTimer::singleShot(sec, dlg, [&dlg]()
    {
        dlg->deleteLater();
        dlg = nullptr;
    });
}

void InfoDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::yellow));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 15, 15);

    QDialog::paintEvent(event);
}

InfoDialog::InfoDialog(QWidget *parent)
    : QDialog(parent)
    , iconLabel(new QLabel(this))
    , infoLabel(new QLabel(this))
{
    setFixedHeight(60);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setWindowFlags(Qt::ToolTip);

    QPixmap pixmap(":/image/dlg_info_icon.png");
    iconLabel->setPixmap(pixmap);
    iconLabel->setAttribute(Qt::WA_TranslucentBackground);

    QFont font;
    font.setPointSize(12);
    infoLabel->setFont(font);
    infoLabel->setWordWrap(false);
    infoLabel->setAttribute(Qt::WA_TranslucentBackground);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(iconLabel);
    hLayout->addWidget(infoLabel);
    hLayout->addStretch(1);
    setLayout(hLayout);
}

InfoDialog::~InfoDialog()
{
}
