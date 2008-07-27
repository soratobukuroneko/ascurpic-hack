#include <cstdlib>
#include <QColorDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include "../include/gui.h"

/* * * * * *
 * public  *
 * * * * * */

AscurpiQ::AscurpiQ(QWidget *parent) : QMainWindow(parent)
{
	backgroundColorButton   = new QPushButton(tr("&Choose"));
	backgroundColorLabel    = new QLabel(tr("Background color:"));
	backgroundRColorLabel   = new QLabel(tr("&R:"));
	backgroundRColorSpinBox = new QSpinBox();
	backgroundGColorLabel   = new QLabel(tr("&G:"));
	backgroundGColorSpinBox = new QSpinBox();
	backgroundBColorLabel   = new QLabel(tr("&B:"));
	backgroundBColorSpinBox = new QSpinBox();
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

	// Setting labels' buddies
	backgroundRColorLabel->setBuddy(backgroundRColorSpinBox);
	backgroundGColorLabel->setBuddy(backgroundGColorSpinBox);
	backgroundBColorLabel->setBuddy(backgroundBColorSpinBox);
	bmpInFileLabel->setBuddy(bmpInFileLineEdit);
	charPerPixelLabel->setBuddy(charPerPixelSpinBox);
	fontSizeLabel->setBuddy(fontSizeSpinBox);
	htmlOutFileLabel->setBuddy(htmlOutFileLineEdit);
	txtInFileLabel->setBuddy(txtInFileLineEdit);

	// Setting spin boxes
	charPerPixelSpinBox->setValue(1);
	fontSizeSpinBox->setSuffix(" px");
	fontSizeSpinBox->setValue(8);
	backgroundRColorSpinBox->setRange(0, 255);
	backgroundGColorSpinBox->setRange(0, 255);
	backgroundBColorSpinBox->setRange(0, 255);

	setWindowTitle("AscurpiQ - Ascurpic Qt GUI");
	createConnections();
	createLayout();
}

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

	// HTML generation.
	connect(generateButton, SIGNAL(clicked()),
	        this, SLOT(generate()));

	// Color selection dialog.
	connect(backgroundColorButton, SIGNAL(clicked()),
	        this, SLOT(selectBackgroundColor()));
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
	QHBoxLayout *rgbLayout         = new QHBoxLayout();

	// RGB values line.
	rgbLayout->addWidget(backgroundRColorLabel);
	rgbLayout->addWidget(backgroundRColorSpinBox);
	rgbLayout->addWidget(backgroundGColorLabel);
	rgbLayout->addWidget(backgroundGColorSpinBox);
	rgbLayout->addWidget(backgroundBColorLabel);
	rgbLayout->addWidget(backgroundBColorSpinBox);

	optionsGridLayout->addWidget(backgroundColorLabel, 0, 0);
	optionsGridLayout->addLayout(rgbLayout, 1, 0, 1, 2);
	optionsGridLayout->addWidget(backgroundColorButton, 2, 0, 1, 2);
	optionsGridLayout->addWidget(fontSizeLabel, 3, 0);
	optionsGridLayout->addWidget(fontSizeSpinBox, 3, 1, 1, 2);
	optionsGridLayout->addWidget(charPerPixelLabel, 4, 0);
	optionsGridLayout->addWidget(charPerPixelSpinBox, 4, 1, 1, 2);

	optionsBox->setLayout(optionsGridLayout);

	// Container layout //
	QGridLayout *containerLayout = new QGridLayout();

	containerLayout->addWidget(filesBox, 0, 0);
	containerLayout->addWidget(optionsBox, 0, 1);
	containerLayout->addWidget(generateButton, 1, 0, 1, 2);

	containerWidget->setLayout(containerLayout);
	setCentralWidget(containerWidget);
}

/**
 * \param[in] qstr QString object to cast.
 * \return A C style string representation of qstr.
 */
const char* AscurpiQ::qStrToChar(const QString &qstr) const
{
	return qstr.toLocal8Bit().data();
}

/* * * * * * * * * *
 * private  slots  *
 * * * * * * * * * */

void AscurpiQ::generate()
{
	// error counter.
	unsigned short err = 0;

	// Check if the required file fields are filled.
	if(bmpInFileLineEdit->text().length() > 0
	   && txtInFileLineEdit->text().length() > 0
	   && htmlOutFileLineEdit->text().length() > 0)
	{
		param_t params;
		//char   *meSertTropARienCePointeur;

		err += open_bmp(&(params.input_bitmap),
		                qStrToChar(bmpInFileLineEdit->text()));
		err += open_file(&(params.input_text),
		                 qStrToChar(txtInFileLineEdit->text()),
				  "r");
		err += open_file(&(params.output_file),
		                 qStrToChar(htmlOutFileLineEdit->text()),
		                 "w");

		params.bgcolor = backgroundRColorSpinBox->value() * 65536
		                 + backgroundGColorSpinBox->value() * 256
		                 + backgroundBColorSpinBox->value();

		params.nbcharpx = charPerPixelSpinBox->value();
		params.fontsize = fontSizeSpinBox->value();

		// if no error happened, we can do that :p
		if(err == 0)
		{
			write_page(&params);
			free_bitmap(params.input_bitmap);
			QMessageBox::information(this,
			                         tr("Success"),
			                         tr("Successfully generated file: ")
			                         + htmlOutFileLineEdit->text());
		}
	}
}

void AscurpiQ::selectBackgroundColor()
{
	QColor newcolor, oldcolor;

	// Current color.
	oldcolor = QColor::fromRgb(backgroundRColorSpinBox->value(),
	                           backgroundGColorSpinBox->value(),
	                           backgroundBColorSpinBox->value());

	// Preselect the current color.
	newcolor = QColorDialog::getColor(oldcolor, this);

	if(newcolor.isValid())
	{
		backgroundRColorSpinBox->setValue(newcolor.red());
		backgroundGColorSpinBox->setValue(newcolor.green());
		backgroundBColorSpinBox->setValue(newcolor.blue());
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
