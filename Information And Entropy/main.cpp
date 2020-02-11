#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		string input;
		cout << "Enter path to the file you want to analyse (quit for exit): ";
		getline(cin, input);
		if (input == "quit")
			break;

		ifstream ifs;
		try
		{
			ifs.open(input);
		}
		catch (const exception & ex)
		{
			cout << ex.what() << endl;
			continue;
		}

		map<char, int> chars;
		int length = 0;
		double H = 0.0;
		for (char ch; ifs.get(ch); )
			++chars[ch], ++length;
		cout << "Length of the text: " << length << " symbols." << endl;
		cout << "Characters counts and probabilities" << endl;
		for (const auto& [ch, cnt] : chars)
		{
			const double p = (double)cnt / length;
			H -= p * log2(p);
			cout << "'" << ch << "': Count - " << cnt << ", p - " << p << endl;
		}
		cout << "Entropy of the alphabet: " << H << "." << endl;
		cout << "Information content of the file content: "
			<< H * length / 8 << " bytes." << endl;
		cout << "------------------------------" << endl;
	}
	return 0;
}