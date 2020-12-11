#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


vector <string> Trim(string str) // splits string devided by '.' into substrings 
{
	vector <string> rez;
	string temp;

	//int i = 0;
	for  (char letter : str)
	{
		if (letter == '.')
		{
			rez.push_back(temp);
			temp = "";
			
		}
		else
		{
			temp += letter;
		}
	}
	rez.push_back(temp);
	return rez;
}

bool OctetCheck(vector<string> str) // returns false if one of the octets or their amount is wrong
{
	if (str.size() != 4)
		return false;
	for (string word : str)
	{
		if (stoi(word) < 0 || stoi(word) > 255)
			return false;
	}
	return true;
}

bool MaskCheck(string str) // returns false if mask sequence is wrong
{
	if (str[0] != '1')
		return false;
	bool zeroMet = false;
	for (char letter : str)
	{
		if (letter == '0')
		{
			zeroMet = true; 
		}
		else
		{
			if (zeroMet) // if 0 is followed by 1
				return false; 
		}
	}
	return true;
}

void main()
{
	string ip, mask;
	

	int temp;
	char tempstr[30];
	string str;
	string binaryip = "";
	string binarymask = "";
	vector <string> ipTrim;
	vector <string> maskTrim;
	int option = 0;
	cout << "Choose option:\n1 - Console input\n2 - File input(input.txt)\n";
	cin >> option;
	if (option == 1)
		while (true)
	{
		binaryip = "";
		binarymask = "";

		cin.clear();
		cout << "IP:\t";
		cin >> ip;
		cout << "Mask:\t";
		cin >> mask;

		ipTrim = Trim(ip);
		maskTrim = Trim(mask);

		if (!OctetCheck(ipTrim))
		{
			cout << "Wrong ip\n\n";
			continue;
		}
		if (!OctetCheck(maskTrim))
		{
			cout << "Wrong mask\n\n";
			continue;
		}
		for (int i : {0, 1, 2, 3})
		{
			temp = stoi(ipTrim[i]);
			_itoa_s(temp, tempstr, 2);
			str = tempstr; // for length check only
			for (int i = str.length(); i < 8; i++)
				binaryip += '0';
			binaryip += tempstr;
		}

		for (int i : {0, 1, 2, 3})
		{
			temp = stoi(maskTrim[i]);
			_itoa_s(temp, tempstr, 2);
			str = tempstr; // for length check only
			for (int i = str.length(); i < 8; i++)
				binarymask += '0';
			binarymask += tempstr;
		}

		if (!MaskCheck(binarymask))
		{
			cout << "Wrong mask sequence\n\n";
			continue;
		}

		cout << "IP:\t";
		for (int i = 0; i < 32; i++)
		{
			cout << binaryip[i];
			if (i % 8 == 7 && i != 31)
				cout << ".";
		}
		cout << endl << "Mask:\t";
		for (int i = 0; i < 32; i++)
		{
			cout << binarymask[i];
			if (i % 8 == 7 && i != 31)
				cout << ".";
		}

		cout << endl << "Subnet:\t";
		for (int i : {0, 1, 2, 3})
		{
			cout << (atoi(ipTrim[i].c_str()) & atoi(maskTrim[i].c_str()));
			if (i != 3)
				cout << ".";
		}
		cout << endl << "Host:\t";
		for (int i : {0, 1, 2, 3})
		{
			cout << (atoi(ipTrim[i].c_str()) & ~atoi(maskTrim[i].c_str()));
			if (i != 3)
				cout << ".";
		}



		cout << endl << endl;

	}
	else
	{
		char* line = new char[100];
		
		ifstream fin("input.txt");
		while (!fin.eof())
		{
			fin.getline(line, 100);
			if (line == "") continue;
			ip = line;
			fin.getline(line, 100);
			if (line == "") continue;
			mask = line;

			binaryip = "";
			binarymask = "";

			cin.clear();
			cout << "IP:\t" << ip << "\n";
			cout << "Mask:\t" << mask << "\n";
			ipTrim = Trim(ip);
			maskTrim = Trim(mask);

			if (!OctetCheck(ipTrim))
			{
				cout << "Wrong ip\n\n";
				continue;
			}
			if (!OctetCheck(maskTrim))
			{
				cout << "Wrong mask\n\n";
				continue;
			}
			for (int i : {0, 1, 2, 3})
			{
				temp = stoi(ipTrim[i]);
				_itoa_s(temp, tempstr, 2);
				str = tempstr; // for length check only
				for (int i = str.length(); i < 8; i++)
					binaryip += '0';
				binaryip += tempstr;
			}

			for (int i : {0, 1, 2, 3})
			{
				temp = stoi(maskTrim[i]);
				_itoa_s(temp, tempstr, 2);
				str = tempstr; // for length check only
				for (int i = str.length(); i < 8; i++)
					binarymask += '0';
				binarymask += tempstr;
			}

			if (!MaskCheck(binarymask))
			{
				cout << "Wrong mask sequence\n\n";
				continue;
			}

			cout << "IP:\t";
			for (int i = 0; i < 32; i++)
			{
				cout << binaryip[i];
				if (i % 8 == 7 && i != 31)
					cout << ".";
			}
			cout << endl << "Mask:\t";
			for (int i = 0; i < 32; i++)
			{
				cout << binarymask[i];
				if (i % 8 == 7 && i != 31)
					cout << ".";
			}

			cout << endl << "Subnet:\t";
			for (int i : {0, 1, 2, 3})
			{
				cout << (atoi(ipTrim[i].c_str()) & atoi(maskTrim[i].c_str()));
				if (i != 3)
					cout << ".";
			}
			cout << endl << "Host:\t";
			for (int i : {0, 1, 2, 3})
			{
				cout << (atoi(ipTrim[i].c_str()) & ~atoi(maskTrim[i].c_str()));
				if (i != 3)
					cout << ".";
			}

			

			cout << endl << endl;
		}
		fin.close();
		cout << "Work finished\n";
		
	}

	getchar();
	getchar();
}