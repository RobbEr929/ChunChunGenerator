// /* ---------------------------------------------------------------------------------------
//  * CopyRight © 2022-2022 ZhongChun All rights reserved
//  * Website : RobbEr.ltd
//  * Github : github.com/RobbEr929
//  * Gitee : gitee.com/robber929
//  * ---------------------------------------------------------------------------------------
//  */

#include <QDir>
#include <QSettings>

#include "ConfigReader.h"

ConfigReader::ConfigReader(QObject *parent)
    : QObject(parent)
{
    InitMap();
    ReadConfig();
}

ConfigReader::~ConfigReader()
{
}

QString ConfigReader::GetValue(QString key)
{
    if (objectMap.contains(key))
    {
        return objectMap[key];
    }
    return "";
}

void ConfigReader::SetValue(QString key, QString value)
{
    objectMap[key] = value;
}

void ConfigReader::WriteConfig()
{
    QSettings settings(iniPath, QSettings::IniFormat);

    for (auto i : objectMap.keys())
    {
        settings.setValue(i, objectMap[i]);
    }
}

void ConfigReader::InitMap()
{
    objectMap["LowerCamelCaseEdit"] = "";
    objectMap["UpperCamelCaseEdit"] = "";
    objectMap["AllLowerEdit"] = "";
    objectMap["AllUpperEdit"] = "";
    objectMap["FirstUpperEdit"] = "";
    objectMap["AddUnderlineEdit"] = "";
    objectMap["GenerateEdit"] = "";
    objectMap["DisplayOrNotEdit"] = "";
    objectMap["QuitEdit"] = "";
}

inline void ConfigReader::ReadConfig()
{
    QDir dir;
    if (!dir.exists(QApplication::applicationDirPath() % "/conf"))
    {
        dir.mkdir(QApplication::applicationDirPath() % "/conf");
    }

    QSettings settings(iniPath, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    for (auto i : objectMap.keys())
    {
        objectMap[i] = settings.value(i).toString();
    }
}
