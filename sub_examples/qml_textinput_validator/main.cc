#include <QtGui/QGuiApplication>
#include <QtGui/QValidator>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QDebug>

class IdiotValidator: public QValidator {
	Q_OBJECT
	Q_PROPERTY(int bottom READ bottom WRITE setBottom)
	Q_PROPERTY(int top READ top WRITE setTop)
	QML_ELEMENT
	
public:
	State validate(QString& input, int& pos) const override
	{
		QString clone = input;
		if (clone.isEmpty()) {
			return State::Intermediate;
		}

		if (bottom() >= 0 && clone[0] == '-') {
			return State::Invalid;
		}
		if (top() < 0 && clone[0] != '-') {
			return State::Invalid;
		}

		bool const is_signed = clone[0] == '+' || clone[0] == '-';
		if (is_signed && clone.size() == 1) {
			return State::Intermediate;
		}

		bool ok = false;
		int value = clone.toInt(&ok);
		if (ok == false) {
			return State::Invalid;
		}

		if (is_signed) {
			clone.remove(0, 1);
		}

		if (clone.size() < minimum_digits_) {
			if (clone.isEmpty()) {
				return State::Intermediate;
			}
			if (clone[0].toLatin1() - '0' > first_bottom_digit_) {
				return State::Invalid;
			}
			return State::Intermediate;
		}

		return value >= bottom() && value <= top() ?
			State::Acceptable : State::Invalid;
	}

	int bottom() const { return bottom_; }
        int top() const { return top_; }
	void setBottom(int const bottom) {
		bottom_ = bottom;

		auto bottom_string = QString::number(bottom);
		if (bottom_string[0] == '+' || bottom_string[0] == '-') {
			bottom_string.remove(0, 1);
		}
		minimum_digits_ = bottom_string.size();
		first_bottom_digit_ = bottom_string[0].toLatin1() - '0';
	}
	void setTop(int const top) { top_ = top; }

private:
	int bottom_ = 0;
	int top_ = 0;
	int minimum_digits_ = 0;
	int first_bottom_digit_ = 0;
};

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<IdiotValidator>("idiot.validator", 1, 0, "IdiotValidator");
	QQmlApplicationEngine engine;
	engine.load(QUrl("qrc:/main.qml"));
	
	return QGuiApplication::exec();
}

#include "main.moc"
