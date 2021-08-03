// DataMatrix.cpp: определяет точку входа для приложения.
//

#include "DataMatrix.h"
//#define write std::cout
//#define end '\n'

// C:\Users\haost\source\repos\DataMatrix\out\build\x64-Debug\DataMatrix

using namespace std;


struct User : public Serialize
{
public:
	 int ID;
	 std::string Name;

	 size_t serialize(std::ostream& os) override
	 {
		 const auto pos = os.tellp();
		 auto buff = reinterpret_cast<const char*>(&ID);
		 os.write(buff, sizeof(ID));
		 return static_cast<std::size_t>(os.tellp() - pos);
	 }

	 void deserialize(std::istream& stream) override
	 {

	 }


};

template<class T>
auto Write(std::ostream& os, T value)->std::size_t
{
	const auto pos = os.tellp();
	auto buff = reinterpret_cast<const unsigned char*>(&value);
	os.write(buff, sizeof(value));
	return static_cast<std::size_t>(os.tellp() - pos);
}

void Writedata(const char* buff);

int main(int argc, char** argv)
{
	
	
	int d = 10;
	std::string st_10 = "10";
	auto buff = reinterpret_cast<const char*>(&st_10);

	istringstream str(buff);
	DataMatrix::Stream buf(str, cout);

	std::ifstream input("myfile.dat", ios::in | std::ios::binary);
	std::ofstream output("myfile.dat", ios::out | std::ios::binary);

	const auto _len = static_cast<size_t>(sizeof(st_10));
	output.write(buff, _len);
	output.close();

	int i = 0;
	if (input)
	{
		/*const auto pos = output.tellp();
		output << input.rdbuf();
		auto szz = static_cast<std::size_t>(output.tellp() - pos);
		std::cout << szz << '\n';*/

		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
		std::stringstream ss;
		for (int i = 0; i < std::size(buffer); ++i)
			ss << std::hex << (int)buffer[i];
		std::string mystr = ss.str();
	}
	else
	{

	}


	const auto pos = output.tellp();
	const auto len = static_cast<size_t>(sizeof(d));

	output.write(buff, len);

	auto szz = static_cast<std::size_t>(output.tellp() - pos);

	std::cout << szz << '\n';

	/*std::stringstream ss;
	ss << output.rdbuf();
	std::string myString = ss.str();*/

	/*std::copy(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(output));*/

	//output << input.rdbuf();
	//auto rf = output.rdbuf();

	



	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	auto sz = std::size(buffer);
	//write << sz << end;

	std::cout << sz << '\n';

	output.close();
	return 0;
	
}

/// <summary>
/// двоичные данные в строковый поток, а затем передает данные в fstream
/// </summary>
/// <param name="buff">data</param>
void Writedata(const char* buff)
{
	stringstream ss(stringstream::binary | stringstream::in | stringstream::out);
	ss.write(buff, 512);  // Loads data into stream

	// Uses a memory block to pass the data between the streams
	char* memBlock = new char[512];
	ss.read(memBlock, 512);

	ofstream fout("someFile.dat", ios::binary);
	fout.write(memBlock, 512);  // Writes the data to a file
	fout.close();

	delete[] memBlock;
}
