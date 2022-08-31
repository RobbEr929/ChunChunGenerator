// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#include "ShortcutEdit.h"

#include "InfoDialog.h"
#include "MainWindow.h"
#include "ShortcutKeysManager.h"

ShortcutEdit::ShortcutEdit(Action act, QWidget *parent)
    : QLineEdit(parent)
    , nowKey(nullptr)
{
    setProperty("Action", static_cast<qint8>(act));
    setObjectName(ActionToStr(act) % "Edit");
    setReadOnly(true);
}

ShortcutEdit::~ShortcutEdit()
{
}

bool ShortcutEdit::RegiserKey(QString key)
{
    QKeySequence keySequence(key);
    nowKey = ShortcutKeysManager::RegisterKey(this, &keySequence);
    SetText();
    if (nowKey != nullptr)
    {
        return true;
    }
    return false;
}

void ShortcutEdit::focusInEvent(QFocusEvent *event)
{
    SetText();
    QLineEdit::focusInEvent(event);
}

void ShortcutEdit::focusOutEvent(QFocusEvent *event)
{
    SetText();
    QLineEdit::focusOutEvent(event);
}

void ShortcutEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Exit)
    {
        SetText();
        qobject_cast<QWidget*>(parent())->setFocus();
        return;
    }
    if (event->key() == Qt::Key_Backspace)
    {
        setText("");
        ShortcutKeysManager::RegisterKey(this, new QPair<qint32, qint32>(), true);
        nowKey = nullptr;
        return;
    }
    inputKey = new QPair<qint32, qint32>(event->modifiers(), event->key());
    if (IsLegal(inputKey))
    {
        nowKey = ShortcutKeysManager::RegisterKey(this, inputKey);
        if (nowKey == nullptr)
        {
            InfoDialog::Show(MainWindow::GetInstance(), 2000, tr("Bind failed, the shortcuts are already bound"));
            return;
        }
        InfoDialog::Show(MainWindow::GetInstance(), 2000, tr("Bind success"));
        nowKey = inputKey;
        SetText();
        qobject_cast<QWidget*>(parent())->setFocus();
        return;
    }
    QLineEdit::keyPressEvent(event);
}

inline bool ShortcutEdit::IsLegal(QPair<qint32, qint32> *key)
{
    if (( key->first & Qt::ControlModifier
            || key->first & Qt::ShiftModifier
            || key->first & Qt::AltModifier )
        && ( key->second >= Qt::Key_0 && key->second <= Qt::Key_9
            || key->second >= Qt::Key_A && key->second <= Qt::Key_Z
            || key->second >= Qt::Key_F1 && key->second <= Qt::Key_F35
            || key->second >= Qt::Key_Left && key->second <= Qt::Key_Down
            || key->second == Qt::Key_Underscore ))
    {
        return true;
    }
    return false;
}

void ShortcutEdit::SetText()
{
    if (nowKey)
    {
        setText(
            ModifiersToStr(static_cast<Qt::KeyboardModifiers>(nowKey->first)) % QKeySequence(
                nowKey->second).toString());
        return;
    }
    setText("");
}
