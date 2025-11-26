#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <string>
#include <unordered_map>
#include <csignal>
#include <string>
#include <sstream>
#include <format>
std::unordered_map<
	std::string,
	std::unordered_map<
		std::string,
		std::string>>
	chars = {
		{"hound",
		 {{"name", "Hound"},
		  {"sex", "Female"}}},
		{"morrigan",
		 {{"name", "Morrigan"},
		  {"sex", "Female"}}}};
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget win;
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QLabel *header = new QLabel("Characters");
	mainLayout->addWidget(header);
	QHBoxLayout *hLayout = new QHBoxLayout();
	for (const auto &[k, _] : chars)
	{
		const auto &c = chars.at(k);
		std::string name = c.at("name");
		std::string s = c.at("sex");
		std::string sex =
			s == "Male"
				? "\u2642"
			: s == "Female"
				? "\u2640"
				: "\u26A5";
		QPushButton *character = new QPushButton(QString::fromStdString(name));
		QObject::connect(
			character,
			&QPushButton::clicked,
			[&win, name, sex]()
			{
				QMessageBox::information(
					&win,
					"Character Selected",
					QString::fromStdString(std::format("You selected {}{}!", name, sex)));
			});
		hLayout->addWidget(character);
	}
	mainLayout->addLayout(hLayout);
	win.setLayout(mainLayout);
	win.setWindowTitle("Characters");
	win.show();
	return app.exec();
}
