#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "../include/ascurpic.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;

/**
 * \brief The application's main window.
 */
class AscurpiQ : public QMainWindow
{
	Q_OBJECT

public:
	AscurpiQ(QWidget *parent = 0);

private slots:
	/// Generates the HTML page.
	void generate();
	/// Display a color selection dialog.
	void selectBackgroundColor();
	// @{
	/// Display a file selection dialog.
	void selectBmpFile();
	void selectOutputFile();
	void selectTextFile();
	// @}

private:
	/// Establishes connections between widgets signals and slots.
	void createConnections();
	/// Lays out the widgets on the Windows .
	void createLayout();
	/// Convert a QString to a C style string.
	const char* qStrToChar(const QString&) const;

	QPushButton *backgroundColorButton;
	QLabel      *backgroundColorLabel;
	QLabel      *backgroundRColorLabel;
	QSpinBox    *backgroundRColorSpinBox;
	QLabel      *backgroundGColorLabel;
	QSpinBox    *backgroundGColorSpinBox;
	QLabel      *backgroundBColorLabel;
	QSpinBox    *backgroundBColorSpinBox;
	QPushButton *bmpInFileButton;
	QLabel      *bmpInFileLabel;
	QLineEdit   *bmpInFileLineEdit;
	QLabel      *charPerPixelLabel;
	QSpinBox    *charPerPixelSpinBox;
	QLabel      *fontSizeLabel;
	QSpinBox    *fontSizeSpinBox;
	QPushButton *generateButton;
	QPushButton *htmlOutFileButton;
	QLabel      *htmlOutFileLabel;
	QLineEdit   *htmlOutFileLineEdit;
	QPushButton *txtInFileButton;
	QLabel      *txtInFileLabel;
	QLineEdit   *txtInFileLineEdit;
};

#endif
