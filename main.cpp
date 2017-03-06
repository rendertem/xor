#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char version[8] = "1.0.1.0";

char parameterHelp[7] = "--help";
char parameterNoLang[10] = "--no-lang";

int lang = 1; // 0=German 1=English

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

int strcmp(char *s1, char *s2)
{
	int i = 0;
	for(; *(s1 + i) != '\0'; i++)
	{
		if(*(s1 + i) != *(s2 + i))
		{
			return 1;
		}
	}
	if(*(s1 + i) != *(s2 + i))
	{
		return 1;
	}
	return 0;
}

void setLang()
{
	printf("1) Sollte ihre Sprache Deutsch sein tippen Sie 1.\n");
	printf("2) Is your speak english type 2.\n");
	int c = getchar();
	getchar();
	if(c == '1')
	{
		lang = 0;
	}
	else if(c == '2')
	{
		lang = 1;
	}
	else
	{
		printf("\"%c\" ist keine Verfügbare Sprache.\n", c);
		printf("\"%c\" is an not avaibal speak.\n", c);
	}
}

void help()
{
	if(lang == 0)
	{
		printf("Eingabedateien:\n\tmes.txt\n\tkey.txt\nAusgabedatei:\n\txor.txt\n");
	}
	else
	{
		printf("Inputfiles:\n\tmes.txt\n\tkey.txt\nOutputfiles:\n\txor.txt\n");
	}
}

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
		if(lang == 0)
		{
			fprintf(stderr, "Fehler: \"mes.txt\" ist nicht vorhanden.\n");
		}
		else
		{
			fprintf(stderr, "Error: \"mes.txt\" not exist.\n");
		}
		dateiFehler = true;
	}
	if(keyF == NULL)
	{
		if(lang == 0)
		{
			fprintf(stderr, "Fehler: \"key.txt\" ist nicht vorhanden.\n");
		}
		else
		{
			fprintf(stderr, "Error: \"key.txt\" not exist.\n");
		}
		dateiFehler = true;
	}
	if(xorF == NULL)
	{
		if(lang == 0)
		{
			fprintf(stderr, "Fehler: \"xor.txt\" ist nicht vorhanden.\n");
		}
		else
		{
			fprintf(stderr, "Error: \"xor.txt\" not exist.\n");
		}
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
				if(lang == 0)
				{
					fprintf(stderr, "Fehler: \"key.txt\" ist kürzer als \"mes.txt\".\n");
				}
				else
				{
					fprintf(stderr, "Error: \"key.txt\" is shorter as \"mes.txt\".\n");
				}
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

void printVersion()
{
	if(lang == 0)
	{
		printf("Verschlüsellung mit xor.\nProgrammversion \"v%s\".\n\n", version);
	}
	else
	{
		printf("Encoding with xor.\nProgram version \"v%s\".\n\n", version);
	}
}

int main(int argc, char *argv[])
{
	char langSet = 0;
	for(int i = 2; argc >= i; i++)
	{
		if(strcmp(argv[i - 1], parameterHelp) == 0)
		{
			printVersion();
			help();
			return 0;
		}
		if(strcmp(argv[i - 1], parameterNoLang) == 0)
		{
			langSet = 1;
		}
	}
	if(langSet == 0)
	{
		setLang();
	}
	printVersion();
	return xorVerschlueseln();
}
