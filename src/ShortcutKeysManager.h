#ifndef CCG_SHORTCUTKEYSMANAGER_H
#define CCG_SHORTCUTKEYSMANAGER_H
#include <QObject>
#include <QMap>
#include <QSet>
#include <QMutex>

#include "def.h"

// todo: complete this class
class ShortcutKeysManager final
    : public QObject
{
    Q_OBJECT
public:
    static ShortcutKeysManager*& GetInstance();

    static void DeleteInstance();

signals:

public slots:

private:
    static ShortcutKeysManager* manager;
    static QMutex mutex;
    explicit ShortcutKeysManager(QObject* parent = nullptr);

    ~ShortcutKeysManager() override;

    QMap<Action, QSet<QPair<Qt::Key, Qt::Key>>> actionMap;
};

#endif // CCG_SHORTCUTKEYSMANAGER_H
