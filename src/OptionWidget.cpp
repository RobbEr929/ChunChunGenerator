#include <QRegExpValidator>
#include <QStringBuilder>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>

#include "OptionWidget.h"

#include "MainWindow.h"

// todo : Bind Shortcut Keys
OptionWidget::OptionWidget(QWidget* parent)
	:QWidget(parent)
    , generalLabel(new QLabel(tr("general"),this))
	, pasteWhenGetFocusBox(new QCheckBox(tr("paste when get focus"), this))
	, copyWhenWorkOverBox(new QCheckBox(tr("copy to clipboard when work over"), this))
    , minimizeWhenCloseBox(new QCheckBox(tr("minimize to tray when close"),this))
    , windowTopHintBox(new QCheckBox(tr("window top hint"),this))
    , multilineInput(new QCheckBox(tr("multiline input"),this))
    , copyWhenClickBox(new QCheckBox(tr("copy to clipboard when click output view"),this))
    , individuationLabel(new QLabel(tr("individuation"),this))
    , themeLabel(new QLabel(tr("theme"),this))
    , themeBox(new QComboBox(this))
    , languageLabel(new QLabel(tr("language"),this))
    , languageBox(new QComboBox(this))
    , shortcutLabel(new QLabel(tr("shortcut keys")))
{
	pasteWhenGetFocusBox->setChecked(true);
	copyWhenWorkOverBox->setChecked(true);
	minimizeWhenCloseBox->setChecked(true);
	windowTopHintBox->setChecked(true);
	multilineInput->setChecked(false);
	copyWhenClickBox->setChecked(false);
	copyWhenClickBox->setEnabled(false);

	QStringList themeList{ tr("light"),tr("dark") };
	themeBox->addItems(themeList);

	QStringList languageList{ QStringLiteral("中文") % "(Chinese)",QStringLiteral("英语") % "(English)" };
	languageBox->addItems(languageList);
	languageBox->setCurrentIndex(MainWindow::nowLanguage == Language::Chinese ? 0 : 1);

	QVBoxLayout* vLayout1 = new QVBoxLayout;
	vLayout1->addStretch(1);
	vLayout1->addWidget(generalLabel,0,Qt::AlignCenter);
	vLayout1->addWidget(pasteWhenGetFocusBox);
	vLayout1->addWidget(copyWhenWorkOverBox);
	vLayout1->addWidget(minimizeWhenCloseBox);
	vLayout1->addWidget(windowTopHintBox);
	vLayout1->addWidget(multilineInput);
	vLayout1->addWidget(copyWhenClickBox);
	vLayout1->addStretch(1);

	QVBoxLayout* vLayout2 = new QVBoxLayout;
	vLayout2->addStretch(1);
	vLayout2->addWidget(individuationLabel,0,Qt::AlignCenter);
	QHBoxLayout* themeLayout = new QHBoxLayout;
	themeLayout->addWidget(themeLabel);
	themeLayout->addWidget(themeBox);
	vLayout2->addLayout(themeLayout);
	QHBoxLayout* languageLayout = new QHBoxLayout;
	languageLayout->addWidget(languageLabel);
	languageLayout->addWidget(languageBox);
	vLayout2->addLayout(languageLayout);
	vLayout2->addStretch(1);

	QVBoxLayout* vLayout3 = new QVBoxLayout;
	vLayout3->addStretch(1);
	vLayout3->addWidget(shortcutLabel,0, Qt::AlignCenter);
	vLayout3->addStretch(1);

	QFrame *frame1 = new QFrame(this);
	frame1->setFrameShape(QFrame::VLine);
	frame1->setLineWidth(3);
	frame1->setFrameShadow(QFrame::Plain);

	QFrame *frame2 = new QFrame(this);
	frame2->setFrameShape(QFrame::VLine);
	frame2->setLineWidth(3);
	frame2->setFrameShadow(QFrame::Plain);

	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->addStretch(1);
	hLayout->addLayout(vLayout1);
	hLayout->addWidget(frame1);
	hLayout->addLayout(vLayout2);
	hLayout->addWidget(frame2);
	hLayout->addLayout(vLayout3);
	hLayout->addStretch(1);
	setLayout(hLayout);
}

OptionWidget::~OptionWidget()
{
}
