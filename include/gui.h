#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QSpinBox;

/**
 * \brief The application's main window.
 */
class AscurpiQ : public QMainWindow
{
	//Q_OBJECT

public:
	AscurpiQ(QWidget *parent = 0);

public slots:

private slots:

private:
	void createLayout();

	QLabel    *backgroundColorLabel;
	QLineEdit *backgroundColorLineEdit;
	QLabel    *bmpInFileLabel;
	QLineEdit *bmpInFileLineEdit;
	QLabel    *charPerPixelLabel;
	QSpinBox  *charPerPixelSpinBox;
	QLabel    *fontSizeLabel;
	QSpinBox  *fontSizeSpinBox;
	QLabel    *htmlOutFileLabel;
	QLineEdit *htmlOutFileLineEdit;
	QLabel    *txtInFileLabel;
	QLineEdit *txtInFileLineEdit;
};

#endif
