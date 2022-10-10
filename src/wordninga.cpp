// --------------------------------------------------------------------------------------
// CopyRight © 2022-2022 ZhongChun All rights reserved
// Website : RobbEr.ltd
// Github : github.com/RobbEr929
// Gitee : gitee.com/robber929
// 
// Project : ChunChunGenerator
// File : wordninja.cpp
// 
// Create On : 2022-10-10 下午 6:03
// Last Update : 2022-10-10 下午 6:12
// ---------------------------------------------------------------------------------------

#include "wordninga.h"

#include <QApplication>
#include <sstream>
#include <QTextStream>
#include <QDirIterator>
#include <QtConcurrent/QtConcurrent>

WordNinga::WordNinga()
    : mFileBuffer(nullptr)
    , mWordMaxLen(0)
    , mIsReady(false)
    , mUseDigit(true)
{
}

WordNinga::~WordNinga()
{
    if (mFileBuffer && mFileBuffer->isOpen())
    {
        mFileBuffer->close();
    }
}

void WordNinga::Init()
{
    mDict.clear();
    QDirIterator iterator(QApplication::applicationDirPath(), QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext())
    {
        iterator.next();
        if(!iterator.fileName().compare("wordninga.txt"))
        {
            mFileBuffer = new QFile(iterator.fileInfo().absoluteFilePath());
            QTextStream stream(mFileBuffer);
            if (!mFileBuffer->open(QIODevice::ReadOnly| QIODevice::Text))
            {
                return;
            }
            stream.seek(0);
            QString word;
            QVector<QString> words;
            words.reserve(20000);
            while (!stream.atEnd())
            {
                word = stream.readLine();
                if (!word.size())
                {
                    continue;
                }
                words.push_back(word);
            }

            int dictSize = words.size();
            for (int i = 0; i < words.size(); i++)
            {
                mDict[words[i]] = log((i + 1) * log(dictSize));
                mWordMaxLen = qMax(mWordMaxLen, words[i].length());
            }
            mIsReady = true;
            return;
        }
    }
}

QVector<QString> WordNinga::split(const QString &inputText)
{
    QVector<QString> result;
    result.clear();
    if (inputText.isEmpty())
        return result;
    if(!mIsReady || !mUseDigit)
    {
        bool first = true;
        int start = -1;
        int step = 0;
        QRegExp exp("[A-Z_\\s]");
        while (first || start != -1)
        {
            first = false;
            step = exp.indexIn(inputText, start + 1);
            QString key = inputText.mid(start, step == -1 ? -1 : step - start).simplified().remove('_');
            start = step;
            if (key.isEmpty())
            {
                continue;
            }
            result.push_back(key);
        }
        return result;
    }

    QString lowerStr = inputText.toLower();
    const int len = lowerStr.size();

    QVector<QPair<float, int>> cost;
    cost.reserve(len + 1);
    cost.push_back(qMakePair(0, -1));
    float curCost = 0.0;
    for (int i = 1; i < len + 1; i++)
    {
        float minCost = cost[i - 1].first + 9e9;
        int minCostIndex = i - 1;

        for (int j = i - mWordMaxLen > 0 ? i - mWordMaxLen : 0; j < i; j++)
        {
            QString subStr = lowerStr.mid(j, i - j);
            if (mDict.find(subStr) == mDict.end())
                continue;

            curCost = cost[j].first + mDict.value(subStr);
            if (minCost > curCost)
            {
                minCost = curCost;
                minCostIndex = j;
            }
        }
        cost.push_back(qMakePair(minCost, minCostIndex));
    }

    int n = len;
    int preIndex;
    while (n > 0)
    {
        preIndex = cost[n].second;
        QString insertStr = inputText.mid(preIndex, n - preIndex);
        if (!result.empty() && isDigit(insertStr + result[0]))
        {
            result[0] = insertStr + result[0];
        }
        else
        {
            result.insert(result.begin(), insertStr);
        }
        n = preIndex;
    }
    return result;
}

void WordNinga::SetUseDigit(bool use)
{
    mUseDigit = use;
}

int WordNinga::AddWordToDigit(const QString &word)
{
    if(word.isEmpty())
    {
        return 3;
    }
    if(!mFileBuffer || !mFileBuffer->isOpen())
    {
        return 1;
    }

    if(mDict.contains(word))
    {
        return 2;
    }

    if (mFileBuffer->isOpen())
    {
        mFileBuffer->close();
        if (!mFileBuffer->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            return 4;
        }
    }
    mDict[word]= log(mDict.size() * log(mDict.size()));
    mWordMaxLen = qMax(mWordMaxLen, word.length());

    QTextStream stream(mFileBuffer);
    stream << word << endl;
    stream.flush();
    return 0;
}

int WordNinga::RemoveWordToDigit(const QString &word)
{
    if(word.isEmpty())
    {
        return 3;
    }
    if (!mFileBuffer)
    {
        return 1;
    }

    if (!mDict.contains(word))
    {
        return 2;
    }

    if(mFileBuffer->isOpen())
    {
        mFileBuffer->close();
        if(!mFileBuffer->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            return 4;
        }
    }

    mDict.remove(word);
    QtConcurrent::run(this, &WordNinga::RemoveWordInFile, word);
    return 0;
}

inline bool WordNinga::isDigit(const QString& str)
{
    std::stringstream s;
    s << str.toStdString();
    double d = 0;
    char c;
    return (s >> d) ? !(s >> c) : false;
}

void WordNinga::RemoveWordInFile(const QString& word)
{
    QTextStream stream(mFileBuffer);
    QString text;
    for(const auto& i :mDict.keys())
    {
        if(!i.compare(word))
        {
            continue;
        }
        text.append(i % "\n");
    }
    stream<< text;
}
