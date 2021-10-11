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

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QApplication>
#include <QHeaderView>
#include <QTableView>
#include <QLineEdit>

class custom_header_t final: public QHeaderView
{
	Q_OBJECT

	QLineEdit m_input;
	int m_section;

public:
	explicit custom_header_t(Qt::Orientation orientation,
				 QWidget* parent = nullptr)
		: QHeaderView(orientation, parent)
	{
		m_input.setParent(viewport());
		m_input.setHidden(true);
		setSectionsClickable(true);
		setSectionsMovable(true);
		connect(this, &custom_header_t::sectionDoubleClicked,
			this, &custom_header_t::on_editing);
		connect(&m_input, &QLineEdit::textChanged,
			this, &custom_header_t::on_text_changed);
	}

	void on_text_changed()
	{
		emit filterTextChanged(m_input.text(), m_section);
	}

	void on_editing(int const index)
	{
		m_section = index;
		auto geometry = m_input.geometry();
		if (Qt::Horizontal == orientation())
		{
			geometry.setWidth(sectionSize(index));
			geometry.setHeight(25); /// FIXME: Set the section height
		}
		else if (Qt::Vertical == orientation())
		{
			geometry.setHeight(sectionSize(index));
		}
		geometry.moveLeft(sectionViewportPosition(index));
		m_input.setGeometry(geometry);
		m_input.setHidden(false);
		m_input.setFocus();
	}

signals:
	void filterTextChanged(QString const& text, int const section);
};
#include "main.moc"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QStandardItemModel model;
	QSortFilterProxyModel filter;
	QTableView table;
	custom_header_t header(Qt::Horizontal);
	filter.setSourceModel(&model);
	table.setModel(&filter);
	table.setHorizontalHeader(&header);

	QObject::connect(&header, &custom_header_t::filterTextChanged,
			 &app, [&](QString const & text, int const section)
	{
		filter.setFilterRegularExpression(text);
		filter.setFilterKeyColumn(section);
	});

	model.setHeaderData(0, Qt::Horizontal, "1");
	model.setHeaderData(0, Qt::Horizontal, "2");
	model.appendRow({new QStandardItem("_1"), new QStandardItem("_2")});
	model.appendRow({new QStandardItem("_3"), new QStandardItem("_4")});
	model.appendRow({new QStandardItem("_5"), new QStandardItem("_6")});

	table.show();
	return app.exec();
}
