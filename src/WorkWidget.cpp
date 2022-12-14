// --------------------------------------------------------------------------------------
// CopyRight © 2022-2022 ZhongChun All rights reserved
// Website : RobbEr.ltd
// Github : github.com/RobbEr929
// Gitee : gitee.com/robber929
// 
// Project : ChunChunGenerator
// File : WorkWidget.cpp
// 
// Create On : 2022-08-25 下午 10:06
// Last Update : 2022-09-04 下午 3:43
// ---------------------------------------------------------------------------------------

#include <QLineEdit>
#include <QKeyEvent>
#include <QTextBlock>
#include <QClipboard>
#include <QButtonGroup>
#include <QApplication>
#include <QStringBuilder>
#include <QtConcurrent/QtConcurrent>
#include "WorkWidget.h"

#include <QThread>

WorkWidget::WorkWidget(QWidget *parent)
    : QWidget(parent)
    , inputLabel(new QLabel(tr("input"), this))
    , inputEdit(new QLineEdit(this))
    , outputLabel(new QLabel(tr("output"), this))
    , outputEdit(new QLineEdit(this))
    , multiInputLabel(new QLabel(tr("multiline\ninput")))
    , inputEditArea(new QTextEdit(this))
    , multiOutputLabel(new QLabel(tr("multiline\noutput")))
    , outputEditArea(new QListWidget(this))
    , group(new QButtonGroup(this))
    , lowerCamelCase(new QRadioButton(tr("lowerCamelCase"), this))
    , upperCamelCase(new QRadioButton(tr("UpperCamelCase"), this))
    , addUnderline(new QRadioButton(tr("add_underline"), this))
    , allUpper(new QRadioButton(tr("ALL UPPER"), this))
    , allLower(new QRadioButton(tr("all lower"), this))
    , firstUpper(new QRadioButton(tr("First upper"), this))
    , generateButton(new QPushButton(tr("generate"), this))
    , prefixLabel(new QLabel(tr("add prefix"), this))
    , prefixEdit(new QLineEdit(this))
    , suffixLabel(new QLabel(tr("add suffix"), this))
    , suffixEdit(new QLineEdit(this))
    , isMultilineInput(false)
    , pasteWhenGetFocus(true)
    , copyWhenWorkOver(true)
    , copyWhenClick(false)
    , regExp("[0-9a-zA-Z_\\s]*")
{
    setFocusPolicy(Qt::StrongFocus);

    btnMap[Action::LowerCamelCase] = lowerCamelCase;
    btnMap[Action::UpperCamelCase] = upperCamelCase;
    btnMap[Action::AllLower] = allLower;
    btnMap[Action::AllUpper] = allUpper;
    btnMap[Action::FirstUpper] = firstUpper;
    btnMap[Action::AddUnderline] = addUnderline;

    validator = new QRegExpValidator(regExp, this);
    inputEdit->setValidator(validator);
    inputEdit->setFixedSize(140, 30);
    outputEdit->setFixedSize(140, 30);
    outputEdit->setReadOnly(true);

    inputEditArea->setFixedSize(140, 90);
    outputEditArea->setFixedSize(140, 90);

    prefixEdit->setFixedSize(100, 30);
    suffixEdit->setFixedSize(100, 30);

    hBoxLayout1 = new QHBoxLayout;
    hBoxLayout1->addStretch(1);
    hBoxLayout1->addWidget(inputLabel);
    hBoxLayout1->addWidget(inputEdit);
    hBoxLayout1->addStretch(1);

    hBoxLayout2 = new QHBoxLayout;
    hBoxLayout2->addStretch(1);
    hBoxLayout2->addWidget(outputLabel);
    hBoxLayout2->addWidget(outputEdit);
    hBoxLayout2->addStretch(1);

    hBoxLayout3 = new QHBoxLayout;
    hBoxLayout3->addStretch(1);
    hBoxLayout3->addWidget(multiInputLabel);
    hBoxLayout3->addWidget(inputEditArea);
    hBoxLayout3->addWidget(multiOutputLabel);
    hBoxLayout3->addWidget(outputEditArea);
    hBoxLayout3->addStretch(1);
    SetLayoutVisible(hBoxLayout3, false);

    group->addButton(lowerCamelCase, 0);
    group->addButton(upperCamelCase, 1);
    group->addButton(allLower, 2);
    group->addButton(allUpper, 3);
    group->addButton(firstUpper, 4);
    group->addButton(addUnderline, 5);
    group->setExclusive(true);

    generateButton->setFixedHeight(80);
    auto buttonLayout = new QVBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(lowerCamelCase);
    buttonLayout->addWidget(upperCamelCase);
    buttonLayout->addWidget(allLower);
    buttonLayout->addWidget(allUpper);
    buttonLayout->addWidget(firstUpper);
    buttonLayout->addWidget(addUnderline);
    buttonLayout->addStretch(1);

    auto prefixLayout = new QHBoxLayout;
    prefixLayout->addStretch(1);
    prefixLayout->addWidget(prefixLabel);
    prefixLayout->addWidget(prefixEdit);
    prefixLayout->addStretch(1);

    auto suffix = new QHBoxLayout;
    suffix->addStretch(1);
    suffix->addWidget(suffixLabel);
    suffix->addWidget(suffixEdit);
    suffix->addStretch(1);

    auto fixLayout = new QVBoxLayout;
    fixLayout->addStretch(1);
    fixLayout->addLayout(prefixLayout);
    fixLayout->addLayout(suffix);
    fixLayout->addWidget(generateButton);
    fixLayout->addStretch(1);

    hBoxLayout4 = new QHBoxLayout;
    hBoxLayout4->addStretch(1);
    hBoxLayout4->addLayout(buttonLayout);
    hBoxLayout4->addLayout(fixLayout);
    hBoxLayout4->addStretch(1);

    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addStretch(1);
    vBoxLayout->addLayout(hBoxLayout1);
    vBoxLayout->addLayout(hBoxLayout2);
    vBoxLayout->addLayout(hBoxLayout4);
    vBoxLayout->addStretch(1);
    setLayout(vBoxLayout);

    connect(generateButton, &QPushButton::clicked, this, &WorkWidget::Execute);

    connect(outputEditArea,
            &QListWidget::itemClicked,
            [this](QListWidgetItem *item)
            {
                if (copyWhenClick)
                {
                    QApplication::clipboard()->setText(item->text());
                }
            });
    QtConcurrent::run(&wordNinga, &WordNinga::Init);
}

WorkWidget::~WorkWidget()
{
}

void WorkWidget::Execute()
{
    QMutexLocker locker(&mutex);
    GetKey();
    switch (group->checkedId())
    {
    case 0:
        {
            LowerKey();
            return;
        }
    case 1:
        {
            UpperKey();
            return;
        }
    case 2:
        {
            AllLower();
            return;
        }
    case 3:
        {
            AllUpper();
            return;
        }
    case 4:
        {
            FirstUpper();
            return;
        }
    case 5:
        {
            AddUnderline();
            return;
        }
    default:
        {
            DoNothing();
        }
    }
}

void WorkWidget::focusInEvent(QFocusEvent *event)
{
    if (pasteWhenGetFocus)
    {
        if (!isMultilineInput)
        {
            QString text = QApplication::clipboard()->text();
            if (lastResult.compare(text))
            {
                if(regExp.exactMatch(text))
                {
                    inputEdit->setText(text);
                    return;
                }
            }
        }
    }
    QWidget::focusInEvent(event);
}

void WorkWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= 0x30 && event->key() <= 0x39
        || event->key() >= 0x41 && event->key() <= 0x5a
        || event->key() == 0x5f)
    {
        if (!isMultilineInput)
        {
            inputEdit->setFocus();
        }
        else
        {
            inputEditArea->setFocus();
        }
    }
    QWidget::keyPressEvent(event);
}

void WorkWidget::UpdateInputArea(bool update)
{
    isMultilineInput = update;
    if (update)
    {
        SetLayoutVisible(hBoxLayout1, false);
        SetLayoutVisible(hBoxLayout2, false);
        SetLayoutVisible(hBoxLayout3, true);
        auto temp1 = vBoxLayout->itemAt(0);
        auto temp2 = vBoxLayout->itemAt(1);
        vBoxLayout->removeItem(temp1);
        vBoxLayout->removeItem(temp2);
        vBoxLayout->insertLayout(0, hBoxLayout3);
        return;
    }

    SetLayoutVisible(hBoxLayout1, true);
    SetLayoutVisible(hBoxLayout2, true);
    SetLayoutVisible(hBoxLayout3, false);
    auto temp1 = vBoxLayout->itemAt(0);
    auto temp2 = vBoxLayout->itemAt(1);
    vBoxLayout->removeItem(temp1);
    vBoxLayout->removeItem(temp2);
    vBoxLayout->insertLayout(0, hBoxLayout1);
    vBoxLayout->insertLayout(1, hBoxLayout2);
}

void WorkWidget::GetKey()
{
    if (isMultilineInput)
    {
        if (inputEditArea->document()->isEmpty())
        {
            return;
        }
        keyVec.clear();
        for (auto i = 0; i < inputEditArea->document()->lineCount(); ++i)
        {
            QString text = inputEditArea->document()->findBlockByLineNumber(i).text();
            keyVec.push_back(wordNinga.split(text));
        }
        return;
    }
    if (inputEdit->text().isEmpty())
    {
        return;
    }
    keyVec.clear();
    QString text = inputEdit->text();
    keyVec.push_back(wordNinga.split(text));
}

void WorkWidget::UpperKey()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            for (auto& j : keyVec[i])
            {
                j = UpperOne(j);
            }
            QString text;
            for (const auto &j : keyVec[i])
            {
                text.append(j);
            }
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::LowerKey()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            keyVec[i][0] = keyVec[i][0].toLower();
            for (auto j = 1; j < keyVec[i].size(); ++j)
            {
                keyVec[i][j] = UpperOne(keyVec[i][j]);
            }
            QString text;
            for (const auto &j : keyVec[i])
            {
                text.append(j);
            }
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::AllUpper()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            QString text;
            for (auto &j : keyVec[i])
            {
                j = j.toUpper();
                text.append(j);
            }
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::AllLower()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            QString text;
            for (auto &j : keyVec[i])
            {
                j = j.toLower();
                text.append(j);
            }
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::FirstUpper()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            QString text;
            for (auto &j : keyVec[i])
            {
                j = j.toLower();
                text.append(j);
            }
            text[0] = text[0].toUpper();
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::AddUnderline()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            QString text;
            for (auto &j : keyVec[i])
            {
                text.append(j % '_');
            }
            text = text.mid(0, text.size() - 1);
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

void WorkWidget::DoNothing()
{
    QString text;
    if (!keyVec.isEmpty())
    {
        QStringList list;
        for (auto i = 0; i < keyVec.size(); ++i)
        {
            QString text;
            for (auto &j : keyVec[i])
            {
                text.append(j);
            }
            AddPrefixAndSuffix(text);
            list.append(text);
        }
        SetResult(list);
    }
}

QString WorkWidget::UpperOne(const QString &str)
{
    QString newStr = str.toLower();
    qint8 pos = 0;
    while (!( newStr[pos] >= 'a' && newStr[pos] <= 'z'
        || newStr[pos] >= 'A' && newStr[pos] <= 'Z' ))
    {
        if (pos >= newStr.size())
        {
            return newStr;
        }
        ++pos;
    }
    newStr[pos] = newStr[pos].toUpper();
    return newStr;
}

void WorkWidget::AddPrefixAndSuffix(QString &str)
{
    if (str.isEmpty())
    {
        return;
    }
    if (!prefixEdit->text().isEmpty())
    {
        str.prepend(prefixEdit->text());
    }
    if (!suffixEdit->text().isEmpty())
    {
        str.append(suffixEdit->text());
    }
}

void WorkWidget::SetResult(const QStringList &str)
{
    if (str.isEmpty())
    {
        return;
    }
    if (isMultilineInput)
    {
        if (copyWhenWorkOver)
        {
            QString text;
            for (const auto &i : str)
            {
                text.append(i % "\r\n");
            }
            lastResult = text;
            QApplication::clipboard()->setText(text);
        }
        QString text;
        for (const auto &i : str)
        {
            text.append(i);
        }
        lastResult = text;
        outputEditArea->clear();
        outputEditArea->addItems(str);
        return;
    }
    if (copyWhenWorkOver)
    {
        QApplication::clipboard()->setText(str.at(0));
    }
    outputEdit->setText(str.at(0));
}

void WorkWidget::SetLayoutVisible(QLayout *layout, bool visible)
{
    for (auto i = 0; i < layout->count(); ++i)
    {
        QWidget *w = layout->itemAt(i)->widget();
        if (w)
        {
            w->setVisible(visible);
        }
    }
}
