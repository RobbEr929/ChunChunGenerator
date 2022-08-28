#ifndef CCG_OPTIONWIDGET_H
#define CCG_OPTIONWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>

class OptionWidget final
	: public QWidget
{
	Q_OBJECT
public:
	explicit OptionWidget(QWidget* parent = nullptr);
	~OptionWidget() override;

private:
	QLabel* generalLabel;
	QCheckBox* pasteWhenGetFocusBox;
	QCheckBox* copyWhenWorkOverBox;
	QCheckBox* minimizeWhenCloseBox;
	QCheckBox* windowTopHintBox;
	QCheckBox* multilineInput;
	QCheckBox* copyWhenClickBox;
	QLabel* individuationLabel;
	QLabel* themeLabel;
	QComboBox* themeBox;
	QLabel* languageLabel;
	QComboBox* languageBox;
	QLabel* shortcutLabel;
	friend class MainWindow;
};

#endif // CCG_OPTIONWIDGET_H
