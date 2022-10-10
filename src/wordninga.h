#ifndef SRC_WORDNINJA_H
#define SRC_WORDNINJA_H

#include <QMap>
#include <QFile>
#include <QObject>
#include <QVector>
#include <QString>

class WordNinga
    : public QObject
{
    Q_OBJECT

public:
    WordNinga();

    ~WordNinga();

    QVector<QString> WordNinga::split(const QString& inputText);

    void SetUseDigit(bool use);

    int AddWordToDigit(const QString& word);

    int RemoveWordToDigit(const QString& word);

public slots:
    void Init();

private:
    inline bool isDigit(const QString& str);

    void RemoveWordInFile(const QString& word);

private:
    QFile* mFileBuffer;
    QMap<QString, float> mDict;
    int mWordMaxLen;
    bool mIsReady;
    bool mUseDigit;
};



#endif