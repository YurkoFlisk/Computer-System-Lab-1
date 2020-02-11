#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	char base64[64];
	for (int i = 0; i < 26; ++i)
		base64[i] = 'A' + i;
	for (int i = 26; i < 52; ++i)
		base64[i] = 'a' + i - 26;
	for (int i = 52; i < 62; ++i)
		base64[i] = '0' + i - 52;
	base64[62] = '+';
	base64[63] = '/';

	while (true)
	{
		string input, savePath;
		cout << "Enter path to the file you want to encode (quit for exit): ";
		getline(cin, input);
		if (input == "quit")
			break;

		ifstream ifs;
		try
		{
			ifs.open(input, ios::binary);
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
			continue;
		}

		cout << "Enter path to save the encoded file: ";
		getline(cin, savePath);

		ofstream ofs;
		try
		{
			ofs.open(savePath);
		}
		catch (const exception & ex)
		{
			cout << ex.what() << endl;
			continue;
		}

		int bitsFromPrev = 0;
		char ch, prevCh;
		for (; ifs.get(ch); prevCh = ch)
		{
			switch (bitsFromPrev)
			{
			case 0:
				ofs.put(base64[(ch & 0b11111100) >> 2]);
				bitsFromPrev = 2;
				break;
			case 2:
				ofs.put(base64[((prevCh & 0b00000011) << 4) | ((ch & 0b11110000) >> 4)]);
				bitsFromPrev = 4;
				break;
			case 4:
				ofs.put(base64[((prevCh & 0b00001111) << 2) | ((ch & 0b11000000) >> 6)]);
				ofs.put(base64[ch & 0b00111111]);
				bitsFromPrev = 0;
				break;
			}
		}
		if (bitsFromPrev == 2)
		{
			ofs.put(base64[(prevCh & 0b00000011) << 4]);
			ofs.write("==", 2);
		}
		else if (bitsFromPrev == 4)
		{
			ofs.put(base64[(prevCh & 0b00001111) << 2]);
			ofs.put('=');
		}

		cout << "File was encoded successfully." << endl;
		cout << "------------------------------" << endl;
	}
	return 0;
}