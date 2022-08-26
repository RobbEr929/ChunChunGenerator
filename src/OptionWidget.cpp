#include <QRegExpValidator>
#include <QStringBuilder>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>

#include "OptionWidget.h"

#include "MainWindow.h"

// todo Bind Shortcut Keys
OptionWidget::OptionWidget(QWidget* parent)
	:QWidget(parent)
	, pasteWhenGetFocusBox(new QCheckBox(tr("paste when get focus"), this))
	, copyWhenWorkOverBox(new QCheckBox(tr("copy to clipboard when work over"), this))
    , minimizeWhenCloseBox(new QCheckBox(tr("minimize to tray when close"),this))
    , windowTopHintBox(new QCheckBox(tr("Window top hint"),this))
    , themeBox(new QComboBox(this))
    , languageBox(new QComboBox(this))
{
	pasteWhenGetFocusBox->setChecked(true);
	copyWhenWorkOverBox->setChecked(true);
	minimizeWhenCloseBox->setChecked(true);
	windowTopHintBox->setChecked(true);

	QStringList themeList{ tr("light"),tr("dark") };
	themeBox->addItems(themeList);

	QStringList languageList{ QStringLiteral("中文") % "(Chinese)",QStringLiteral("英语") % "(English)" };
	languageBox->addItems(languageList);
	languageBox->setCurrentIndex(MainWindow::nowLanguage == Language::Chinese ? 0 : 1);

	QVBoxLayout* vLayout1 = new QVBoxLayout;
	vLayout1->addStretch(1);
	vLayout1->addWidget(pasteWhenGetFocusBox);
	vLayout1->addWidget(copyWhenWorkOverBox);
	vLayout1->addWidget(minimizeWhenCloseBox);
	vLayout1->addWidget(windowTopHintBox);
	vLayout1->addStretch(1);

	QVBoxLayout* vLayout2 = new QVBoxLayout;
	vLayout2->addStretch(1);
	vLayout2->addWidget(themeBox);
	vLayout2->addWidget(languageBox);
	vLayout2->addStretch(1);

	QFrame *frame = new QFrame(this);
	frame->setFrameShape(QFrame::VLine);
	frame->setLineWidth(3);
	frame->setFrameShadow(QFrame::Plain);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->addStretch(1);
	hLayout->addLayout(vLayout1);
	hLayout->addWidget(frame);
	hLayout->addLayout(vLayout2);
	hLayout->addStretch(1);
	setLayout(hLayout);
}

OptionWidget::~OptionWidget()
{
}
