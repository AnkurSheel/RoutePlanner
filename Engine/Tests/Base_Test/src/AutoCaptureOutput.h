//  *******************************************************************************************************************
//  AutoCaptureOutput   version:  1.0   Ankur Sheel  date: 2014/12/10
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __AUTOCAPTUREOUTPUT_H__
#define __AUTOCAPTUREOUTPUT_H__

struct AutoCaptureOutput
{	
	AutoCaptureOutput();

	~AutoCaptureOutput();

	std::string str();
	void reset();

	std::streambuf *old_buffer;
	std::stringstream ss;
};

#define CHECK_OUTPUT(text) \
	{ EXPECT_STREQ(std::string(text).data(), m_Output.str().data()); \
		m_Output.reset(); }

#endif  // __AUTOCAPTUREOUTPUT_H__

