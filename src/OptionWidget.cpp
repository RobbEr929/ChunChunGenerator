#include <QComboBox>

#include "OptionWidget.h"

#include "MainWindow.h"
#include "ShortcutEdit.h"

OptionWidget::OptionWidget(QWidget* parent)
	:QWidget(parent)
    , optionTabWidget(new QTabWidget(this))
	, pasteWhenGetFocusBox(new QCheckBox(tr("paste when get focus"), this))
	, copyWhenWorkOverBox(new QCheckBox(tr("copy to clipboard when work over"), this))
    , minimizeWhenCloseBox(new QCheckBox(tr("minimize to tray when close"),this))
    , windowTopHintBox(new QCheckBox(tr("window top hint"),this))
    , multilineInput(new QCheckBox(tr("multiline input"),this))
    , copyWhenClickBox(new QCheckBox(tr("copy to clipboard when click output view"),this))
    , defocusWidget(new TitleWidget(tr("defocus transparency(%)"),new QSlider(Qt::Horizontal, this), this))
    , themeWidget(new TitleWidget(tr("theme"),new QComboBox(this), this))
    , languageWidget(new TitleWidget(tr("language"), new QComboBox(this), this))
    , shortcutArea(new QScrollArea)
    , lccWdiget(new TitleWidget(tr("lowerCamelCase"),new ShortcutEdit(Action::LowerCamelCase),this))
    , uccWidget(new TitleWidget(tr("UpperCamelCase"),new ShortcutEdit(Action::UpperCamelCase),this))
    , alWidget(new TitleWidget(tr("all lower"),new ShortcutEdit(Action::AllLower),this))
    , auWdiget(new TitleWidget(tr("ALL UPPER"),new ShortcutEdit(Action::AllUpper),this))
    , fuWidget(new TitleWidget(tr("First upper"),new ShortcutEdit(Action::FirstUpper),this))
    , aulWidget(new TitleWidget(tr("add_underline"),new ShortcutEdit(Action::AddUnderline),this))
    , gWdiget(new TitleWidget(tr("generate"),new ShortcutEdit(Action::Generate),this))
    , dWidget(new TitleWidget(tr("display or not"),new ShortcutEdit(Action::DisplayOrNot),this))
    , qWidget(new TitleWidget(tr("quit"),new ShortcutEdit(Action::Quit),this))
    , useDictionaryBox(new QCheckBox(tr("enable dictionary segmentation"),this))
    , awtdLabel(new QLabel(tr("add word to dictionary"),this))
    , awtdEdit(new QLineEdit(this))
    , awtdButton(new QPushButton(tr("add"),this))
    , rwtdLabel(new QLabel(tr("remove word to dictionary"),this))
	, rwtdEdit(new QLineEdit(this))
	, rwtdButton(new QPushButton(tr("remove"), this))
    , configReader(new ConfigReader(this))
{
	setFixedSize(parent->size());

	optionTabWidget->setFixedSize(size());
	optionTabWidget->addTab(InitGeneralWidget(), tr("general"));
	optionTabWidget->addTab(InitIndividuationWidget(), tr("individuation"));
	optionTabWidget->addTab(InitShortcutWidget(), tr("shortcut keys"));
	optionTabWidget->addTab(InitDictionaryWidget(), tr("word segmentation"));
	optionTabWidget->setCurrentIndex(0);
}

OptionWidget::~OptionWidget()
{
}

void OptionWidget::ReadConfig() const
{
	if (!configReader->GetValue(lccWdiget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(lccWdiget->Object())->RegiserKey(configReader->GetValue(lccWdiget->Object()->objectName()));
	}
	if (!configReader->GetValue(uccWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(uccWidget->Object())->RegiserKey(configReader->GetValue(uccWidget->Object()->objectName()));
	}
	if (!configReader->GetValue(alWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(alWidget->Object())->RegiserKey(configReader->GetValue(alWidget->Object()->objectName()));
	}
	if (!configReader->GetValue(auWdiget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(auWdiget->Object())->RegiserKey(configReader->GetValue(auWdiget->Object()->objectName()));
	}
	if (!configReader->GetValue(fuWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(fuWidget->Object())->RegiserKey(configReader->GetValue(fuWidget->Object()->objectName()));
	}
	if (!configReader->GetValue(aulWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(aulWidget->Object())->RegiserKey(configReader->GetValue(aulWidget->Object()->objectName()));
	}
	if (!configReader->GetValue(gWdiget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(gWdiget->Object())->RegiserKey(configReader->GetValue(gWdiget->Object()->objectName()));
	}
	if (!configReader->GetValue(dWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(dWidget->Object())->RegiserKey(configReader->GetValue(dWidget->Object()->objectName()));
	}
	if (!configReader->GetValue(qWidget->Object()->objectName()).isEmpty())
	{
		qobject_cast<ShortcutEdit*>(qWidget->Object())->RegiserKey(configReader->GetValue(qWidget->Object()->objectName()));
	}
}

void OptionWidget::SaveConfig() const
{
	configReader->SetValue(lccWdiget->Object()->objectName(), qobject_cast<ShortcutEdit*>(lccWdiget->Object())->text());
	configReader->SetValue(uccWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(uccWidget->Object())->text());
	configReader->SetValue(alWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(alWidget->Object())->text());
	configReader->SetValue(auWdiget->Object()->objectName(), qobject_cast<ShortcutEdit*>(auWdiget->Object())->text());
	configReader->SetValue(fuWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(fuWidget->Object())->text());
	configReader->SetValue(aulWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(aulWidget->Object())->text());
	configReader->SetValue(gWdiget->Object()->objectName(), qobject_cast<ShortcutEdit*>(gWdiget->Object())->text());
	configReader->SetValue(dWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(dWidget->Object())->text());
	configReader->SetValue(qWidget->Object()->objectName(), qobject_cast<ShortcutEdit*>(qWidget->Object())->text());
}

QWidget * OptionWidget::InitGeneralWidget()
{
	pasteWhenGetFocusBox->setChecked(true);
	copyWhenWorkOverBox->setChecked(true);
	minimizeWhenCloseBox->setChecked(false);
	windowTopHintBox->setChecked(true);
	multilineInput->setChecked(false);
	copyWhenClickBox->setChecked(false);
	copyWhenClickBox->setEnabled(false);

	QWidget* generalWidget = new QWidget(this);
	generalWidget->setFixedSize(560, 240);

	QVBoxLayout* generalLayout = new QVBoxLayout;
	generalLayout->setContentsMargins(140, 20, 140, 20);
	generalLayout->addWidget(pasteWhenGetFocusBox);
	generalLayout->addWidget(copyWhenWorkOverBox);
	generalLayout->addWidget(minimizeWhenCloseBox);
	generalLayout->addWidget(windowTopHintBox);
	generalLayout->addWidget(multilineInput);
	generalLayout->addWidget(copyWhenClickBox);

	generalWidget->setLayout(generalLayout);

	return generalWidget;
}

QWidget * OptionWidget::InitIndividuationWidget()
{
	QWidget* individuationWidget = new QWidget(this);
	individuationWidget->setFixedSize(560, 240);

	qobject_cast<QSlider*>(defocusWidget->Object())->setTickPosition(QSlider::TicksAbove);
	qobject_cast<QSlider*>(defocusWidget->Object())->setMaximum(100);
	qobject_cast<QSlider*>(defocusWidget->Object())->setMinimum(10);
	qobject_cast<QSlider*>(defocusWidget->Object())->setSingleStep(10);
	qobject_cast<QSlider*>(defocusWidget->Object())->setValue(30);

	QStringList themeList{ tr("light"),tr("dark") };
	qobject_cast<QComboBox*>(themeWidget->Object())->addItems(themeList);

	QStringList languageList{ QStringLiteral("中文") % "(Chinese)",QStringLiteral("英语") % "(English)" };
	qobject_cast<QComboBox*>(languageWidget->Object())->addItems(languageList);
	qobject_cast<QComboBox*>(languageWidget->Object())->setCurrentIndex(MainWindow::nowLanguage == Language::Chinese ? 0 : 1);

	QVBoxLayout* individuationLayout = new QVBoxLayout;
	individuationLayout->setContentsMargins(140, 20, 140, 20);
	individuationLayout->addStretch(1);
	individuationLayout->addWidget(defocusWidget);
	individuationLayout->addWidget(themeWidget);
	individuationLayout->addWidget(languageWidget);
	individuationLayout->addStretch(1);

	individuationWidget->setLayout(individuationLayout);

	return individuationWidget;
}

QWidget * OptionWidget::InitShortcutWidget()
{
	QFrame* frame1 = new QFrame(this);
	frame1->setFrameShape(QFrame::HLine);
	frame1->setLineWidth(3);
	frame1->setFrameShadow(QFrame::Plain);
	frame1->setFixedWidth(100);
	localWidget = new TitleWidget(tr("local shortcut keys, only works in software"), frame1, this);

	QFrame* frame2 = new QFrame(this);
	frame2->setFrameShape(QFrame::HLine);
	frame2->setLineWidth(3);
	frame2->setFrameShadow(QFrame::Plain);
	frame2->setFixedWidth(100);
	globalWidget = new TitleWidget(tr("global shortcut keys, works any where"), frame2,this);

	QWidget* shortcutWidget = new QWidget(this);
	shortcutWidget->setFixedSize(560, 240);
	QVBoxLayout* shortcutLayout = new QVBoxLayout(shortcutWidget);

	QWidget* shortcutContentWidget = new QWidget;
	QVBoxLayout* shortcutContentLayout = new QVBoxLayout(shortcutContentWidget);
	shortcutContentLayout->addWidget(localWidget);
	shortcutContentLayout->addWidget(lccWdiget);
	shortcutContentLayout->addWidget(uccWidget);
	shortcutContentLayout->addWidget(alWidget);
	shortcutContentLayout->addWidget(auWdiget);
	shortcutContentLayout->addWidget(fuWidget); 
	shortcutContentLayout->addWidget(aulWidget);
	shortcutContentLayout->addWidget(globalWidget);
	shortcutContentLayout->addWidget(gWdiget);
	shortcutContentLayout->addWidget(dWidget);
	shortcutContentLayout->addWidget(qWidget);
	shortcutContentLayout->addStretch(1);

	shortcutArea->setParent(shortcutWidget);
	shortcutArea->setWidget(shortcutContentWidget);
	shortcutArea->setWidgetResizable(true);
	shortcutArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	shortcutLayout->addWidget(shortcutArea);

	return shortcutWidget;

}

QWidget * OptionWidget::InitDictionaryWidget()
{
	useDictionaryBox->setToolTip(tr("use the dictionary for word segmentation when on. use simple word segmentation when off."));
	useDictionaryBox->setChecked(true);

	QHBoxLayout* awtdLayout = new QHBoxLayout;
	awtdLayout->addStretch(1);
	awtdLayout->addWidget(awtdLabel);
	awtdLayout->addWidget(awtdEdit);
	awtdLayout->addWidget(awtdButton);
	awtdLayout->addStretch(1);

	QHBoxLayout* rwtdLayout = new QHBoxLayout;
	rwtdLayout->addStretch(1);
	rwtdLayout->addWidget(rwtdLabel);
	rwtdLayout->addWidget(rwtdEdit);
	rwtdLayout->addWidget(rwtdButton);
	rwtdLayout->addStretch(1);

    QWidget* dictionaryWidget = new QWidget(this);
	dictionaryWidget->setFixedSize(560, 240);

	QVBoxLayout* dictionaryLayout = new QVBoxLayout;
	dictionaryLayout->setContentsMargins(140, 20, 140, 20);
	dictionaryLayout->addStretch(1);
	dictionaryLayout->addWidget(useDictionaryBox);
	dictionaryLayout->addLayout(awtdLayout);
	dictionaryLayout->addLayout(rwtdLayout);
	dictionaryLayout->addStretch(1);

	dictionaryWidget->setLayout(dictionaryLayout);

	return dictionaryWidget;
}
