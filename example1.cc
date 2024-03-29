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

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binInfile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

  if(!binInfile) {
    cout << "Cannot open the bin file." << endl;
    return 1;
  }

  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

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
  setCDKMatrixCell(myMatrix, 1, 1, "Magic: ");
  setCDKMatrixCell(myMatrix, 2, 2, "Test12344  22 Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
  }
