#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct FileHeader {
	char bfType[2];
	unsigned int bfSize;
	unsigned short int bfReserved1;
	unsigned short int bfReserved2;
	unsigned int bfOffBits;
};

struct InfoHeader {
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short int biPlanes;
	unsigned short int biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXpelsPerMeter;
	unsigned int biYpelsPerMeter;
	unsigned int biCrlUses;
	unsigned int biCrlImportant;
};

struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct Bitmap {
	FileHeader fileHeader;
	InfoHeader infoHeader;
	vector<vector<Pixel>> pixels;
};

struct Tabs {
	int S1[3][3];
	int S2[3][3];
	int S3[3][3];
	int S4[3][3];
	int S5[3][3];
	int S6[3][3];
	int S7[3][3];
	int S8[3][3];
};

void getTabValue(string tabFileName, int tab[3][3]) {
	ifstream tabFile;
	tabFile.open(tabFileName);
	if (!tabFile) {
		cout << "Blad odczytu danych tablicy" << endl;
	}
	else {
		for (int w = 0; w < 3; w += 1) {
			for (int k = 0; k < 3; k += 1) {
				tabFile >> tab[w][k];
			}
		}
	}
	tabFile.close();
}

Tabs getTabsValues() {
	Tabs tab;
	getTabValue("s1.filter", tab.S1);
	getTabValue("s2.filter", tab.S2);
	getTabValue("s3.filter", tab.S3);
	getTabValue("s4.filter", tab.S4);
	getTabValue("s5.filter", tab.S5);
	getTabValue("s6.filter", tab.S6);
	getTabValue("s7.filter", tab.S7);
	getTabValue("s8.filter", tab.S8);
	return tab;
}

string readInputFileName() {
	cout << "Wprowadz nazwe pliku wejsciowego: ";
	string inputFileName;
	cin >> inputFileName;
	return inputFileName;
}

string readOutputFileName() {
	cout << "Wprowadz nazwe pliku wyjsciowego: ";
	string outputFileName;
	cin >> outputFileName;
	return outputFileName;
}

void readFileHeader(ifstream& file, FileHeader& fileHeader)
{
	file.read((char*)&fileHeader.bfType, sizeof(fileHeader.bfType));
	file.read((char*)&fileHeader.bfSize, sizeof(fileHeader.bfSize));
	file.read((char*)&fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
	file.read((char*)&fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
	file.read((char*)&fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
}

void readInfoHeader(ifstream& file, InfoHeader& infoHeader)
{
	file.read((char*)&infoHeader.biSize, sizeof(infoHeader.biSize));
	file.read((char*)&infoHeader.biWidth, sizeof(infoHeader.biWidth));
	file.read((char*)&infoHeader.biHeight, sizeof(infoHeader.biHeight));
	file.read((char*)&infoHeader.biPlanes, sizeof(infoHeader.biPlanes));
	file.read((char*)&infoHeader.biBitCount, sizeof(infoHeader.biBitCount));
	file.read((char*)&infoHeader.biCompression, sizeof(infoHeader.biCompression));
	file.read((char*)&infoHeader.biSizeImage, sizeof(infoHeader.biSizeImage));
	file.read((char*)&infoHeader.biXpelsPerMeter, sizeof(infoHeader.biXpelsPerMeter));
	file.read((char*)&infoHeader.biYpelsPerMeter, sizeof(infoHeader.biYpelsPerMeter));
	file.read((char*)&infoHeader.biCrlUses, sizeof(infoHeader.biCrlUses));
	file.read((char*)&infoHeader.biCrlImportant, sizeof(infoHeader.biCrlImportant));
}

void print_parametres(InfoHeader infoHeader, FileHeader fileHeader) {
	cout << "Parametry pliku BMP:" << endl << endl << "Naglowek pliku:" << endl << endl;
	cout << "bfType - sygnatura pliku, 'BM' dla prawidlowego pliku BMP" << endl << "Wartosc: " << fileHeader.bfType[0] << fileHeader.bfType[1] << endl;
	cout << "bfSize - dlugosc calego pliku w bajtach" << endl << "Wartosc: " << fileHeader.bfSize << endl;
	cout << "bfReserved1 - pole zarezerwowane (zwykle zero)" << endl << "Wartosc: " << fileHeader.bfReserved1 << endl;
	cout << "bfReserved2 - pole zarezerwowane (zwykle zero)" << endl << "Wartosc: " << fileHeader.bfReserved2 << endl;
	cout << "bfOffBits - pozycja danych obrazowych w pliku" << endl << "Wartosc: " << fileHeader.bfOffBits << endl << endl;
	cout << "Naglowek obrazu:" << endl << endl;
	cout << "biSize - rozmiar naglowka informacyjnego" << endl << "Wartosc: " << infoHeader.biSize << endl;
	cout << "biWidth - szerokosc obrazu w pikselach" << endl << "Wartosc: " << infoHeader.biWidth << endl;
	cout << "biHeight - wysokosc obrazu w pikselach" << endl << "Wartosc: " << infoHeader.biHeight << endl;
	cout << "biPlanes - liczba platow (musi byc 1)" << endl << "Wartosc: " << infoHeader.biPlanes << endl;
	cout << "biBitCount - liczba bitow na piksel: 1, 4, 8, 16, 24 lub 32" << endl << "Wartosc: " << infoHeader.biBitCount << endl;
	cout << "biCompression - algorytm kompresji: BI_RGB=0, BI_RLE8=1, BI_RLE4=2, BI_BITFIELDS=3" << endl << "Wartosc: " << infoHeader.biCompression << endl;
	cout << "biSizeImage - rozmiar rysunku" << endl << "Wartosc: " << infoHeader.biSizeImage << endl;
	cout << "biXpelsPerMeter - rozdzielczosc pozioma" << endl << "Wartosc: " << infoHeader.biXpelsPerMeter << endl;
	cout << "biYpelsPerMeter - rozdzielczosc pionowa" << endl << "Wartosc: " << infoHeader.biYpelsPerMeter << endl;
	cout << "biCrlUses - liczba kolorow w palecie" << endl << "Wartosc: " << infoHeader.biCrlUses << endl;
	cout << "biCrlImportant - liczba waznych kolorow w palecie" << endl << "Wartosc: " << infoHeader.biCrlImportant << endl;
}

Bitmap parseFile(ifstream& file, FileHeader& fileHeader, InfoHeader& infoHeader) {
	Bitmap bitmap;
	bitmap.fileHeader = fileHeader;
	bitmap.infoHeader = infoHeader;
	int zero;
	unsigned char zeros;
	if (infoHeader.biWidth % 4 == 0) {
		zero = 0;
	}
	else {
		zero = 4 - (((infoHeader.biWidth) * 3) % 4);
	}
	const int height = infoHeader.biHeight + 2;
	const int width = infoHeader.biWidth + 2;
	bitmap.pixels.resize(height, vector<Pixel>(width));
	for (int w = 0; w < height; w += 1) {
		for (int k = 0; k < width; k += 1) {
			bitmap.pixels[w][k].b = 0;
			bitmap.pixels[w][k].g = 0;
			bitmap.pixels[w][k].r = 0;
		}
	}
	for (int w = 1; w < height - 1; w += 1) {
		for (int k = 1; k < width - 1; k += 1) {
			file.read((char*)&bitmap.pixels[w][k].b, sizeof(unsigned char));
			file.read((char*)&bitmap.pixels[w][k].g, sizeof(unsigned char));
			file.read((char*)&bitmap.pixels[w][k].r, sizeof(unsigned char));
		}
		for (int i = 0; i < zero; i += 1) {
			file.read((char*)&zeros, sizeof(unsigned char));
		}
	}
	return bitmap;
}

Bitmap parseFileLargeBegin(ifstream& file, FileHeader& fileHeader, InfoHeader& infoHeader, int zero) {
	Bitmap input;
	input.fileHeader = fileHeader;
	input.infoHeader = infoHeader;
	unsigned char zeros;
	const int width = infoHeader.biWidth + 2;
	input.pixels.resize(3, vector<Pixel>(width));
	for (int w = 0; w < 3; w += 1) {
		for (int k = 0; k < width; k += 1) {
			input.pixels[w][k].b = 0;
			input.pixels[w][k].g = 0;
			input.pixels[w][k].r = 0;
		}
	}
	for (int w = 1; w < 3; w += 1) {
		for (int k = 1; k < width - 1; k += 1) {
			file.read((char*)&input.pixels[w][k].b, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].g, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].r, sizeof(unsigned char));
		}
		for (int i = 0; i < zero; i += 1) {
			file.read((char*)&zeros, sizeof(unsigned char));
		}
	}
	return input;
}

void parseFileLarge(Bitmap& input, ifstream& file, FileHeader& fileHeader, InfoHeader& infoHeader, int zero) {
	unsigned char zeros;
	const int width = infoHeader.biWidth + 2;
	for (int w = 0; w < 3; w += 1) {
		for (int k = 1; k < width - 1; k += 1) {
			file.read((char*)&input.pixels[w][k].b, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].g, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].r, sizeof(unsigned char));
		}
		for (int i = 0; i < zero; i += 1) {
			file.read((char*)&zeros, sizeof(unsigned char));
		}
	}
}

void parseFileLargeEnd(Bitmap& input, ifstream& file, FileHeader& fileHeader, InfoHeader& infoHeader, int zero) {
	unsigned char zeros;
	const int width = infoHeader.biWidth + 2;
	for (int w = 0; w < 3; w += 1) {
		for (int k = 0; k < width; k += 1) {
			input.pixels[w][k].b = 0;
			input.pixels[w][k].g = 0;
			input.pixels[w][k].r = 0;
		}
	}
	for (int w = 0; w < 2; w += 1) {
		for (int k = 1; k < width - 1; k += 1) {
			file.read((char*)&input.pixels[w][k].b, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].g, sizeof(unsigned char));
			file.read((char*)&input.pixels[w][k].r, sizeof(unsigned char));
		}
		for (int i = 0; i < zero; i += 1) {
			file.read((char*)&zeros, sizeof(unsigned char));
		}
	}
}

unsigned char checkValue(int suma) {
	if (suma > 255) {
		suma = 255;
		return suma;
	}
	else if (suma < 0) {
		suma = 0;
		return suma;
	}
	else {
		return suma;
	}
}

void checkrgb(Bitmap& input, Bitmap& output, int w, int k, int tab[3][3]) {
	int sumR = 0;
	int sumG = 0;
	int sumB = 0;
	for (int a = -1; a < 2; a += 1) {
		for (int b = -1; b < 2; b += 1) {
			sumR = sumR + input.pixels[w + a][k + b].r * tab[a + 1][b + 1];
			sumG = sumG + input.pixels[w + a][k + b].g * tab[a + 1][b + 1];
			sumB = sumB + input.pixels[w + a][k + b].b * tab[a + 1][b + 1];
		}
	}
	unsigned char tempR = checkValue(sumR);
	unsigned char tempG = checkValue(sumG);
	unsigned char tempB = checkValue(sumB);
	if (tempR > output.pixels[w][k].r) {
		output.pixels[w][k].r = tempR;
	}
	if (tempG > output.pixels[w][k].g) {
		output.pixels[w][k].g = tempG;
	}
	if (tempB > output.pixels[w][k].b) {
		output.pixels[w][k].b = tempB;
	}
}

Bitmap process(Bitmap& input, Tabs& tab) {
	Bitmap output;
	const int width = input.infoHeader.biWidth + 2;
	const int height = input.infoHeader.biHeight + 2;
	output.fileHeader = input.fileHeader;
	output.infoHeader = input.infoHeader;
	output.pixels.resize(height, vector<Pixel>(width));
	for (int w = 0; w < height; w += 1) {
		for (int k = 0; k < width; k += 1) {
			output.pixels[w][k].r = 0;
			output.pixels[w][k].g = 0;
			output.pixels[w][k].b = 0;
		}
	}
	for (int w = 1; w < height - 1; w += 1) {
		for (int k = 1; k < width - 1; k += 1) {
			checkrgb(input, output, w, k, tab.S1);
			checkrgb(input, output, w, k, tab.S2);
			checkrgb(input, output, w, k, tab.S3);
			checkrgb(input, output, w, k, tab.S4);
			checkrgb(input, output, w, k, tab.S5);
			checkrgb(input, output, w, k, tab.S6);
			checkrgb(input, output, w, k, tab.S7);
			checkrgb(input, output, w, k, tab.S8);
		}
	}
	return output;
}

Bitmap processLargeBegin(Bitmap& input, Tabs& tab) {
	Bitmap output;
	const int width = input.infoHeader.biWidth + 2;
	output.fileHeader = input.fileHeader;
	output.infoHeader = input.infoHeader;
	output.pixels.resize(3, vector<Pixel>(width));
	for (int w = 0; w < 3; w += 1) {
		for (int k = 0; k < width; k += 1) {
			output.pixels[w][k].r = 0;
			output.pixels[w][k].g = 0;
			output.pixels[w][k].b = 0;
		}
	}
	for (int k = 1; k < width - 1; k += 1) {
		checkrgb(input, output, 1, k, tab.S1);
		checkrgb(input, output, 1, k, tab.S2);
		checkrgb(input, output, 1, k, tab.S3);
		checkrgb(input, output, 1, k, tab.S4);
		checkrgb(input, output, 1, k, tab.S5);
		checkrgb(input, output, 1, k, tab.S6);
		checkrgb(input, output, 1, k, tab.S7);
		checkrgb(input, output, 1, k, tab.S8);
	}
	return output;
}

void processLarge(Bitmap& input, Bitmap& output, Tabs& tab) {
	const int width = input.infoHeader.biWidth + 2;
	for (int w = 0; w < 3; w += 1) {
		for (int k = 0; k < width; k += 1) {
			output.pixels[w][k].r = 0;
			output.pixels[w][k].g = 0;
			output.pixels[w][k].b = 0;
		}
	}
	for (int k = 1; k < width - 1; k += 1) {
		checkrgb(input, output, 1, k, tab.S1);
		checkrgb(input, output, 1, k, tab.S2);
		checkrgb(input, output, 1, k, tab.S3);
		checkrgb(input, output, 1, k, tab.S4);
		checkrgb(input, output, 1, k, tab.S5);
		checkrgb(input, output, 1, k, tab.S6);
		checkrgb(input, output, 1, k, tab.S7);
		checkrgb(input, output, 1, k, tab.S8);
	}
}

void writeFileHeader(ofstream& file, FileHeader& fileHeader)
{
	file.write((char*)&fileHeader.bfType, sizeof(fileHeader.bfType));
	file.write((char*)&fileHeader.bfSize, sizeof(fileHeader.bfSize));
	file.write((char*)&fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
	file.write((char*)&fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
	file.write((char*)&fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
}

void writeInfoHeader(ofstream& file, InfoHeader& infoHeader)
{
	file.write((char*)&infoHeader.biSize, sizeof(infoHeader.biSize));
	file.write((char*)&infoHeader.biWidth, sizeof(infoHeader.biWidth));
	file.write((char*)&infoHeader.biHeight, sizeof(infoHeader.biHeight));
	file.write((char*)&infoHeader.biPlanes, sizeof(infoHeader.biPlanes));
	file.write((char*)&infoHeader.biBitCount, sizeof(infoHeader.biBitCount));
	file.write((char*)&infoHeader.biCompression, sizeof(infoHeader.biCompression));
	file.write((char*)&infoHeader.biSizeImage, sizeof(infoHeader.biSizeImage));
	file.write((char*)&infoHeader.biXpelsPerMeter, sizeof(infoHeader.biXpelsPerMeter));
	file.write((char*)&infoHeader.biYpelsPerMeter, sizeof(infoHeader.biYpelsPerMeter));
	file.write((char*)&infoHeader.biCrlUses, sizeof(infoHeader.biCrlUses));
	file.write((char*)&infoHeader.biCrlImportant, sizeof(infoHeader.biCrlImportant));
}

void writeBitmap(ofstream& file, Bitmap& output) {
	int zero;
	unsigned char zeros;
	if (output.infoHeader.biWidth % 4 == 0) {
		zero = 0;
	}
	else {
		zero = 4 - (((output.infoHeader.biWidth) * 3) % 4);
	}
	for (int w = 1; w < output.infoHeader.biHeight + 1; w += 1) {
		for (int k = 1; k < output.infoHeader.biWidth + 1; k += 1) {
			file.write((char*)&output.pixels[w][k].b, sizeof(unsigned char));
			file.write((char*)&output.pixels[w][k].g, sizeof(unsigned char));
			file.write((char*)&output.pixels[w][k].r, sizeof(unsigned char));
		}
		for (int i = 0; i < zero; i += 1) {
			file.write((char*)&zeros, sizeof(unsigned char));
		}
	}
}

void writeBitmapLarge(ofstream& file, Bitmap& output, int zero) {
	unsigned char zeros;
	for (int k = 1; k < output.infoHeader.biWidth + 1; k += 1) {
		file.write((char*)&output.pixels[1][k].b, sizeof(unsigned char));
		file.write((char*)&output.pixels[1][k].g, sizeof(unsigned char));
		file.write((char*)&output.pixels[1][k].r, sizeof(unsigned char));
	}
	for (int i = 0; i < zero; i += 1) {
		file.write((char*)&zeros, sizeof(unsigned char));
	}
}

int main()
{
	Tabs tab;
	tab = getTabsValues();
	string inputFileName = readInputFileName();
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open(inputFileName, ios::binary);
	if (!inputFile) {
		cout << "Nie udalo sie otworzyc pliku";
		return 0;
	}
	else {
		cout << "Pomyslnie otwarto plik" << endl << endl;
	}
	FileHeader fileHeader;
	InfoHeader infoHeader;
	readFileHeader(inputFile, fileHeader);
	readInfoHeader(inputFile, infoHeader);
	print_parametres(infoHeader, fileHeader);
	cout << endl << "Wybierz tryb przetwarzania pliku (1 - wczytanie obrazu w calosci, 2 - wczytanie obrazu we fragmentach): ";
	char mode;
	cin >> mode;
	while (mode != '1' && mode != '2') {
		cout << "Blad, wybierz ponownie: ";
		cin >> mode;
	}
	if (mode == '1') {
		Bitmap input = parseFile(inputFile, fileHeader, infoHeader);
		Bitmap output = process(input, tab);
		inputFile.close();
		string outputFileName = readOutputFileName();
		outputFile.open(outputFileName, ios::binary);
		writeFileHeader(outputFile, fileHeader);
		writeInfoHeader(outputFile, infoHeader);
		writeBitmap(outputFile, output);
		outputFile.close();
		cout << "Plik zostal pomyslnie utworzony";
	}
	else {
		string outputFileName = readOutputFileName();
		outputFile.open(outputFileName, ios::binary);
		writeFileHeader(outputFile, fileHeader);
		writeInfoHeader(outputFile, infoHeader);
		int zero; //liczba zer w wierszu
		if (infoHeader.biWidth % 4 == 0) {
			zero = 0;
		}
		else {
			zero = 4 - (((infoHeader.biWidth) * 3) % 4);
		}
		int back = -2 * (infoHeader.biWidth);
		Bitmap input = parseFileLargeBegin(inputFile, fileHeader, infoHeader, zero);
		inputFile.seekg(back, ios::cur);
		Bitmap output = processLargeBegin(input, tab);
		writeBitmapLarge(outputFile, output, zero);
		for (int row = 1; row < infoHeader.biHeight - 1; row += 1) {
			parseFileLarge(input, inputFile, fileHeader, infoHeader, zero);
			inputFile.seekg(back, ios::cur);
			processLarge(input, output, tab);
			writeBitmapLarge(outputFile, output, zero);
		}
		parseFileLargeEnd(input, inputFile, fileHeader, infoHeader, zero);
		inputFile.seekg(back, ios::cur);
		processLarge(input, output, tab);
		writeBitmapLarge(outputFile, output, zero);
		inputFile.close();
		outputFile.close();
		cout << "Plik zostal pomyslnie utworzony";
	}
	return 0;
}