#include <QApplication>
#include <QDir>
#include <QStringBuilder>
#include <QTextCodec>
#include <QTranslator>
#include <QMessageBox>
#include "easylogging++.h"
#include "MainWindow.h"

INITIALIZE_EASYLOGGINGPP;

inline bool LoadTranslate(Language language)
{
    QTranslator *translateChinese = new QTranslator(qApp);
    translateChinese->load(qApp->applicationDirPath() + "/translations/ccg_zh.qm");
    QTranslator *translateEnglish = new QTranslator(qApp);
    translateEnglish->load(qApp->applicationDirPath() + "/translations/ccg_en.qm");

    switch (language)
    {
    case Language::Chinese:
        {
        if (MainWindow::nowLanguage != Language::Chinese && MainWindow::nowLanguage != Language::UnInstall)
        {
            qApp->removeTranslator(translateEnglish);
        }
        return qApp->installTranslator(translateChinese);
        }
    case Language::English:
    default:
        {
        if (MainWindow::nowLanguage != Language::English && MainWindow::nowLanguage != Language::UnInstall)
        {
            qApp->removeTranslator(translateChinese);
        }
        return qApp->installTranslator(translateEnglish);
        }
    }
}

inline void LoadLog(int argc, char** argv)
{
    START_EASYLOGGINGPP(argc, argv);
    QString logPath = QCoreApplication::applicationDirPath() % "/logs";
    QString logName = QCoreApplication::applicationDirPath() % "/logs/log_%datetime{%Y%M%d}.log";
    QDir dir;
    if (!dir.exists(logPath))
        dir.mkdir(logPath);

    el::Configurations conf;
    conf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime %msg");
    conf.set(el::Level::Global, el::ConfigurationType::Filename, logName.toStdString());
    conf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
    conf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
#if defined(_DEBUG)|| defined(DEBUG)
    conf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "true");
#else
    conf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");
#endif
    conf.set(el::Level::Global, el::ConfigurationType::SubsecondPrecision, "0");
    conf.set(el::Level::Global, el::ConfigurationType::PerformanceTracking, "true");
    conf.set(el::Level::Global, el::ConfigurationType::MaxLogFileSize, "1024000");
    conf.set(el::Level::Global, el::ConfigurationType::LogFlushThreshold, "1");
    el::Loggers::reconfigureAllLoggers(conf);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
}

int main(int argc, char** argv)
{
    // 默认中文
    int result = 0xff;
    while (result != 0)
    {
        QApplication app(argc, argv);

        LoadLog(argc, argv);

        Language language = static_cast<Language>(result);
        
        if(LoadTranslate(language))
        {
            MainWindow::nowLanguage = language;
        }

        MainWindow mainWindow;
        mainWindow.show();
        result = app.exec();
    }
	return result;
}