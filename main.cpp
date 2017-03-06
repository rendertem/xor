#include <iostream>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char version[8] = "1.0.0.0";

int boolInInt(bool rv)
{
	if(rv)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct byte
{
	public:
	bool b0 : 1;
	bool b1 : 1;
	bool b2 : 1;
	bool b3 : 1;
	bool b4 : 1;
	bool b5 : 1;
	bool b6 : 1;
	bool b7 : 1;
};

int xorVerschlueseln()
{
	FILE *mesF;
	FILE *keyF;
	FILE *xorF;
	bool dateiFehler = false;

	mesF = fopen("mes.txt", "r");
	keyF = fopen("key.txt", "r");
	xorF = fopen("xor.txt", "w");

	if(mesF == NULL)
	{
		fprintf(stderr, "Fehler: \"mes.txt\" ist nicht vorhanden.\n");
		dateiFehler = true;
	}
	if(keyF == NULL)
	{
		fprintf(stderr, "Fehler: \"key.txt\" ist nicht vorhanden.\n");
		dateiFehler = true;
	}
	if(xorF == NULL)
	{
		fprintf(stderr, "Fehler: \"xor.txt\" ist nicht vorhanden.\n");
		dateiFehler = true;
	}
	if(dateiFehler)
	{
		return 2;
	}
	if(!(mesF == NULL || keyF == NULL || xorF == NULL))
	{
		int c = 0;
		int c2 = 0;
		int c3 = 0;
		while((c = getc(mesF)) != EOF)
		{
			byte bits;
			byte bits2;
			byte bits3;
			if((c2 = getc(keyF)) == EOF)
			{
				fprintf(stderr, "Fehler: \"key.txt\" ist kürzer als \"mes.txt\".\n");
				return 1;
			}
			bits.b0 = (c & 0x01) != 0;
			bits.b1 = (c & 0x02) != 0;
			bits.b2 = (c & 0x04) != 0;
			bits.b3 = (c & 0x08) != 0;
			bits.b4 = (c & 0x10) != 0;
			bits.b5 = (c & 0x20) != 0;
			bits.b6 = (c & 0x40) != 0;
			bits.b7 = (c & 0x80) != 0;
			bits2.b0 = (c2 & 0x01) != 0;
			bits2.b1 = (c2 & 0x02) != 0;
			bits2.b2 = (c2 & 0x04) != 0;
			bits2.b3 = (c2 & 0x08) != 0;
			bits2.b4 = (c2 & 0x10) != 0;
			bits2.b5 = (c2 & 0x20) != 0;
			bits2.b6 = (c2 & 0x40) != 0;
			bits2.b7 = (c2 & 0x80) != 0;
			bits3.b0 = bits.b0 ^ bits2.b0;
			bits3.b1 = bits.b1 ^ bits2.b1;
			bits3.b2 = bits.b2 ^ bits2.b2;
			bits3.b3 = bits.b3 ^ bits2.b3;
			bits3.b4 = bits.b4 ^ bits2.b4;
			bits3.b5 = bits.b5 ^ bits2.b5;
			bits3.b6 = bits.b6 ^ bits2.b6;
			bits3.b7 = bits.b7 ^ bits2.b7;
			c3 = 0;
			c3 += boolInInt(bits3.b7);
			c3 *= 2;
			c3 += boolInInt(bits3.b6);
			c3 *= 2;
			c3 += boolInInt(bits3.b5);
			c3 *= 2;
			c3 += boolInInt(bits3.b4);
			c3 *= 2;
			c3 += boolInInt(bits3.b3);
			c3 *= 2;
			c3 += boolInInt(bits3.b2);
			c3 *= 2;
			c3 += boolInInt(bits3.b1);
			c3 *= 2;
			c3 += boolInInt(bits3.b0);
			putc(c3, xorF);
		}
	}
	fclose(mesF);
	fclose(keyF);
	fclose(xorF);
}

int main()
{
	printf("Verschlüsellung mit xor.\nProgrammversion \"v%s\".\n\n", version);
	printf("Eingabedateien:\n\tmes.txt\n\tkey.txt\nAusgabedatei:\n\txor.txt\n");
	return xorVerschlueseln();
}
