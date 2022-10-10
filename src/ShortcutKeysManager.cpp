// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#include "ShortcutKeysManager.h"

#include "MainWindow.h"

ShortcutKeysManager *ShortcutKeysManager::manager = nullptr;
QMutex ShortcutKeysManager::mutex;

ShortcutKeysManager *&ShortcutKeysManager::GetInstance()
{
    if (!manager)
    {
        QMutexLocker locker(&mutex);
        if (!manager)
        {
            manager = new(std::nothrow) ShortcutKeysManager;
        }
    }
    return manager;
}

void ShortcutKeysManager::DeleteInstance()
{
    QMutexLocker locker(&mutex);
    if (manager)
    {
        manager->deleteLater();
        manager = nullptr;
    }
}

QPair<qint32, qint32> *ShortcutKeysManager::RegisterKey(ShortcutEdit *edit, QPair<qint32, qint32> *key, bool del)
{
    auto action = static_cast<Action>(edit->property("Action").toInt());

    if (del)
    {
        QMutexLocker locker(&mutex);

        LOG(DEBUG) << QString(edit->objectName() % "unbind");
        GetInstance()->actionMap[action]->deleteLater();
        GetInstance()->actionMap[action] = nullptr;
        GetInstance()->editMap[action] = edit;
        GetInstance()->keyMap.remove(action);

        return nullptr;
    }

    QHotkey *hotkey = new QHotkey(static_cast<Qt::Key>(key->second),
                                  static_cast<Qt::KeyboardModifiers>(key->first),
                                  true,
                                  MainWindow::GetInstance());

    LOG(DEBUG) << QString(
        edit->objectName() % " bind " % ModifiersToStr(static_cast<Qt::KeyboardModifiers>(key->first)) %
        QKeySequence(key->second).toString());
    if (GetInstance()->keyMap.values().contains(*key))
    {
        LOG(INFO) << QString(edit->objectName() % tr("Bind failed, the shortcuts are already bound"));
        hotkey->deleteLater();
        hotkey = nullptr;
        return nullptr;
    }

    QMutexLocker locker(&mutex);

    GetInstance()->actionMap[action] = hotkey;
    GetInstance()->editMap[action] = edit;
    GetInstance()->keyMap.insert(action, qMakePair(key->first, key->second));
    connect(hotkey, &QHotkey::activated, MainWindow::GetInstance(), MainWindow::GetInstance()->SlotFunction(edit->GetAction()));

    return new QPair<int, int>(key->first, key->second);
}

QPair<qint32, qint32> *ShortcutKeysManager::RegisterKey(ShortcutEdit *edit, QKeySequence *key, bool del)
{
    auto action = static_cast<Action>(edit->property("Action").toInt());

    if (del)
    {
        QMutexLocker locker(&mutex);

        LOG(DEBUG) << QString(edit->objectName() % "unbind");

        GetInstance()->actionMap[action]->deleteLater();
        GetInstance()->actionMap[action] = nullptr;
        GetInstance()->editMap[action] = edit;
        GetInstance()->keyMap.remove(action);

        return nullptr;
    }

    QHotkey *hotkey = new QHotkey(*key, true, MainWindow::GetInstance());

    LOG(DEBUG) << QString(
        edit->objectName() % " bind " % ModifiersToStr(static_cast<Qt::KeyboardModifiers>(hotkey->modifiers())) %
        QKeySequence(hotkey->keyCode()).toString());

    if (GetInstance()->keyMap.values().contains(qMakePair(hotkey->modifiers(), hotkey->keyCode())))
    {
        LOG(INFO) << QString(edit->objectName() % tr("Bind failed, the shortcuts are already bound"));
        hotkey->deleteLater();
        hotkey = nullptr;
        return nullptr;
    }

    QMutexLocker locker(&mutex);

    GetInstance()->actionMap[action] = hotkey;
    GetInstance()->editMap[action] = edit;
    GetInstance()->keyMap.insert(action, qMakePair(hotkey->modifiers(), hotkey->keyCode()));
    connect(hotkey, &QHotkey::activated, MainWindow::GetInstance(), MainWindow::GetInstance()->SlotFunction(edit->GetAction()));

    return new QPair<int, int>(hotkey->modifiers(), hotkey->keyCode());
}

ShortcutKeysManager::ShortcutKeysManager(QObject *parent)
    : QObject(parent)
{
}

ShortcutKeysManager::~ShortcutKeysManager()
{
}
