//Cory Cothrum
//10/11/2017
//Caesar Cipher; take a phrase and a shift value from user shift each letter by shift, 
//decode the opposite (negative) way.


//too complex, redo


//*****************************(NON-AVG)*SCREEN*WIDTH************************************

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

string shiftOperation(string, int, char);
int main() 
{
	//declare variables
	string message, secretMessage;			//before and after message strings
	int shiftValue;
	char keepGoing, modeSelect;				//menu selects

	cout <<"Caesar Cipher\n\nThis"
		 << "program takes a phrase you wish to encipher/decipher,\nand applies the "
		 << "Caesar Shift to it. Used extensively by\nJulius Caesar, this cipher simply "
		 << "takes a value (Julius used 3!) and\nmoves up the alphabet for each letter"
		 << "in the phrase.\nTo deciper, just move down.";
	do
	{
		//ask for inputs
		do
		{
			cout << "\n\nWould you like to Encipher or Decipher?\nPlease enter 'E' or 'D',"
				 << " then press Enter:\n";
			cin.get(modeSelect);
			cin.ignore(); //clear buffer
		//input validation
		} while ((modeSelect != 'E' && modeSelect != 'e') && (modeSelect != 'D' && modeSelect != 'd'));
		cout << "\nEnter the message:\n";
		getline(cin, message);
		cout << "Please enter the shift value (1-25):\n";
		cin >> shiftValue;

		//pass to function
		secretMessage = shiftOperation(message, (shiftValue % 26), modeSelect); // the % 26 is cheap input val on shiftvalue

		//output and ask if user would like to decode/encode again.
		cout << "\n============================================\nThe message encrypts to '" 
			 << secretMessage + "' when applying the shift value of " << shiftValue << "." << endl;
		cout << "Would you like to use this program again? (Y/N):\n";
		cin >> keepGoing;
	} while (keepGoing == 'y' || keepGoing == 'Y');
	cout << "\nGoodbye!";
}

string shiftOperation(string plainText, int shiftVal, char mode)
{
	const int ALPHABET_LENGTH = 26, PUNC_A_LENGTH = 15, PUNC_B_LENGTH = 7,
			  PUNC_C_LENGTH = 6, PUNC_D_LENGTH = 4, NUMBER_LENGTH = 10,
			  SPACE = 32;			//used for wraparound

	int messageLength = plainText.length();
	string shiftedText;

	//decide if encrypting or decrypting
	if (mode == 'd' || mode == 'D')		 //decrypt shift the 'opposite' way, negate value
	{
		shiftVal *= -1;
	} //broken, doesnt properly shift

	//perform operation
	//for letter in string, grab letter at position, apply shift value [wrap if over limit]

	//Just to be funny, apply the shift to all categories of ASCII value, correctly. 
	//As in no spill over between categories.
	for (int pos = 0; pos <= (messageLength - 1); pos++) //properly iterates over message
	{
		/*diagnostic - print out current ascii
		charVal = plainText[pos];
		cout << charVal << endl;
		*/
		if ((plainText[pos] <= 32) || (plainText[pos] == 127))
		{ //these are ASCII Commands, or space, skip these/do nothing - just in case
			shiftedText += plainText[pos];
		}
		else if ((plainText[pos] >= 33) && (plainText[pos] <= 47))
		{ //Punctuation A - ! " # $ % & ' ( ) * + , - . /
			//add shift to value, if above limit, subtract const, else just add shift - do for all
			shiftedText += ((plainText[pos] + shiftVal) > 47 ? (plainText[pos] + shiftVal%PUNC_A_LENGTH) - PUNC_A_LENGTH 
							: plainText[pos] + shiftVal%PUNC_A_LENGTH);
		}
		else if ((plainText[pos] >= 48) && (plainText[pos] <= 57))
		{ //Numbers - 0 1 2 3 4 5 6 7 8 9
			shiftedText += ((plainText[pos] + shiftVal) > 57 ? (plainText[pos] + shiftVal%NUMBER_LENGTH) - NUMBER_LENGTH 
							: plainText[pos] + shiftVal%NUMBER_LENGTH);
		}
		else if ((plainText[pos] >= 58) && (plainText[pos] <= 64))
		{ //Punctuation B - : ; < = > ? @
			shiftedText += ((plainText[pos] + shiftVal) > 64 ? (plainText[pos] + shiftVal%PUNC_B_LENGTH) - PUNC_B_LENGTH 
							: plainText[pos] + shiftVal%PUNC_B_LENGTH);
		}
		else if ((plainText[pos] >= 65) && (plainText[pos] <= 90))
		{ //Uppercase Alphabet - A B C D E F G H I J K L M N O P Q R S T U V W X Y Z			
			shiftedText += ((plainText[pos] + shiftVal) > 90 ? (plainText[pos] + shiftVal) - ALPHABET_LENGTH 
							: plainText[pos] + shiftVal);
		}
		else if ((plainText[pos] >= 91) && (plainText[pos] <= 96))
		{ //Punctuation C - [ \ ] ^ _ `
			shiftedText += ((plainText[pos] + shiftVal) > 96 ? (plainText[pos] + shiftVal%PUNC_C_LENGTH) - PUNC_C_LENGTH 
							: plainText[pos] + shiftVal%PUNC_C_LENGTH);
		}
		else if ((plainText[pos] >= 97) && (plainText[pos] <= 122))
		{ //Lowercase Alphabet - a b c d e f g h i j k l m n o p q r s t u v w x y z
			shiftedText += ((plainText[pos] + shiftVal) > 122 ? (plainText[pos] + shiftVal) - ALPHABET_LENGTH 
							: plainText[pos] + shiftVal);
		}
		else if ((plainText[pos] >= 123) && (plainText[pos] <= 126))
		{ //Punctuation D - { | } ~
			shiftedText += ((plainText[pos] + shiftVal) > 126 ? (plainText[pos] + shiftVal%PUNC_D_LENGTH) - PUNC_D_LENGTH 
							: plainText[pos] + shiftVal%PUNC_D_LENGTH);
		}
		else
		{//Bad Input 
			cout << "Bad input! (How?)";
		}
	}
	//return message
	return shiftedText;
}