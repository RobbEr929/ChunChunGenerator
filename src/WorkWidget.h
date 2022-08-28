#ifndef CCG_WORKWIDGET_H
#define CCG_WORKWIDGET_H
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>

class WorkWidget final
    : public QWidget
{
    Q_OBJECT
public:
    explicit WorkWidget(QWidget *parent = nullptr);

    ~WorkWidget() override;

protected:
    void focusInEvent(QFocusEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
private:
    void UpdateInputArea(bool update);

    void GetKey();

    inline QVector<QString> SeparateKey(const QString &text);

    void UpperKey();

    void LowerKey();

    void AllUpper();

    void AllLower();

    void FirstUpper();

    void AddUnderline();

    void DoNothing();

    inline void AddPrefixAndSuffix(QString &str);

    void SetResult(const QStringList &str);

    void SetLayoutVisible(QLayout *layout, bool visible);

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
    QCheckBox *underlineTolerate;
    QLabel *prefixLabel;
    QLineEdit *prefixEdit;
    QLabel *suffixLabel;
    QLineEdit *suffixEdit;
    QVector<QVector<QString>> keyVec;
    QRegExpValidator *validator;
    QString lastResult;
    bool isMultilineInput;
    bool pasteWhenGetFocus;
    bool copyWhenWorkOver;
    bool copyWhenClick;
    bool isFocus;
    friend class MainWindow;
};

#endif // CCG_WORKWIDGET_H
