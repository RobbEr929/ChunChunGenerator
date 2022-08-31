// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef CCG_TITLEWIDGET_H
#define CCG_TITLEWIDGET_H
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QString title, QWidget *object, QWidget *parent = nullptr);

    ~TitleWidget() override;

    QWidget *Object() const;

private:
    QHBoxLayout *hBoxLayout;
    QLabel *titleLabel;
    QWidget *widget;
};

#endif // CCG_TITLEWIDGET_H
