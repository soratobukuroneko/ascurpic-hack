#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include "gui.h"

/* * * * * *
 * public  *
 * * * * * */
 
AscurpiQ::AscurpiQ(QWidget *parent) : QMainWindow(parent)
{
	backgroundColorLabel    = new QLabel(tr("Background color:"));
	backgroundColorLineEdit = new QLineEdit("ffffff");
	bmpInFileLabel          = new QLabel(tr("Bitmap file:"));
	bmpInFileLineEdit       = new QLineEdit();
	charPerPixelLabel       = new QLabel(tr("Characters per pixel:"));
	charPerPixelSpinBox     = new QSpinBox();
	fontSizeLabel           = new QLabel(tr("Font size:"));
	fontSizeSpinBox         = new QSpinBox();
	htmlOutFileLabel        = new QLabel(tr("Output file:"));
	htmlOutFileLineEdit     = new QLineEdit();
	txtInFileLabel          = new QLabel(tr("Text file:"));
	txtInFileLineEdit       = new QLineEdit();

	charPerPixelSpinBox->setValue(1);
	fontSizeSpinBox->setSuffix(" px");
	fontSizeSpinBox->setValue(8);

	setWindowTitle("AscurpiQ - Ascurpic Qt GUI");
	createLayout();
}

/* * * * * * * * *
 * public  slots *
 * * * * * * * * */

/* * * * * *
 * private *
 * * * * * */

void AscurpiQ::createLayout()
{
	QGroupBox   *filesBox       = new QGroupBox(tr("Files"));
	QHBoxLayout *bmpFileLayout  = new QHBoxLayout();
	QHBoxLayout *htmlFileLayout = new QHBoxLayout();
	QHBoxLayout *txtFileLayout  = new QHBoxLayout();
	QVBoxLayout *filesBoxLayout = new QVBoxLayout();

	bmpFileLayout->addWidget(bmpInFileLabel);
	bmpFileLayout->addStretch();
	bmpFileLayout->addWidget(bmpInFileLineEdit);
	htmlFileLayout->addWidget(htmlOutFileLabel);
	htmlFileLayout->addStretch();
	htmlFileLayout->addWidget(htmlOutFileLineEdit);
	txtFileLayout->addWidget(txtInFileLabel);
	txtFileLayout->addStretch();
	txtFileLayout->addWidget(txtInFileLineEdit);

	filesBoxLayout->addLayout(bmpFileLayout);
	filesBoxLayout->addLayout(htmlFileLayout);
	filesBoxLayout->addLayout(txtFileLayout);
	filesBoxLayout->addStretch();

	//htmlOutFileLineEdit->resize(bmpInFileLabel->sizeHint());
	//txtInFileLineEdit->resize(bmpInFileLabel->sizeHint());

	filesBox->setLayout(filesBoxLayout);
	setCentralWidget(filesBox);
}

 /* * * * * * * * * *
 * private  slots  *
 * * * * * * * * * */
