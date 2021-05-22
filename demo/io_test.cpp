#include<iostream>
#include<fstream>
#include<string>
#include <stdio.h>
#include <cmath>
using namespace std;

//not review 
bool ReadSpecify(const char *fPath, long fStart, long fNumber)
{
	FILE *srcFile;
	srcFile = fopen(fPath, "rb");
	if (NULL == srcFile)
	{
		printf("	Open file: %s failed.\n", fPath);
		return false;
	}
 
	unsigned long iSize;
	fseek(srcFile, 0,SEEK_END);
	iSize = ftell(srcFile);
	rewind(srcFile);
	if ((fNumber>iSize) || (labs(fStart)>iSize))
	{
		printf("	Parameter error.\n");
		return false;
	}
 
	printf("isize:%d start:%d num:%d\n", iSize, fStart, fNumber);
 
	if (fStart >= 0)		// read form file header
	{	
		char *buff = new char[fNumber+1];
		buff[fNumber] = '\0';
		fseek(srcFile, fStart, SEEK_SET);
		fread(buff, 1, fNumber, srcFile);
		printf("%s\n", buff);
		rewind(srcFile);
		delete[] buff;
	}
	else if ((fStart<0) && (labs(fStart) >= fNumber))		// read form file tail
	{
		char *buff = new char[fNumber+1];
		buff[fNumber] = '\0';
		fseek(srcFile, fStart, SEEK_END);
		fread(buff, 1, fNumber, srcFile);
		printf("%s\n", buff);
		rewind(srcFile);
		delete[] buff;
	}
	else
	{
		printf("	Parameter error.\n");
		return false;
	}
 
	fclose(srcFile);
	return true;
}
 
int main()
{
	string filePath="/var/log/system.log";

	ReadSpecify(filePath.c_str(), 0, 4);
	
 
	return 0;
}
