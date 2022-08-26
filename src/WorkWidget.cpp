#include <QKeyEvent>
#include <QRegExpValidator>
#include <QtWidgets/QHBoxLayout>
#include <QStringBuilder>

#include "WorkWidget.h"

#include <QApplication>
#include <QClipboard>

WorkWidget::WorkWidget(QWidget* parent)
    : QWidget(parent)
    , inputLabel(new QLabel(tr("input"), this))
    , inputEdit(new QLineEdit(this))
    , outputLabel(new QLabel(tr("output"), this))
    , outputEdit(new QLineEdit(this))
    , lowerCamelCase(new QPushButton(tr("to lowerCamelCase"), this))
    , upperCamelCase(new QPushButton(tr("to UpperCamelCase"), this))
    , addUnderline(new QPushButton(tr("add_underline"), this))
    , allUpper(new QPushButton(tr("ALL UPPER"),this))
    , allLower(new QPushButton(tr("all lower"),this))
    , firstUpper(new QPushButton(tr("First upper"),this))
    , underlineTolerate(new QCheckBox(tr("UnderlineTolerate"),this))
    , prefixLabel(new QLabel(tr("add prefix"), this))
    , prefixEdit(new QLineEdit(this))
    , suffixLabel(new QLabel(tr("add suffix"), this))
    , suffixEdit(new QLineEdit(this))
    , pasteWhenGetFocus(true)
    , copyWhenWorkOver(true)
{
    setFocusPolicy(Qt::StrongFocus);

    // todo History Record
    QRegExp regExp("[a-z A-Z 0-9 _]*");
    auto validator = new QRegExpValidator(regExp, this);
    inputEdit->setValidator(validator);
    inputEdit->resize(200, 100);

    outputEdit->setReadOnly(true);

    auto hBoxLayout1 = new QHBoxLayout;
    hBoxLayout1->addStretch(1);
    hBoxLayout1->addWidget(inputLabel);
    hBoxLayout1->addWidget(inputEdit);
    hBoxLayout1->addStretch(1);

    auto hBoxLayout2 = new QHBoxLayout;
    hBoxLayout2->addStretch(1);
    hBoxLayout2->addWidget(outputLabel);
    hBoxLayout2->addWidget(outputEdit);
    hBoxLayout2->addStretch(1);

    auto hBoxLayout3 = new QHBoxLayout;
    hBoxLayout3->addStretch(1);
    hBoxLayout3->addWidget(lowerCamelCase);
    hBoxLayout3->addWidget(upperCamelCase);
    hBoxLayout3->addWidget(underlineTolerate);

    hBoxLayout3->addStretch(1);

    auto hBoxLayout4 = new QHBoxLayout;
    hBoxLayout4->addStretch(1);
    hBoxLayout4->addWidget(allLower);
    hBoxLayout4->addWidget(allUpper);
    hBoxLayout4->addWidget(firstUpper);
    hBoxLayout4->addWidget(addUnderline);
    hBoxLayout4->addStretch(1);

    
    auto hBoxLayout5 = new QHBoxLayout;
    hBoxLayout5->addStretch(1);
    hBoxLayout5->addWidget(prefixLabel);
    hBoxLayout5->addWidget(prefixEdit);
    hBoxLayout5->addWidget(suffixLabel);
    hBoxLayout5->addWidget(suffixEdit);
    hBoxLayout5->addStretch(1);

    auto vBoxLayout = new QVBoxLayout;
    vBoxLayout->addStretch(1);
    vBoxLayout->addLayout(hBoxLayout1);
    vBoxLayout->addLayout(hBoxLayout2);
    vBoxLayout->addLayout(hBoxLayout3);
    vBoxLayout->addLayout(hBoxLayout4);
    vBoxLayout->addLayout(hBoxLayout5);
    vBoxLayout->addStretch(1);
    setLayout(vBoxLayout);

    connect(inputEdit, &QLineEdit::textChanged, this, [this](const QString &str)
    {
        nowText = str;
    });
    connect(lowerCamelCase, &QPushButton::clicked, this, [this]()
    {
            SeparateKey();
            LowerKey();
    });
    connect(upperCamelCase, &QPushButton::clicked, this, [this]()
    {
            SeparateKey();
            UpperKey();
    });
    connect(allLower, &QPushButton::clicked, this, [this]()
    {
            // todo All Lower
    });
    connect(allLower, &QPushButton::clicked, this, [this]()
    {
            // todo All Upper
    });
    connect(firstUpper, &QPushButton::clicked, this, [this]()
    {
            // todo First Upper
    });
    connect(addUnderline, &QPushButton::clicked, this, [this]()
    {
            SeparateKey();
            AddUnderlineKey();
    });
}

WorkWidget::~WorkWidget()
{
}

void WorkWidget::focusInEvent(QFocusEvent *event)
{
    if (pasteWhenGetFocus)
    {
        inputEdit->setText(QApplication::clipboard()->text());
    }
    QWidget::focusInEvent(event);
}

void WorkWidget::SeparateKey()
{
    // todo Underline Tolerate

    if(nowText.isEmpty())
    {
        return;
    }
    keyVec.clear();
    QString text = nowText;
    int start = 0;
    int step = 0;

    QRegExp regExp("[A-Z _ \\s]");
    while(step != -1)
    {
        step = regExp.indexIn(text, start + 1);
        QString key = text.mid(start, step == -1 ? -1 : step - start).simplified().remove('_');
        start = step;
        if(key.isEmpty())
        {
            continue;
        }
        keyVec.push_back(key);
    }
}

void WorkWidget::UpperKey()
{
    QString text;
    if(!keyVec.isEmpty() &&!keyVec[0].isEmpty())
    {
        keyVec[0][0] = keyVec[0][0].toUpper();
    }
    for(const auto& i : keyVec)
    {
        text.append(i);
    }
    AddPrefixAndSuffix(text);
    SetResult(text);
}

void WorkWidget::LowerKey()
{
    QString text;
    if (!keyVec.isEmpty() && !keyVec[0].isEmpty())
    {
        keyVec[0][0] = keyVec[0][0].toLower();
    }
    for (const auto& i : keyVec)
    {
        text.append(i);
    }
    AddPrefixAndSuffix(text);
    SetResult(text);
}

void WorkWidget::AddUnderlineKey()
{
    QString text;
    for (const auto& i : keyVec)
    {
        text.append(i % '_');
    }
    text = text.mid(0,text.size() - 1);
    AddPrefixAndSuffix(text);
    SetResult(text);
}

void WorkWidget::AddPrefixAndSuffix(QString &str)
{
    if(str.isEmpty())
    {
        return;
    }
    if(!prefixEdit->text().isEmpty())
    {
        str.prepend(prefixEdit->text());
    }
    if(!suffixEdit->text().isEmpty())
    {
        str.append(suffixEdit->text());
    }
}

void WorkWidget::SetResult(const QString& str)
{
    if(str.isEmpty())
    {
        return;
    }
    if(copyWhenWorkOver)
    {
        QApplication::clipboard()->setText(str);
    }
    outputEdit->setText(str);
}
