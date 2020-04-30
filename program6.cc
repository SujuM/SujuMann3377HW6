/* 
 * Filename	program6.cc
 * Date		2020/04/27
 * Author	Suju Mann
 * Email	skm180005@utdallas.edu
 * Course	CS 3377.501 Spring 2020
 * Version	1.0
 * Copyright	2020, All Rights Reserved
 *
 * Description
 * 	This program reads the supplied binary file and display the results in a CDK window.
 * */

#include <iostream>
#include <fstream>
#include <inttypes.h> 	//For the fixed width types like uint32_t
#include <string.h> 	//strcpy(), strcat().
#include "displayMatrix.h"
#include "binfile.h"

using namespace std;

int main()
{
//Those are the buffers to process strings when we display the contents on the Matrix.
  char buffer32[32];
  char buffer64[64];
  char mystr[128];
  string bfcontents[11];

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  
  ifstream binInfile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

//Error checking to see the binary file is openable.
  if(!binInfile) {
    cout << "Cannot open the bin file." << endl;
    return 1;
  }

  //Read the header of the binary file.
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  //Process the header record contents to display on the matrix
  snprintf(buffer32, sizeof(buffer32), "%" PRIx32, myHeader->magicNumber);
  strcpy (mystr, "Magic: 0x");
  strcat (mystr, buffer32);
  //Set the cell with processed string.
  bfcontents[0] = mystr;

  snprintf(buffer32, sizeof(buffer32), "%" PRIu32, myHeader->versionNumber);
  strcpy (mystr, "Version: ");
  strcat (mystr, buffer32);
  bfcontents[1] = mystr;
  
  snprintf(buffer64, sizeof(buffer64), "%" PRIu64, myHeader->numRecords);
  strcpy (mystr, "NumRecords: ");
  strcat (mystr, buffer64);  
  bfcontents[2] = mystr;
  
  //Disply up to the first 4 records in the CDK Matrix
  for (int i = 0; i < 4; i++) {
  //Read the record of the binary file contents.
  	binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
  //Process the record contents to display on the matrix
 	snprintf(buffer32, sizeof(buffer32), "%" PRIu8, myRecord->strLength);
  	strcpy (mystr, "strlen: ");
  	strcat (mystr, buffer32);
  //Set the cell with processed string.
 	bfcontents[i + 3] = mystr;
 	
	snprintf(buffer32, sizeof(buffer32), "%s", myRecord->stringBuffer);
  	strcpy (mystr, "strlen: ");
  	strcat (mystr, buffer32);
	
	bfcontents[i + 7] = mystr;
  }

//Close the binary file that we opened.
  binInfile.close();

  //Call displayMatrix to create a matrix and display the contents of the binary file on it.
  displayMatrix(bfcontents);

  return 0;
  }
