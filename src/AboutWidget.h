
#ifndef CCG_ABOUTWIDGET_H
#define CCG_ABOUTWIDGET_H
#include <QWidget>
#include <QLabel>

class HelpLabel final
    : public QLabel
{
    Q_OBJECT
public:
    explicit HelpLabel(QString text = QString(), QWidget* parent = nullptr);
    ~HelpLabel() override;
    void SetLocalUrl(const QString &url);
    void SetNetWorkUrl(const QString &url);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QString localUrl;
    QString networkUrl;

};
class AboutWidget final
    :public QWidget
{
    Q_OBJECT
public:
    explicit AboutWidget(QWidget* parent = nullptr);
    ~AboutWidget() override;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    QLabel* iconLabel;
    QLabel* nameLabel;
    QLabel* versionLabel;
    QLabel* copyRightLabel;
    HelpLabel* helpLabel;
};



#endif // CCG_ABOUTWIDGET_H

