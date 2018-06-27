//written in Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>		//includes bool identifier, true, and false

#define numseats 200
#define seatsA 50
#define seatsB 50
#define seatsC 100
#define priceA 50
#define priceB 70
#define priceC 80
#define maxseats 100

int seats[numseats] = { 0 };
int secA = 0;
int secB = seatsA;
int secC = seatsA + seatsB;
int availableA = seatsA;
int availableB = seatsB;
int availableC = seatsC;

int askCount, newSection, askSection;

void askSeat();
bool Available(char section);
void updateSeats(char section);
void printTicket(char section);
bool customerFlexible(void);
char alternativeSection(char section);
bool theaterBooked(void);

int main()
{
	int customerHere = 1;

	while (customerHere)
	{
		askSeat();
		if (Available(askSection))
		{
			printTicket(askSection);
			updateSeats(askSection);
			if (theaterBooked())
			{
				printf("Theater is full. Press 0 to exit.\n");
				getchar();
				return 0;
			}
			else
			{
				char moreCustomer;
				printf("Would you like to order more tickets? (y/n)\n");
				scanf_s("%c", &moreCustomer);
				getchar();
				if (moreCustomer == 'y')
					customerHere = 1;
				else
					customerHere = 0;
			}
		}
		else if (alternativeSection(askSection) != askSection)
			if (customerFlexible())
			{
				printTicket(newSection);
				updateSeats(newSection);
				if (theaterBooked())
				{
					printf("Theater is full. Press 0 to exit.\n");
					getchar();
					return 0;
				}
				else
				{
					char moreCustomer;
					printf("Would you like to order more tickets? (y/n)\n");
					scanf_s("%c", &moreCustomer);
					getchar();
					if (moreCustomer == 'y')
						customerHere = 1;
					else
						customerHere = 0;
				}
			}
			else
			{
				char moreCustomer;
				printf("Sorry we are booked. Would you like to order more tickets? (y/n)\n");
				scanf_s("%c", &moreCustomer);
				getchar();
				if (moreCustomer == 'y')
					customerHere = 1;
				else
					customerHere = 0;
			}
	}
}
void askSeat(void)
{
	printf("Would you like to be seated in section A(1), B(2), or C(3)?\n");
	scanf_s("%d", &askSection);
	getchar();
	printf("How many seats would you like?\n");
	scanf_s("%d", &askCount);
	getchar();
}
bool Available(char section)
{
	int i, count = 0;
	if (section == 1)
	{
		for (i = 0; i < availableA; i++)
		{
			if (seats[i+secA] == 0)
				count++;
		}
		if (askCount <= count)
			return true;
		else
			return false;
	}
	if (section == 2)
	{
		for (i = 0; i < availableB; i++)
		{
			if (seats[i+secB] == 0)
				count++;
		}
		if (askCount <= count)
			return true;
		else
			return false;
	}
	if (section == 3)
	{
		for (i = 0; i < availableC; i++)
		{
			if (seats[i+secC] == 0)
				count++;
		}
		if (askCount <= count)
			return true;
		else
			return false;
	}
}
void updateSeats(char section)
{
	int i;
	if (section == 1)
	{
		for (i = 0; i < askCount; i++)
		{
			if (seats[i + secA] == 0)
			{
				seats[i + secA] = 1;
			}
		}
		secA = secA + askCount;
		availableA = availableA - askCount;
	}
	if (section == 2)
	{
		for (i = 0; i < askCount; i++)
		{
			if (seats[i + secB] == 0)
			{
				seats[i + secB] = 1;
			}
		}
		secB = secB + askCount;
		availableB = availableB - askCount;
	}
	if (section == 3)
	{
		for (i = 0; i < askCount; i++)
		{
			if (seats[i + secC] == 0)
			{
				seats[i + secC] = 1;
			}
		}
		secC = secC + askCount;
		availableC = availableC - askCount;
	}
}
void printTicket(char section)
{
	int i=0, price, first, last;
	char sect;
	if (section == 1)
	{
		price = priceA*askCount;
		for (i = 1; i <= availableA; i++)
		{
			if (seats[i + secA] == 0)
			{
				first = i + secA;
				break;
			}
		}
		last = secA + askCount;
		sect = 'A';
	}
	if (section == 2)
	{
		price = priceB*askCount;
		for (i = 1; i <= availableB; i++)
		{
			if (seats[i + secB] == 0)
			{
				first = i + secB;
				break;
			}
		}
		last = secB + askCount;
		sect = 'B';
	}
	if (section == 3)
	{
		price = priceC*askCount;
		for (i = 1; i <= availableC; i++)
		{
			if (seats[i + secC] == 0)
			{
				first = i + secC;
				break;
			}
		}
		last = secC + askCount;
		sect = 'C';
	}
	printf("You are in section %c, seats %d through %d.\n", sect, first, last);
	printf("Total cost is: %d\n", price);
}
bool customerFlexible(void)
{
	char isFlexible;
	printf("Sorry, this section is full. Would you like to be placed in another section? (y/n)\n");
	scanf_s("%c", &isFlexible);
	getchar();
	if (isFlexible == 'y')
		return true;
	else
		return false;
}
char alternativeSection(char section)
{
	int i, count = 0;
	while (1)
	{
		if (section != 1)
		{
			for (i = 0; i <= availableA; i++)
			{
				if (seats[i + secA] == 0)
					count++;
			}
			if (askCount <= count)
			{
				return newSection = 1;
				break;
			}
		}
		if (section != 2)
		{
			for (i = 0; i <= availableB; i++)
			{
				if (seats[i + secB] == 0)
					count++;
			}
			if (askCount <= count)
			{
				return newSection = 2;
				break;
			}
		}
		if (section != 3)
		{
			for (i = 0; i <= availableC; i++)
			{
				if (seats[i + secC] == 0)
					count++;
			}
			if (askCount <= count)
			{
				return newSection = 3;
				break;
			}
		}
	}
}
bool theaterBooked(void)
{
	int i, count = 0;
	for (i = 0; i < numseats; i++)
	{
		if (seats[i] == 1)
			count++;
	}
	if (count == 200)
		return true;
	else
		return false;

}