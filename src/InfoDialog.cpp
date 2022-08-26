#include <QTimer>
#include <QHBoxLayout>

#include "InfoDialog.h"


InfoDialog* InfoDialog::dlg = nullptr;
QMutex InfoDialog::mutex;

void InfoDialog::Show(QPoint positon, QSize size, int sec, QString info)
{
    if(!dlg)
    {
        QMutexLocker locker(&mutex);
        if(!dlg)
        {
            dlg = new(std::nothrow) InfoDialog;
        }
    }
    dlg->infoLabel->clear();
    dlg->infoLabel->setText(info);

    positon.setX(positon.x() + (size.width() - dlg->width()) / 2);
    positon.setY(positon.y() + (size.height() - dlg->width() - 20));
    dlg->move(positon);
    dlg->show();
    QTimer::singleShot(sec, dlg, &InfoDialog::hide);
}

InfoDialog::InfoDialog()
    :QDialog(nullptr)
    ,infoLabel(new QLabel(this))
{
    setFixedWidth(140);

    QFont font;
    font.setPointSize(16);
    infoLabel->setFont(font);
    infoLabel->setWordWrap(true);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(infoLabel);
    hLayout->addStretch(1);
    setLayout(hLayout);
}

InfoDialog::~InfoDialog()
{
}
