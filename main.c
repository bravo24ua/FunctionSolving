#include <stdio.h>

#define MAX_BASE  (26 * 2 + 10)  // 26 Letters can be used in small and capital form and 10 digits 0..9

unsigned int x[75] = { 
					15840, 16465, 17941, 17942, 18898, 19172, 20512, 20626, 20758, 25736,
					25893, 26039, 26134, 26345, 26346, 26676, 28161, 31622, 31873, 32028,
					35260, 36368, 36428, 38716, 38805, 40111, 40893, 40956, 40957, 40958,
					40959, 40960, 42541, 47987, 49137, 49169, 49443, 49444, 49639, 50047,
					50048, 50127, 50128, 50129, 51183, 51184, 51204, 52071, 52977, 54650,
					55908, 56100, 57924, 60538, 60539, 60540, 61474, 63141, 64436, 64437,
					67416, 72677, 73039, 73040, 73211, 73654, 73756, 74037, 74038, 76081,
					76082, 79467, 79564, 79790, 79791 
					};
char y[75][3] = {	"cGp",	"cmW",	"cX3",	"cXB",	"ctR",	"ckN",	"PVg",	"PD4",	"PBR",	"MYM",	
					"MSL",	"MUk",	"MIE",	"Mgr",	"MgK",	"MKd",	"GVT",	"vNx",	"vwP",	"vV9",	
					"zAj",	"zO9",	"zu1",	"AcO",	"APF",	"AHl",	"ALW",	"AQ9",	"AQs",	"AQq",	
					"AQL",	"AQQ",	"Zcz",	"yuk",	"yh2",	"yIi",	"yau",	"yap",	"ytL",	"T7T",	
					"T7N",	"Tx8",	"TxE",	"Tx2",	"Tn2",	"Tn1",	"Tnf",	"T2a",	"Thu",	"NTO",	
					"N2e",	"N9g",	"ocd",	"oeH",	"oe0",	"oeO",	"okE",	"dH6",	"dUw",	"dUn",	
					"m2D",	"wtT",	"nCi",	"nCc",	"nxJ",	"nzb",	"nZq",	"ndz",	"ndA",	"nIG",	
					"nIv",	"VXS",	"VYw",	"VeK",	"Vel",
				};

int count_unique_characters(char ref[75][3]);
void rebase_decimal_number(unsigned int dec, unsigned int base, unsigned int* d1, unsigned int* d2, unsigned int* d3);

int main(void)
{
	unsigned int min_base;
	unsigned int valid_base = 0;
	unsigned int task_inputs[3] = { 30001, 55555, 77788 };
	char base_digits[MAX_BASE] = { 0 };

	unsigned int dig1 = 0, dig2 = 0, dig3 = 0;
	// This is to check our reference table for count of unique characters (digits) to define the minimal base (it can be the case that not all characters and figures are used)
	min_base = count_unique_characters(y);
	printf("Total unique characters: %u\n\n", min_base);

	for (int i = min_base; i <= MAX_BASE; i++)
	{
		printf("\nPossible base is: %u\n", i);
		for (int j = 0; j < 75; j++)
		{
			rebase_decimal_number(x[j], i, &dig1, &dig2, &dig3);
			printf("%02u). %u -> %c %c %c : %02u %02u %02u",j+1, x[j], y[j][0], y[j][1], y[j][2], dig3, dig2, dig1);
			// The fastest way to check if this number base is correct is to check if it's found digits decimal representations for this base are matching the same characters...
			// In spreadsheet we have 2 nice points of function with duplicated characters...
			// So we can start our check of selected base corectness by checking if digits for these duplicated characters are the same:
			// 40960	AQQ (Two "Q")   - rebase result in decimal digits representation should result digits like XXX YYY YYY
			// 50047	T7T (Two "T")   - rebase result in decimal digits representation should result digits like ZZZ AAA ZZZ
			if (40960 == x[j])
			{
				if (dig2 == dig1)
				{
					printf(" MATCHING to condition 1!!!\n");
					valid_base = i;
				}
					
				else
					printf(" NOT matching to condition 1!!!\n");
			}
			else if (50047 == x[j])
			{
				if (dig3 == dig1)
					printf(" MATCHING to condition 2!!!\n");
				else
					printf(" NOT matching to condition 2!!!\n");
			}
			else
				printf("\n");
		}
	}
	// Now we should find how our base figures are assigned to characters and figures
	// Let's scan (again) reference table and make this assignment
	for (int k = 0; k < 75; k++)
	{
		rebase_decimal_number(x[k], valid_base, &dig1, &dig2, &dig3);
		base_digits[dig1] = y[k][2];
		base_digits[dig2] = y[k][1];
		base_digits[dig3] = y[k][0];
	}
	// Let's print an result for reference
	for (int l = 0; l < valid_base; l++)
	{
		if (0 == base_digits[l])
		{
			base_digits[l] = '5';  // To fix the fact that 5 was never presented in reference table result column
		}
		printf("%02u = %c\n", l, base_digits[l]);
	}

	// And now we can provide an output for  provided inputs
	printf("\nFunction output for inputs from the task:\n");
	for (int m = 0; m < 3; m++)
	{
		rebase_decimal_number(task_inputs[m], valid_base, &dig1, &dig2, &dig3);
		printf("%u -> %c %c %c\n", task_inputs[m], base_digits[dig3], base_digits[dig2], base_digits[dig1]);
	}
	// The domain of function is limited by it's base we found during task solving:
	// Function domain is [0..(62^3)-1].
	printf("\nFunction domain is [0..%u] in decimal numbering system and its range is [%c%c%c..%c%c%c] in numbering system with base %u\n", 62*62*62 - 1, 
		base_digits[0], base_digits[0], base_digits[0], base_digits[valid_base - 1], base_digits[valid_base - 1],base_digits[valid_base -1], valid_base);
	printf("If function argument is more than %d, it will result overflow\n", 62 * 62 * 62 - 1);
	printf("****BUT this range can be extended if result can consist more than 3 digits (it's not clear from task if it can't)*****\n\n");
}

int count_unique_characters(char ref[75][3])
{
	int hash[128] = { 0 };
	int i,j, c = 0;

	// reading each character of ref[]
	for (i = 0; i < 75; ++i)
	{
		for (j = 0; j < 3; j++)
		{
			// set the position corresponding 
			// to the ASCII value of ref[i][j] in hash[] to 1
			hash[ref[i][j]] = 1;
		}
	}

	// counting number of unique characters
	// repeated elements are only counted once
	for (i = 0; i < 128; ++i)
	{
		c += hash[i];
		if ((hash[i] == 0)&&(((i>=48)&&(i<=57)) || ((i >= 65) && (i <= 90)) || ((i >= 97) && (i <= 122))))
		{
			printf("Attention, %c not used in reference table.\n", i);
			// Console output gives us an idea that "5" was not present in reference table result column
		}
	}

	return c;
}
// This function covers our task requirements. It's not universal but it does what it has to do in task conditions
void rebase_decimal_number(unsigned int dec, unsigned int base, unsigned int *d1, unsigned int *d2, unsigned int *d3)
{
	*d1 = dec % base;
	*d2 = (dec / base) % base;
	*d3 = (dec / base / base) % base;
}
