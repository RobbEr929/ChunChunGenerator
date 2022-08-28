#include "ShortcutKeysManager.h"

ShortcutKeysManager* ShortcutKeysManager::manager = nullptr;
QMutex ShortcutKeysManager::mutex;

ShortcutKeysManager *& ShortcutKeysManager::GetInstance()
{
    if(!manager)
    {
        QMutexLocker locker(&mutex);
        if(!manager)
        {
            manager = new(std::nothrow) ShortcutKeysManager;
        }
    }
    return manager;
}

void ShortcutKeysManager::DeleteInstance()
{
    QMutexLocker locker(&mutex);
    if(manager)
    {
        manager->deleteLater();
        manager = nullptr;
    }
}

ShortcutKeysManager::ShortcutKeysManager(QObject *parent)
    : QObject(parent)
{
}

ShortcutKeysManager::~ShortcutKeysManager()
{
}
