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
#include "cdk.h"
#include "binfile.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20	//Make sure the width are wide enough.
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_WIDTH+1] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_HEIGHT+1] = {"C0", "a", "b", "c"};
  int			boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int			boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

//Those are the buffers to process strings when we display the contents on the Matrix.
  char buffer32[32];
  char buffer64[64];
  char mystr[128];

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  
  ifstream binInfile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

//Error checking to see the binary file is openable.
  if(!binInfile) {
    cout << "Cannot open the bin file." << endl;
    return 1;
  }

  /*
   * Initialize the Cdk screen.
   * Make sure the putty terminal is large enough
   */

  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

//Error checking
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  //Read the header of the binary file.
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

  //Process the header record contents to display on the matrix
  snprintf(buffer32, sizeof(buffer32), "%" PRIx32, myHeader->magicNumber);
  strcpy (mystr, "Magic: 0x");
  strcat (mystr, buffer32);
  //Set the cell with processed string.
  setCDKMatrixCell(myMatrix, 1, 1, mystr);

  snprintf(buffer32, sizeof(buffer32), "%" PRIu32, myHeader->versionNumber);
  strcpy (mystr, "Version: ");
  strcat (mystr, buffer32);
  
  setCDKMatrixCell(myMatrix, 1, 2, mystr);
 
  snprintf(buffer64, sizeof(buffer64), "%" PRIu64, myHeader->numRecords);
  strcpy (mystr, "NumRecords: ");
  strcat (mystr, buffer64);  
  
  setCDKMatrixCell(myMatrix, 1, 3, mystr);
  
  //Disply up to the first 4 records in the CDK Matrix
  for (int i = 0; i < 4; i++) {
  //Read the record of the binary file contents.
  	binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
  //Process the record contents to display on the matrix
 	snprintf(buffer32, sizeof(buffer32), "%" PRIu8, myRecord->strLength);
  	strcpy (mystr, "strlen: ");
  	strcat (mystr, buffer32);
  //Set the cell with processed string.
  	setCDKMatrixCell(myMatrix,i+2, 1, mystr);
  	setCDKMatrixCell(myMatrix,i+2, 2, (char *) myRecord->stringBuffer);
  }


//Close the binary file that we opened.
  binInfile.close();

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);

  // Cleanup screen
  endCDK();
  }
