#ifndef CCG_WORKWIDGET_H
#define CCG_WORKWIDGET_H
#include <QCheckBox>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

class WorkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorkWidget(QWidget *parent = nullptr);

    ~WorkWidget() override;

protected:
    void focusInEvent(QFocusEvent *event) override;

private:
    void SeparateKey();

    void UpperKey();

    void LowerKey();

    void AddUnderlineKey();

    inline void AddPrefixAndSuffix(QString &str);

    void SetResult(const QString &str);

    QLabel *inputLabel;
    QLineEdit *inputEdit;
    QLabel *outputLabel;
    QLineEdit *outputEdit;
    QPushButton *lowerCamelCase;
    QPushButton *upperCamelCase;
    QPushButton *addUnderline;
    QPushButton *allUpper;
    QPushButton *allLower;
    QPushButton *firstUpper;
    QCheckBox *underlineTolerate;
    QLabel *prefixLabel;
    QLineEdit *prefixEdit;
    QLabel *suffixLabel;
    QLineEdit *suffixEdit;
    QString nowText;
    QVector<QString> keyVec;
    QVector<QString> logVec;
    bool pasteWhenGetFocus;
    bool copyWhenWorkOver;
    friend class MainWindow;
};

#endif // CCG_WORKWIDGET_H
