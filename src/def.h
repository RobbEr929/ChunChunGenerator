#ifndef CCG_DEF_H
#define CCG_DEF_H

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

#endif // CCG_DEF_H
