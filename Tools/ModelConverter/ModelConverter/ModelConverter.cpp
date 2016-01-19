// ModelConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObjModelLoader.h"

using namespace Graphics;

void main()
{
	string strObjFile;
	cout<<"Enter obj file path : ";
	cin>>strObjFile;

	string strOutputFile;
	cout<<"Enter output file name (w/o extn) : ";
	cin>>strOutputFile;

	cObjModelLoader obj;

	obj.ConvertObjFile(strObjFile, strOutputFile + ".spdo");
	system("pause");
}

