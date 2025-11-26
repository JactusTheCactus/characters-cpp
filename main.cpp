#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <list>
int main(int argc, char *argv[])
{
	std::list<QString> chars = {
		"Hound",
		"Morrigan",
	};
	QApplication app(argc, argv);
	QWidget win;
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QLabel *label = new QLabel("Characters");
	mainLayout->addWidget(label);
	QHBoxLayout *hLayout = new QHBoxLayout();
	for (const QString &c : chars)
	{
		QPushButton *ch = new QPushButton(c);
		hLayout->addWidget(ch);
	}
	mainLayout->addLayout(hLayout);
	win.setLayout(mainLayout);
	win.show();
	return app.exec();
}
