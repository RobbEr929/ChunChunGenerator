#ifndef SHORTCUTEDIT_H
#define SHORTCUTEDIT_H
#include <QLineEdit>

// todo : complete this class
class ShortcutEdit final
:    public QLineEdit
{
Q_OBJECT
public:
    explicit ShortcutEdit(QWidget* parent = nullptr);
    ~ShortcutEdit();
    
};


#endif // SHORTCUTEDIT_H




