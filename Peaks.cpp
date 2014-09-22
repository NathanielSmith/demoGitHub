/*
 * Peaks.cpp
 * Program to solve 1D and 2D peak finding problems
 *  Created on: Sep 15, 2014
 *      Author: Nathaniel D. Smith
 *      Class: CS 433
 */

#include <iostream>  //  Used for standard input and output
#include <math.h>  //  Used for round, ceil, floor, and trunc functions
#include <ctime>  //  Used to generate a random seed for a RNG
#include <cstdlib>  //  Used for the random function
#include <time.h>  //  Used for clock_t, clock, CLOCKS_PER_SEC
#include <stdio.h>  //  Used for prinf
#include <Windows.h>  //  Used for sleep function in WINDOWS
//#include <unistd.h>  //  Used for sleep function in LINUX

//unsigned int sleep(unsigned int seconds);  //  Used for sleep function in LINUX


using namespace std;

const long LENGTH = 250;  //  1048576 = 2^20

class Peak {
private:
	//  These are the arrays to be used for the fast peak finding
	int array1[LENGTH];
	int array2[LENGTH][LENGTH];

	//  These are the arrays to be used for the worst case scenario peak finding through linear search
	int array1B[LENGTH];
	int array2B[LENGTH][LENGTH];

public:
	Peak();  //  constructor
	void find1dPeak(int, int);
	void find2dPeak(int, int, int, int);
	int find2dPeak(int, int, int);  //  Used to find the global max in a row/column
	void find1dPeakB();  //  worst case scenario
	void find2dPeakB();  //  worst case scenario
	void display();
};  //  end Peak()

int main() {
	//  declare the random seed for the RNG
	srand(time(NULL));

	//  Create the object
	Peak p;

	//  Display all 4 arrays created
	p.display();

	//  find the peak for the random 1d array
	clock_t a;
	a = clock();
	cout << "Fast 1D peak: \n";
	for (int i = 0; i < 100000; i++) {
		p.find1dPeak(0, LENGTH - 1);
	}
	a = clock() - a;
	printf("It took me %d clicks (%f seconds) \n", a, ((float)a)/CLOCKS_PER_SEC);

	//  find the peak for the random 2d array
	clock_t b;
	b = clock();
	cout << "Fast 2D peak: \n";
	for (int i = 0; i < 100000; i++) {
		p.find2dPeak(0, 0, LENGTH - 1, LENGTH - 1);
	}
	b = clock() - b;
	printf("It took me %d clicks (%f seconds) \n", b, ((float)b)/CLOCKS_PER_SEC);

	//  find the peak for the linear searched 1d array (worst case scenario)
	clock_t c;
	c = clock();
	cout << "Worst case 1D peak: \n";
	for (int i = 0; i < 100000; i++) {
		p.find1dPeakB();
	}
	c = clock() - c;
	printf("It took me %d clicks (%f seconds) \n", c, ((float)c)/CLOCKS_PER_SEC);

	//  find the peak for the linear searched 2d array (worst case scenario)
	clock_t d;
	d = clock();
	cout << "Worst case 2D peak: \n";
	for (int i = 0; i < 100000; i++) {
		p.find2dPeakB();
	}
	d = clock() - d;
	printf("It took me %d clicks (%f seconds) \n", d, ((float)d)/CLOCKS_PER_SEC);

	//  return 0 to ensure proper exit of the program
	return 0;
}  //  end main()

/* 	Used for testing when program would infinitely recurse  */
void WINAPI Sleep( DWORD dwMilliseconds );  //  Used for the Sleep function in WINDOWS

void Peak :: find1dPeak(int bottom, int top){
	//  Find the middle of the array given
	int middle = floor((top + bottom) / 2);

/*	Used for testing when program would infinitely recurse
	Sleep(2000);  */

	if ((middle - 1) < 0) {
		if (array1[middle + 1] >= array1[middle]) {
			//cout << "Condition: middle - 1 < 0 & right >= middle (" << middle - 1 << "<0" << '&' << array1[middle + 1] << ">=" << array1[middle] << ')'<< endl;
//			cout << "Peak was found at index: " << middle << " with value: " << array1[middle] << "\n\n";
			return;
		}  //  end if (right >= middle)
		else {
			//cout << "Condition: middle - 1 < bottom & right < middle (" << middle - 1 << '<' << bottom << '&' << array1[middle + 1] << '<' << array1[middle] << ')' << endl;
//			cout << "Peak was found at index: " << middle << " with value: " << array1[middle] << "\n\n";
			return;
		}  //  end else (right < middle)
	}  //  end if (middle - 1 > 0)
	else if ((middle + 1) > (LENGTH - 1)) {
		if (array1[middle - 1] >= array1[middle]) {
			//cout << "Condition: middle + 1 > LENGTH - 1 & left >= middle (" << middle + 1 << '>' << LENGTH - 1 << '&' << array1[middle + 1] << ">=" << array1[middle] << ')' << endl;
			find1dPeak(bottom, middle - 1);
		}  //  end if (left >= middle)
		else {
			//cout << "Condition: middle + 1 < LENGTH - 1 & left < middle (" << middle + 1 << '<' << LENGTH - 1 << '&' << array1[middle - 1] << '<' << array1[middle]  << ')'<< endl;
//			cout << "Peak was found at index: " << middle << " with value: " << array1[middle] << "\n\n";
			return;
		}  //  end else (left < middle)
	}  //  end else if (right > LENGHT - 1)
	else if (array1[middle - 1] >= array1[middle]) {
		find1dPeak(bottom, middle - 1);
	}  //  end else if (left >= middle)
	else if (array1[middle + 1] >= array1[middle]) {
		find1dPeak(middle + 1, top);
	}  //  end else if (right >= middle)
	else {
//		cout << "Peak was found at index: " << middle << " with value: " << array1[middle] << "\n\n";
		return;
	}  //  end else (middle > right & middle > left)
}

//  Worst case scenario 1D peak finder (peak is at the last element of the array searching for it linearly
void Peak :: find1dPeakB() {
	//  Search linearly for a peak comparing each i to i - 1 & i + 1 as you go until you reach the end of the array
	for (int i = 0; i < LENGTH; i++) {
/*		//  Display all values used during execution for testing purposes
		cout << "array1B[i - 1]: " << array1B[i - 1]
		     << "  array1B[i ]: " << array1B[i]
		     << "  array1B[i + 1]: " << array1B[i + 1]
		     << "\n";  */
		if (i == 0) {
			if (array1B[i] >= array1B[i + 1]) {
//				cout << "A Peak was found at index: " << i << " with value: " << array1B[i] << "\n\n\n";
			}  //  end if (i >= i + 1)
		}  //  end else if (i == 0)
		else if (i == (LENGTH - 1)) {
			if (array1B[i] >= array1B[i - 1]) {
//				cout << "A Peak was found at index: " << i << " with value: " << array1B[i] << "\n\n\n";
			}  //  end if (i >= i - 1)
		}  //  end else if (LENGTH - 1)
		else if ((array1B[i] >= array1B[i + 1]) && (array1B[i] >= array1B[i - 1])) {
//			cout << "A Peak was found at index: " << i << " with value: " << array1B[i] << "\n\n\n";
		}  //  end if (i >= i + 1 && i >= i - 1)
	}  //  end for(i)
}  //  end find1dPeakB()

void Peak :: find2dPeak(int bottomX, int bottomY, int topX, int topY) {
	//  Declare variables
	int middleY = floor((topY + bottomY) / 2);
	int middleX = find2dPeak(bottomX, topX, middleY);
//	Sleep(2000);  //  Sleeps for 2000 milliseconds (2 seconds) in WINDOWS
//	sleep(2);  //  Sleeps for 2 seconds in LINUX

	if ((middleY - 1) < 0) {
			if (array2[middleX][middleY + 1] >= array2[middleX][middleY]) {
				//cout << "Condition: middleY - 1 < 0 & right >= middleY (" << middleY - 1 << "<0&" << array2[middleX][middleY + 1] << ">=" << array2[middleX][middleY] << ')'<< endl;
//				cout << "Peak was found at index: (" << middleX << ',' << middleY + 1 << ") with value: " << array2[middleX][middleY + 1] << "\n\n";
				return;
			}  //  end if (right >= middle)
			else {
				//cout << "Condition: middleY - 1 < bottom & right < middleY (" << middleY - 1 << "<0&" << array2[middleX][middleY + 1] << '<' << array2[middleX][middleY] << ')' << endl;
//				cout << "Peak was found at index: (" << middleX << ',' << middleY << ") with value: " << array2[middleX][middleY] << "\n\n";
				return;
			}  //  end else (right < middle)
		}  //  end if (middle - 1 > 0)
		else if ((middleY + 1) > (LENGTH - 1)) {
			if (array2[middleX][middleY - 1] >= array2[middleX][middleY]) {
				//cout << "Condition: middleY + 1 > LENGTH - 1 & left >= middleY (" << middleY + 1 << '>' << LENGTH - 1 << '&' << array2[middleX][middleY + 1] << ">=" << array2[middleX][middleY] << ')' << endl;
				find2dPeak(bottomX, bottomY, topX, middleY - 1);  //  find2dPeak(int bottom, int top,
			}  //  end if (left >= middle)
			else {
				//cout << "Condition: middleY + 1 < LENGTH - 1 & left < middleY (" << middleY + 1 << '<' << LENGTH - 1 << '&' << array2[middleX][middleY - 1] << '<' << array2[middleX][middleY]  << ')'<< endl;
//				cout << "Peak was found at index: (" << middleX << ',' << middleY << ") with value: " << array2[middleX][middleY] << "\n\n";
				return;
			}  //  end else (left < middle)
		}  //  end else if (right > LENGHT - 1)
		else if (array2[middleX][middleY - 1] >= array2[middleX][middleY]) {
			find2dPeak(bottomX, bottomY, topX, middleY - 1);  //  find2dPeak(int bottom, int top,
		}  //  end else if (left >= middle)
		else if (array2[middleX][middleY + 1] >= array2[middleX][middleY]) {
			find2dPeak(bottomX, middleY + 1, topX, topY);  //  find2dPeak(int bottom, int top,
		}  //  end else if (right >= middle)
		else {
//			cout << "Peak was found at index: (" << middleX << ',' << middleY << ") with value: " << array2[middleX][middleY] << "\n\n";
			return;
		}  //  end else (middle > right & middle > left)
}

//  This function finds the max of the row given to find the peak in the fast 2d array
int Peak :: find2dPeak(int bottom, int top, int middleY) {
	//  Find the middle of the array given
	int middleX = floor((top + bottom) / 2);

/*	Used for testing when program would infinitely recurse
	Sleep(2000);  */

	if ((middleX - 1) < 0) {
		if (array2[middleX + 1][middleY] >= array2[middleX][middleY]) {
/*			cout << "Condition: middle - 1 < 0 & right >= middle (" << middleX - 1 << "<0" << '&' << array2[middleX + 1][middleY] << ">=" << array2[middleX][middleY] << ')'<< endl;
			cout << "Peak was found at index: " << middleX + 1 << " with value: " << array2[middleX + 1] << endl;  */
			return middleX + 1;
		}  //  end if (right >= middle)
		else {
/*			cout << "Condition: middle - 1 < bottom & right < middle (" << middleX - 1 << '<' << bottom << '&' << array2[middleX + 1][middleY] << '<' << array2[middleX][middleY] << ')' << endl;
			cout << "Peak was found at index: " << middleX << " with value: " << array2[middleX][middleY] << endl; */
			return middleX;
		}  //  end else (right < middle)
	}  //  end if (middle - 1 > 0)
	else if ((middleX + 1) > (LENGTH - 1)) {
		if (array2[middleX - 1][middleY] >= array2[middleX][middleY]) {
/*			cout << "Condition: middle + 1 > LENGTH - 1 & left >= middle (" << middleX + 1 << '>' << LENGTH - 1 << '&' << array2[middleX + 1][middleY] << ">=" << array2[middleX][middleY] << ')' << endl;  */
			find2dPeak(bottom, middleX - 1, middleY);
		}  //  end if (left >= middle)
		else {
/*			cout << "Condition: middle + 1 < LENGTH - 1 & left < middle (" << middleX + 1 << '<' << LENGTH - 1 << '&' << array2[middleX - 1][middleY] << '<' << array2[middleX][middleY]  << ')'<< endl;
			cout << "Peak was found at index: " << middleX << " with value: " << array2[middleX][middleY] << endl;  */
			return middleX;
		}  //  end else (left < middle)
	}  //  end else if (right > LENGHT - 1)
	else if (array2[middleX - 1][middleY] >= array2[middleX][middleY]) {
		find2dPeak(bottom, middleX - 1, middleY);
	}  //  end else if (left >= middle)
	else if (array2[middleX + 1][middleY] >= array2[middleX][middleY]) {
		find2dPeak(middleX + 1, top, middleY);
	}  //  end else if (right >= middle)
	else {
/*		cout << "Peak was found at index: " << middleX << " with value: " << array2[middleX][middleY] << endl;  */
		return middleX;
	}  //  end else (middle > right & middle > left)
}

//  Worst case scenario 2D peak finder (peak is at the last element of the array searching for it linearly
void Peak :: find2dPeakB(){
	//  Search linearly for a peak comparing i to i - 1 & i + 1 and j to j - 1 & j + 1 as you go until you reach the end of the array
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (i == 0) {
				if (j == 0) {
					if ((array2B[i][j] >= array2B[i + 1][j]) && (array2B[i][j] >= array2B[i][j + 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}  //  end if (ij >= right and bottom)
				}  //  end if (j == 0)
				else if (j == (LENGTH - 1)) {
					if ((array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j - 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}  //  end if (ij >= left and bottom)
				}  //  end if (j == LENGTH - 1)
				else {
					if ((array2B[i][j] >= array2B[i + 1][j]) && (array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j - 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}//  end if (ij >= left right and bottom)
				}  //  end else if (ij != 0 && j != LENGTH - 1)
			}  //  end if (i == 0)
			else if (i == (LENGTH - 1)) {
				if (j == 0) {
					if ((array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j + 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}  //  end if (ij >= right and top)
				}  //  end if (j == 0)
				else if (j == (LENGTH - 1)) {
					if ((array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j - 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}  //  end if (ij >= left and top)
				}  //  end if (j == LENGTH - 1)
				else {
					if ((array2B[i][j] >= array2B[i + 1][j]) && (array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j + 1])) {
//						cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
						return;
					}  //  end if (ij >= right left and top)
				}  //  end else if (j != 0 && j != LENGTH - 1)
			}  //  end if (i == LENGTH - 1)
			else if ((array2B[i][j] >= array2B[i + 1][j]) && (array2B[i][j] >= array2B[i - 1][j]) && (array2B[i][j] >= array2B[i][j + 1]) && (array2B[i][j] >= array2B[i][j - 1])) {
//				cout << "A Peak was found at index: (" << i << ", " << j << ") with value: " << array2B[i][j] << "\n\n";
				return;
			}  //  if (ij >= top bottom left and right)
		}  //  end for (j)
	}  //  end for(i)
}  //  end find2dPeakB()

//  Constructor to initialize arrays
Peak :: Peak() {
	//  Fill the arrays for the fast peak finding with random numbers from 10 to 99
	//  Fill the arrays for the worst case scenario peak finding with numbers from 10 to the limit
	for (int i = 0; i < LENGTH; i++) {
		array1[i] = 10 + (rand() % 90);
		array1B[i] = i + 10;
		for (int j = 0; j < LENGTH; j++) {
			array2[i][j] = 10 + (rand() % 90);
			array2B[i][j] = i + j;
		}  //  end for(j)
	}  //  end for(i)
}  //  end peak() constructor

//  This function displays all arrays
void Peak :: display() {
	for (int i = 0; i < LENGTH; i++) {
		cout << array1[i] << ' ';
	}
	cout << "\n\n\n";

	for (int i = 0; i < LENGTH; i++) {
		cout << array1B[i] << ' ';
	}
	cout << "\n\n\n";

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			cout << array2[i][j] << ' ';
		}
		cout << "\n";
	}
	cout << "\n\n";

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			cout << array2B[i][j] << ' ';
		}
		cout << "\n";
	}
	cout << "\n\n";
}
