// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QApplication>
#include <QStringBuilder>

#include "def.h"


class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QObject *parent = nullptr);

    ~ConfigReader() override;

    QString GetValue(QString key);

    void SetValue(QString key, QString value);

    void WriteConfig();

private:
    inline void InitMap();

    inline void ReadConfig();

    const QString iniPath = QApplication::applicationDirPath() % "/conf/ccg.ini";

    QMap<QString, QString> objectMap;
};

#endif // CONFIGREADER_H
