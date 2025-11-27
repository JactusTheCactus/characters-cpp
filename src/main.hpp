#include "pre.hpp"
std::string join(const auto &r, const std::string &sep = " ")
{
	std::string out;
	auto i = std::begin(r);
	if (i != std::end(r))
	{
		if (*i != "")
		{
			out += *i;
		}
		i++;
	}
	while (i != std::end(r))
	{
		if (*i != "")
		{
			out += sep + *i;
		}
		i++;
	}
	return out;
}
QString css(std::unordered_map<std::string, std::string> style)
{
	std::ostringstream out;
	for (const auto &[key, value] : style)
	{
		out << std::format("{}:{};", key, value);
	}
	return QString::fromStdString(out.str());
}
struct Character
{
	std::string sex;
	std::string name[2];
	std::string pron[2];
	std::list<std::string> species;
	std::set<std::string> extra;
};
struct CharCompare
{
	bool operator()(const Character &a, const Character &b) const
	{
		std::string A[2];
		std::copy(a.name, a.name + 2, A);
		reverse(A, A + (sizeof(A) / sizeof(A[0])));
		std::string B[2];
		std::copy(b.name, b.name + 2, B);
		reverse(B, B + (sizeof(B) / sizeof(B[0])));
		return join(A) < join(B);
	}
};
class CharView : public QWidget
{
public:
	CharView(const Character &c, QWidget *parent = nullptr) : QWidget(parent)
	{
		auto layout = new QVBoxLayout(this);
		auto n = new QLabel(QString::fromStdString(std::format(
			"{}{}",
			c.sex == "Male"
				? "\u2642"
			: c.sex == "Female"
				? "\u2640"
				: "\u26A5",
			join(c.name, " "))));
		n->setStyleSheet(css({
			{"font-size",
			 "30pt"},
			{"font-weight",
			 "bold"},
		}));
		layout->addWidget(n);
		auto p = new QLabel(QString::fromStdString(std::format("<{}>", join(c.pron, "|"))));
		p->setStyleSheet(css({
			{"font-size",
			 "25pt"},
			{"color",
			 "#666"},
		}));
		layout->addWidget(p);
		auto s = new QLabel("Species:");
		layout->addWidget(s);
		std::list<std::string> species;
		if (c.species.size() < 1)
		{
			species = {"Human"};
		}
		else
		{
			species = c.species;
		}
		for (const std::string &i : species)
		{
			layout->addWidget(new QLabel(QString::fromStdString(std::format("- {}", i))));
		}
		if (c.extra.size() > 0)
		{
			auto e = new QLabel("Extra:");
			layout->addWidget(e);
			for (const std::string &i : c.extra)
			{
				layout->addWidget(new QLabel(QString::fromStdString(std::format("- {}", i))));
			}
		}
		layout->addStretch();
	}
};