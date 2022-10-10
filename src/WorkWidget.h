// --------------------------------------------------------------------------------------
// CopyRight © 2022-2022 ZhongChun All rights reserved
// Website : RobbEr.ltd
// Github : github.com/RobbEr929
// Gitee : gitee.com/robber929
// 
// Project : ChunChunGenerator
// File : WorkWidget.h
// 
// Create On : 2022-08-25 下午 10:06
// Last Update : 2022-09-04 下午 3:43
// ---------------------------------------------------------------------------------------

#ifndef CCG_WORKWIDGET_H
#define CCG_WORKWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMutex>
#include <QRadioButton>

#include "def.h"
#include "wordninga.h"

class WorkWidget final
    : public QWidget
{
    Q_OBJECT
public:
    explicit WorkWidget(QWidget *parent = nullptr);

    ~WorkWidget() override;

    void Execute();

protected:
    void focusInEvent(QFocusEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    void UpdateInputArea(bool update);

    void GetKey();

    void UpperKey();

    void LowerKey();

    void AllUpper();

    void AllLower();

    void FirstUpper();

    void AddUnderline();

    void DoNothing();

    QString UpperOne(const QString &str);

    void AddPrefixAndSuffix(QString &str);

    void SetResult(const QStringList &str);

    void SetLayoutVisible(QLayout *layout, bool visible);

    QMutex mutex;
    QHBoxLayout *hBoxLayout1;
    QHBoxLayout *hBoxLayout2;
    QHBoxLayout *hBoxLayout3;
    QHBoxLayout *hBoxLayout4;
    QVBoxLayout *vBoxLayout;
    QLabel *inputLabel;
    QLineEdit *inputEdit;
    QLabel *outputLabel;
    QLineEdit *outputEdit;
    QLabel *multiInputLabel;
    QTextEdit *inputEditArea;
    QLabel *multiOutputLabel;
    QListWidget *outputEditArea;
    QButtonGroup *group;
    QRadioButton *lowerCamelCase;
    QRadioButton *upperCamelCase;
    QRadioButton *addUnderline;
    QRadioButton *allUpper;
    QRadioButton *allLower;
    QRadioButton *firstUpper;
    QPushButton *generateButton;
    QLabel *prefixLabel;
    QLineEdit *prefixEdit;
    QLabel *suffixLabel;
    QLineEdit *suffixEdit;
    QVector<QVector<QString>> keyVec;
    QRegExp regExp;
    QRegExpValidator *validator;
    QString lastResult;
    bool isMultilineInput;
    bool pasteWhenGetFocus;
    bool copyWhenWorkOver;
    bool copyWhenClick;
    bool isFocus;
    friend class MainWindow;
    QMap<Action, QAbstractButton*> btnMap;
    WordNinga wordNinga;
};

#endif // CCG_WORKWIDGET_H
