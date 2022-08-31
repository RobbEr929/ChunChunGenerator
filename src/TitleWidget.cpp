// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#include "TitleWidget.h"

TitleWidget::TitleWidget(QString title, QWidget *object, QWidget *parent)
    : QWidget(parent)
    , hBoxLayout(new QHBoxLayout(this))
    , titleLabel(new QLabel(title, this))
    , widget(object)
{
    widget->setParent(this);

    hBoxLayout->addStretch(1);
    hBoxLayout->addWidget(titleLabel);
    hBoxLayout->addWidget(widget);
    hBoxLayout->addStretch(1);

    setLayout(hBoxLayout);
}

TitleWidget::~TitleWidget()
{
}

QWidget *TitleWidget::Object() const
{
    return widget;
}
