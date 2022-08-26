#ifndef CCG_INFODIALOG_H
#define CCG_INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMutex>

class InfoDialog :
    public QDialog
{
    Q_OBJECT
public:
    static void Show(QPoint positon, QSize size, int sec = 3000, QString info = tr("Modify has saved"));

private:
    InfoDialog();
    ~InfoDialog();
    QLabel* infoLabel;
    static InfoDialog* dlg;
    static QMutex mutex;

};

#endif // CCG_INFODIALOG_H




