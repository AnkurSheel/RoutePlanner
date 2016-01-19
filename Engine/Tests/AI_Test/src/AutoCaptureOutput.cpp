#include "stdafx.h"
#include "AutoCaptureOutput.h"

//  ********************************************************************************************************************
AutoCaptureOutput::AutoCaptureOutput()
{
	old_buffer = std::cout.rdbuf();
	std::cout.rdbuf(ss.rdbuf());
}

//  ********************************************************************************************************************
AutoCaptureOutput::~AutoCaptureOutput()
{
	std::cout.rdbuf(old_buffer);
	old_buffer = NULL;
}

//  ********************************************************************************************************************
std::string AutoCaptureOutput::str()
{
	return ss.rdbuf()->str();
}

//  ********************************************************************************************************************
void AutoCaptureOutput::reset()
{
	ss.rdbuf()->str("");
}
