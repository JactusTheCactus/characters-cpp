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
#include <format>
#include <list>
#define omega "\u03C9"
#define acute "\u0301"
#define schwa "\u0259"
#define grave "\u0300"
struct Character
{
	std::string name, pron, sex, species;
	std::list<std::string> extra;
};
int main(int argc, char *argv[])
{
	std::list<Character> characters = {
		{
			"Hound",
			"haund",
			"Female",
			"Changeling",
			{
				"Shapeshifts into a large, black wolf",
			},
		},
		{
			"Morrigan",
			std::format("m{}{}r{}gy{}n", omega, acute, schwa, grave),
			"Female",
			"Reaper",
			{
				"Killing touch",
				"Wields a scythe",
			},
		},
	};
	QApplication app(argc, argv);
	QWidget win;
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QLabel *header = new QLabel("Characters");
	mainLayout->addWidget(header);
	QHBoxLayout *hLayout = new QHBoxLayout();
	for (const Character &c : characters)
	{
		QPushButton *character = new QPushButton(QString::fromStdString(c.name));
		QObject::connect(
			character,
			&QPushButton::clicked,
			[&win, c]()
			{
				std::string sex;
				if (c.sex == "Male")
				{
					sex = "\u2642";
				}
				else if (c.sex == "Female")
				{
					sex = "\u2640";
				}
				else
				{
					sex = "\u26A5";
				}
				std::string body;
				body += std::format("{}{}\n", c.name, sex);
				body += std::format("\t<{}>\n", c.pron);
				body += std::format("Species:\n");
				body += std::format("\t{}\n", c.species);
				body += std::format("Extra:\n");
				for (const std::string &e : c.extra)
				{
					body += std::format("\t- {}\n", e);
				}
				QMessageBox::information(
					&win,
					"Character Selected",
					QString::fromStdString(body));
			});
		hLayout->addWidget(character);
	}
	mainLayout->addLayout(hLayout);
	win.setLayout(mainLayout);
	win.setWindowTitle("Characters");
	win.show();
	return app.exec();
}