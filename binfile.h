/*
 * Filename:	binfile.h
 * Date:	04/29/2020
 * Author:	Suju Mann
 * Email:	skm180005@utdallas.edu
 * Course:	CS 3377.501 Spring 2020
 * version:	1.0
 * Copyright	2020, All rights reserved.
 *
 * Description
 * 	This is a header including class definitions.
 * */



class BinaryFileHeader
{
 public:

 uint32_t magicNumber;
 uint32_t versionNumber;
 uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:

 uint8_t strLength;
 char	 stringBuffer[maxRecordStringLength];
};
