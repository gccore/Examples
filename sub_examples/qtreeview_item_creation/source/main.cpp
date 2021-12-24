/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

#include <QTreeWidgetItem>
#include <QApplication>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QPointer>
#include <QWidget>
#include <QLabel>

struct my_widget final : QWidget
{
	QPointer<QTreeWidget> m_list = new QTreeWidget;
	QPointer<QPushButton> m_add_children = new QPushButton("Generate Children");
	QPointer<QPushButton> m_add_item = new QPushButton("Add");
	QPointer<QLineEdit> m_name = new QLineEdit;
	QPointer<QLabel> m_depth_lbn = new QLabel("Depth: ");
	QPointer<QSpinBox> m_depth = new QSpinBox;

	my_widget()
	{
		auto const vlayout = new QVBoxLayout;
		vlayout->addWidget(m_list);
		auto const hlayout = new QHBoxLayout;
		hlayout->addWidget(m_name);
		hlayout->addWidget(m_add_item);
		hlayout->addWidget(m_add_children);
		auto const hlayout2 = new QHBoxLayout;
		hlayout2->addWidget(m_depth_lbn);
		hlayout2->addWidget(m_depth);
		vlayout->addLayout(hlayout);
		vlayout->addLayout(hlayout2);
		setLayout(vlayout);

		m_depth->setValue(3);

		connect(m_add_children, &QPushButton::clicked, this, &my_widget::create_childs);
		connect(m_add_item, &QPushButton::clicked, this, &my_widget::add_item);
	}

	void add_item()
	{
		m_list->addTopLevelItem(new QTreeWidgetItem({m_name->text()}));
		m_name->clear();
	}

	void create_childs()
	{
		auto const items = m_list->selectedItems();
		QTreeWidgetItem* item = nullptr;
		if(!items.isEmpty() && !(item = items[0]))
		{
			return;
		}

		auto const depth = m_depth->value();
		auto const name = item->text(0);

		for(int i = 0; i < depth; ++i)
		{
			auto const top = new QTreeWidgetItem({name + QString::number(i)});

			for(int i = 0; i < depth; ++i)
			{
				auto const child1 = new QTreeWidgetItem(top);
				child1->setText(0, name + QString::number(i));

				for(int i = 0; i < depth; ++i)
				{
					auto const child2 = new QTreeWidgetItem(child1);
					child2->setText(0, name + QString::number(i));
				}
			}

			item->addChild(top);
		}
	}
};

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	my_widget widget;
	widget.show();
	return app.exec();
}
