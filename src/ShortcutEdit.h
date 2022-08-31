// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H

#include <QLineEdit>

#include "ConfigReader.h"
#include "def.h"

class ShortcutEdit final
    : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortcutEdit(Action act, QWidget *parent = nullptr);

    ~ShortcutEdit() override;

    bool RegiserKey(QString key);

protected:
    void focusInEvent(QFocusEvent *event) override;

    void focusOutEvent(QFocusEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    inline bool IsLegal(QPair<qint32, qint32> *key);

    inline void SetText();

    QPair<qint32, qint32> *inputKey;
    QPair<qint32, qint32> *nowKey;
};

#endif // SHORTCUTEDIT_H
