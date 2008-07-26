#include <cstdlib>
#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QSpinBox>
#include "../include/gui.h"

/* * * * * *
 * public  *
 * * * * * */

AscurpiQ::AscurpiQ(QWidget *parent) : QMainWindow(parent)
{
	backgroundColorButton   = new QPushButton(tr("&Choose"));
	backgroundColorLabel    = new QLabel(tr("&Background color:"));
	backgroundColorLineEdit = new QLineEdit("0x0");
	bmpInFileButton         = new QPushButton(tr("Browse"));
	bmpInFileLabel          = new QLabel(tr("Bitmap &file:"));
	bmpInFileLineEdit       = new QLineEdit();
	charPerPixelLabel       = new QLabel(tr("Characters per &pixel:"));
	charPerPixelSpinBox     = new QSpinBox();
	fontSizeLabel           = new QLabel(tr("&Font size:"));
	fontSizeSpinBox         = new QSpinBox();
	generateButton          = new QPushButton(tr("&Generate"));
	htmlOutFileButton       = new QPushButton(tr("Browse"));
	htmlOutFileLabel        = new QLabel(tr("&Output file:"));
	htmlOutFileLineEdit     = new QLineEdit();
	txtInFileButton         = new QPushButton(tr("Browse"));
	txtInFileLabel          = new QLabel(tr("&Text file:"));
	txtInFileLineEdit       = new QLineEdit();

	// Matching hexa numbers between 0 and FFFFFFFF
	QRegExp hexaRegExp("^0x(\\d|[a-fA-F]){1,8}$");

	// Setting labels' buddies
	backgroundColorLabel->setBuddy(backgroundColorLineEdit);
	bmpInFileLabel->setBuddy(bmpInFileLineEdit);
	charPerPixelLabel->setBuddy(charPerPixelSpinBox);
	fontSizeLabel->setBuddy(fontSizeSpinBox);
	htmlOutFileLabel->setBuddy(htmlOutFileLineEdit);
	txtInFileLabel->setBuddy(txtInFileLineEdit);

	// Hexa validator
	backgroundColorLineEdit->setValidator(new QRegExpValidator(hexaRegExp, backgroundColorLineEdit));

	// Setting spin boxes
	charPerPixelSpinBox->setValue(1);
	fontSizeSpinBox->setSuffix(" px");
	fontSizeSpinBox->setValue(8);

	setWindowTitle("AscurpiQ - Ascurpic Qt GUI");
	createConnections();
	createLayout();
}

/* * * * * * * * *
 * public  slots *
 * * * * * * * * */

/* * * * * *
 * private *
 * * * * * */

void AscurpiQ::createConnections()
{
	// Browse file buttons //
	connect(bmpInFileButton, SIGNAL(clicked()),
	        this, SLOT(selectBmpFile()));
	connect(htmlOutFileButton, SIGNAL(clicked()),
	        this, SLOT(selectOutputFile()));
	connect(txtInFileButton, SIGNAL(clicked()),
	        this, SLOT(selectTextFile()));

	connect(generateButton, SIGNAL(clicked()),
	        this, SLOT(generate()));
}

void AscurpiQ::createLayout()
{
	QWidget *containerWidget = new QWidget();

	// Files group box //
	QGroupBox   *filesBox        = new QGroupBox(tr("Files"));
	QGridLayout *filesGridLayout = new QGridLayout();

	filesGridLayout->addWidget(bmpInFileLabel, 0, 0);
	filesGridLayout->addWidget(bmpInFileLineEdit, 0, 1);
	filesGridLayout->addWidget(bmpInFileButton, 0, 2);
	filesGridLayout->addWidget(txtInFileLabel, 1, 0);
	filesGridLayout->addWidget(txtInFileLineEdit, 1, 1);
	filesGridLayout->addWidget(txtInFileButton, 1, 2);
	filesGridLayout->addWidget(htmlOutFileLabel, 2, 0);
	filesGridLayout->addWidget(htmlOutFileLineEdit, 2, 1);
	filesGridLayout->addWidget(htmlOutFileButton, 2, 2);

	filesBox->setLayout(filesGridLayout);

	// Options group box //
	QGroupBox   *optionsBox        = new QGroupBox(tr("Options"));
	QGridLayout *optionsGridLayout = new QGridLayout();

	optionsGridLayout->addWidget(backgroundColorLabel, 0, 0);
	optionsGridLayout->addWidget(backgroundColorLineEdit, 0, 1);
	//optionsGridLayout->addWidget(backgroundColorButton, 0, 2);
	optionsGridLayout->addWidget(fontSizeLabel, 1, 0);
	optionsGridLayout->addWidget(fontSizeSpinBox, 1, 1);
	optionsGridLayout->addWidget(charPerPixelLabel, 2, 0);
	optionsGridLayout->addWidget(charPerPixelSpinBox, 2, 1);

	optionsBox->setLayout(optionsGridLayout);

	// Container layout //
	QGridLayout *containerLayout = new QGridLayout();

	containerLayout->addWidget(filesBox, 0, 0);
	containerLayout->addWidget(optionsBox, 0, 1);
	containerLayout->addWidget(generateButton, 1, 0, 1, 2);

	containerWidget->setLayout(containerLayout);
	setCentralWidget(containerWidget);
}

const char* AscurpiQ::qStrToChar(const QString &qstr) const
{
	return qstr.toLocal8Bit().data();
}

/* * * * * * * * * *
 * private  slots  *
 * * * * * * * * * */

void AscurpiQ::generate() const
{
	short err = 0;

	if(bmpInFileLineEdit->text().length() > 0
	   && txtInFileLineEdit->text().length() > 0
	   && htmlOutFileLineEdit->text().length() > 0)
	{
		param_t params;
		char   *meSertTropARienCePointeur;

		err += open_bmp(&(params.input_bitmap),
		                qStrToChar(bmpInFileLineEdit->text()));
		err += open_file(&(params.input_text),
		                 qStrToChar(txtInFileLineEdit->text()),
				  "r");
		err += open_file(&(params.output_file),
		                 qStrToChar(htmlOutFileLineEdit->text()),
		                 "w");

		params.bgcolor = strtol(qStrToChar(backgroundColorLineEdit->text()),
		                        &meSertTropARienCePointeur,
		                        16);

		params.nbcharpx = charPerPixelSpinBox->value();
		params.fontsize = fontSizeSpinBox->value();

		// if no error happened, we can do that :p
		if(err == 0)
		{
			write_page(&params);
			free_bitmap(params.input_bitmap);
		}
	}
}

void AscurpiQ::selectBmpFile()
{
	QString filename;

	filename = QFileDialog::getOpenFileName(this, tr("Select bitmap file"),
	                                        bmpInFileLineEdit->text(),
	                                        tr("Bitmap pictures (*.bmp);;All (*.*)")
	                                       );

	bmpInFileLineEdit->setText(filename);
}

void AscurpiQ::selectOutputFile()
{
	QString     filename;
	QFileDialog dialog(this, tr("Select output file"), htmlOutFileLineEdit->text(),
	                   tr("HTML files (*.html)"));

	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.selectFile(htmlOutFileLineEdit->text());

	if (dialog.exec())
	{
		htmlOutFileLineEdit->setText(dialog.selectedFiles().at(0));
	}
}

void AscurpiQ::selectTextFile()
{
	QString filename;

	filename = QFileDialog::getOpenFileName(this, tr("Select text file"),
	                                        txtInFileLineEdit->text(),
	                                        tr("Text file (*.txt);;All (*.*)")
	                                       );

	txtInFileLineEdit->setText(filename);
}
