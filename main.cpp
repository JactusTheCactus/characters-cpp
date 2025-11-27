#include "src/main.hpp"
int main(int argc, char *argv[])
{
	std::set<Character, CharCompare> characters;
	characters.insert(
		{"Female",
		 {"Hound",
		  ""},
		 {"haund",
		  ""},
		 {"Human",
		  "Changeling"},
		 {"Shapeshifts into a large, black wolf"}});
	characters.insert(
		{"Female",
		 {"Morrigan",
		  "Heffernan"},
		 {std::format("m{}{}r{}gy{}n", omega, acute, schwa, grave),
		  std::format("he{}f{}rny{}n",acute,schwa,grave)},
		 {"Reaper"},
		 {"Killing touch",
		  "Wields a scythe"}});
	std::list<Character> chars(
		characters.begin(),
		characters.end());
	chars.push_front(
		{"",
		 {"Character",
		  "Name"},
		 {std::format("k{}rykt{}r", eh, schwa),
		  std::format("n{}jm", eh)}});
	QApplication app(argc, argv);
	QWidget win;
	win.setWindowTitle("Characters");
	QVBoxLayout *mainLayout = new QVBoxLayout(&win);
	QStackedWidget *stack = new QStackedWidget();
	mainLayout->addWidget(stack);
	QHBoxLayout *buttonRow = new QHBoxLayout();
	mainLayout->addLayout(buttonRow);
	int index = 0;
	for (const Character &c : chars)
	{
		stack->addWidget(new CharView(c));
		if (index > 0)
		{
			std::string name;
			QPushButton *btn = new QPushButton(QString::fromStdString(join(c.name)));
			QObject::connect(
				btn,
				&QPushButton::clicked,
				[stack, index]()
				{
					stack->setCurrentIndex(index);
				});
			buttonRow->addWidget(btn);
			stack->setStyleSheet(css({
				{"font-size",
				 "20pt"},
			}));
		}
		index++;
	}
	win.show();
	return app.exec();
}