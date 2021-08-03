#include <iostream>
#include <sstream>
#include <string>

/*
const char str1[] = "In 4 bytes 55 contains 32 bits";
	const char str2[] = "Unix time starts from Jan 1, 1970";
	istringstream str(str1);

	DataMatrix::Stream buf(str, cout); // ������ �� stringstream, �������� � �������
	iostream numfilter(&buf); // ����� ������� ��������� ��� ���������� ������ ���������� iostream

	string val;
	getline(numfilter, val);
	numfilter.clear(); // �������� ���������� ��������� ����� EOF � �������� ������ �� stringstream

	cout << "Original: '" << str1 << "'" << endl;
	cout << "Read from numfilter: '" << val << "'" << endl;

	cout << "Original: '" << str2 << "'" << endl;
	cout << "Written to numfilter: '";
	numfilter << str2;
	cout << "'" << endl;

	return 0;
*/

namespace DataMatrix
{
	class  Stream : public std::streambuf
	{
	public:
		Stream(std::istream& _in, std::ostream& _out)
			: in(&_in), out(&_out), cur(traits_type::eof())
		{};
		~Stream();
	private:
		std::istream* in;
		std::ostream* out;
		int cur; //��������� ��������� ��������, ������������ � underflow()
	protected:
		/* ������� ������ � �����: */

		virtual int overflow(int c) override {
			if (c == traits_type::eof()) {
				return traits_type::eof();
			}

			char_type ch = static_cast<char_type>(c);
			if (ch == ' ' || (ch >= '0' && ch <= '9')) { // ������ ������� � �����
				out->put(ch);
				//���� ���-�� �� ����������, ������ EOF
				return out->good() ? ch : traits_type::eof();
			}

			return ch;
		}

		/* ������� ������ �� ������: */

		//���������� ��-��������� �������������� ������� ��������� � ������ � �������� segmentation fault
		virtual int uflow() override {
			int c = underflow();
			cur = traits_type::eof(); //������� underflow() ������� ��������� ������ ��� ��������� ������
			return c;
		}

		virtual int underflow() override {
			if (cur != traits_type::eof()) {
				return cur;
			}

			// ���� ����� ������, ������
			while (in->good()) {
				cur = in->get();
				if (cur == traits_type::eof()) {
					return traits_type::eof();
				}

				char_type ch = static_cast<char_type>(cur);
				if (ch == ' ' || (ch >= '0' && ch <= '9')) { // ������ ������ ������� � �����
					return ch;
				}
			}

			return traits_type::eof();
		}
	};
}