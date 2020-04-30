/* 
 * Filename	displayMatrix.cc
 * Date		2020/04/29
 * Author	Suju Mann
 * Email	skm180005@utdallas.edu
 * Course	CS 3377.501 Spring 2020
 * Version	1.0
 * Copyright	2020, All Rights Reserved
 *
 * Description
 * 	This is a function to display the contents in a CDK window with the str array argument.
 * */

#include <iostream>
#include <string>
#include "displayMatrix.h"
#include "cdk.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20	//Make sure the width are wide enough.
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

void displayMatrix(string *contents)
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_WIDTH+1] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_HEIGHT+1] = {"C0", "a", "b", "c"};
  int			boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int			boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

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

  //Set the cell with the header of the binary file from the contents.
  setCDKMatrixCell(myMatrix, 1, 1, contents[0].c_str());
  setCDKMatrixCell(myMatrix, 1, 2, contents[1].c_str());
  setCDKMatrixCell(myMatrix, 1, 3, contents[2].c_str());
  
  //Set the cell with the records of the binary file up to the first 4 records.
  //contents[3] to contents[11]
  for (int i = 0; i < 4; i++) {
  //Set the cell with processed string.
  //	This is the contents for the first column of the matrix.
  	setCDKMatrixCell(myMatrix,i+2, 1, contents[i+3].c_str());
	//This is the contents for the second column of the matrix.
  	setCDKMatrixCell(myMatrix,i+2, 2, contents[i+7].c_str());
  }

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);
  
  getch(); //Wait for the user to types a character on the keyboard.
  // Cleanup screen
  endCDK();

  cout << "Done" << endl;

  };
