#ifndef CCG_INFODIALOG_H
#define CCG_INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMutex>

class InfoDialog final
    : public QDialog
{
    Q_OBJECT
public:
    static void Show(QWidget *parent = nullptr, int sec = 2000, QString info = tr("Modify has saved"));

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    explicit InfoDialog(QWidget *parent = nullptr);

    ~InfoDialog() override;

    QLabel *iconLabel;
    QLabel *infoLabel;
};

#endif // CCG_INFODIALOG_H
