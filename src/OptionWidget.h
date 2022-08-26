#ifndef CCG_OPTIONWIDGET_H
#define CCG_OPTIONWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>

class OptionWidget
	: public QWidget
{
	Q_OBJECT
public:
	explicit OptionWidget(QWidget* parent = nullptr);
	~OptionWidget() override;

private:
	QCheckBox* pasteWhenGetFocusBox;
	QCheckBox* copyWhenWorkOverBox;
	QCheckBox* minimizeWhenCloseBox;
	QCheckBox* windowTopHintBox;
	QComboBox* themeBox;
	QComboBox* languageBox;
	friend class MainWindow;
};

#endif // CCG_OPTIONWIDGET_H
