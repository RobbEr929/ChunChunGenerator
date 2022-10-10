// --------------------------------------------------------------------------------------
// CopyRight © 2022-2022 ZhongChun All rights reserved
// Website : RobbEr.ltd
// Github : github.com/RobbEr929
// Gitee : gitee.com/robber929
// 
// Project : ChunChunGenerator
// File : def.h
// 
// Create On : 2022-08-26 下午 6:27
// Last Update : 2022-08-31 下午 7:15
// ---------------------------------------------------------------------------------------

#ifndef CCG_DEF_H
#define CCG_DEF_H

#include "easylogging++.h"

// 语言
enum class Language : uint8_t
{
    UnInstall = 0,
    // 中文
    Chinese = 0xff,
    English = 0xaa,
};

// 主题
enum class Theme : int8_t
{
    // 明亮
    Light = 0,
    // 黑暗
    Dark,
};

const QString defaultPath = ":/qdarkstyle/dark/darkstyle.qss";
const QString lightPath = ":/qdarkstyle/light/lightstyle.qss";

enum class Action : qint8
{
    UNKNOWN = 0,
    LowerCamelCase,
    UpperCamelCase,
    AllLower,
    AllUpper,
    FirstUpper,
    AddUnderline,
    Generate,
    DisplayOrNot,
    Quit,
};

inline QString ActionToStr(Action action)
{
    switch (action)
    {
    case Action::LowerCamelCase:
        return "LowerCamelCase";
    case Action::UpperCamelCase:
        return "UpperCamelCase";
    case Action::AllLower:
        return "AllLower";
    case Action::AllUpper:
        return "AllUpper";
    case Action::FirstUpper:
        return "FirstUpper";
    case Action::AddUnderline:
        return "AddUnderline";
    case Action::Generate:
        return "Generate";
    case Action::DisplayOrNot:
        return "DisplayOrNot";
    case Action::Quit:
        return "Quit";
    case Action::UNKNOWN:
    default:
        return "UNKNOWN";
    }
}

inline QString ModifiersToStr(Qt::KeyboardModifiers modifiers)
{
    QString str;
    if (modifiers & Qt::ControlModifier)
    {
        str.append("Ctrl+");
    }
    if (modifiers & Qt::ShiftModifier)
    {
        str.append("Shift+");
    }
    if (modifiers & Qt::AltModifier)
    {
        str.append("Alt+");
    }
    return str;
}

inline int ModifiersToKey(Qt::KeyboardModifiers modifiers)
{
    int key = 0;
    if (modifiers & Qt::ControlModifier)
    {
        key += Qt::CTRL;
    }
    if (modifiers & Qt::ShiftModifier)
    {
        key += Qt::SHIFT;
    }
    if (modifiers & Qt::AltModifier)
    {
        key += Qt::ALT;
    }
    return key;
}

#endif // CCG_DEF_H
