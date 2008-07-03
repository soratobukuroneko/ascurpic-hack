#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

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

public slots:

private slots:
	void selectBmpFile();
	void selectOutputFile();
	void selectTextFile();

private:
	void createConnections();
	void createLayout();

	QPushButton *backgroundColorButton;
	QLabel      *backgroundColorLabel;
	QLineEdit   *backgroundColorLineEdit;
	QPushButton *bmpInFileButton;
	QLabel      *bmpInFileLabel;
	QLineEdit   *bmpInFileLineEdit;
	QLabel      *charPerPixelLabel;
	QSpinBox    *charPerPixelSpinBox;
	QLabel      *fontSizeLabel;
	QSpinBox    *fontSizeSpinBox;
	QPushButton *htmlOutFileButton;
	QLabel      *htmlOutFileLabel;
	QLineEdit   *htmlOutFileLineEdit;
	QPushButton *txtInFileButton;
	QLabel      *txtInFileLabel;
	QLineEdit   *txtInFileLineEdit;
};

#endif
