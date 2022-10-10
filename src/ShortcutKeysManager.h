// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef CCG_SHORTCUTKEYSMANAGER_H
#define CCG_SHORTCUTKEYSMANAGER_H

#include <QMutex>

#include "def.h"
#include "ShortcutEdit.h"
#include "qhotkey.h"

class ShortcutKeysManager final
    : public QObject
{
    Q_OBJECT
public:
    static ShortcutKeysManager *&GetInstance();

    static void DeleteInstance();

    static QPair<qint32, qint32> *RegisterKey(ShortcutEdit *edit, QPair<qint32, qint32> *key, bool del = false);

    static QPair<qint32, qint32> *RegisterKey(ShortcutEdit *edit, QKeySequence *key, bool del = false);

private:
    static ShortcutKeysManager *manager;
    static QMutex mutex;

    explicit ShortcutKeysManager(QObject *parent = nullptr);

    ~ShortcutKeysManager() override;

    QMap<Action, QObject*> actionMap;
    QMap<Action, ShortcutEdit*> editMap;
    QMap<Action, QPair<qint32, qint32>> keyMap;
};

#endif // CCG_SHORTCUTKEYSMANAGER_H
