#include "stdafx.h"
#include "ParamLoader.h"
#include "FileIO.hxx"

using namespace Utilities;
using namespace Base;
using namespace std;

//  *******************************************************************************************************************
cParamLoader::cParamLoader()
: m_pFile(NULL)
{
}

//  *******************************************************************************************************************
cParamLoader::~cParamLoader()
{
	SafeDelete(&m_pFile);
	m_vCommandLineArguments.clear();
}

//  *******************************************************************************************************************
void cParamLoader::VLoadParametersFromFile(const cString & strFileName)
{
	m_pFile = IFileIO::CreateFileIO();
	if(m_pFile->VOpenFile(strFileName, std::ios_base::in))
	{
		m_Buffer = m_pFile->VReadLine();

		while(!m_pFile->VIsEOF() || !m_Buffer.IsEmpty())
		{
			ExtractParameters();
			m_Buffer = m_pFile->VReadLine();
		}
		m_pFile->VCloseFile();
	}
}

//  *******************************************************************************************************************
void cParamLoader::VLoadParametersFromBuffer(const cString & Buffer)
{
	const cString delims("\n");
	tOptional<int> begIndex = 0;
	tOptional<int> endIndex;

	while(true)
	{
		endIndex = Buffer.FindFirstOfAny(delims, begIndex.GetValue());
		if(endIndex.IsValid())
		{
			m_Buffer = Buffer.GetSubString(begIndex.GetValue(), endIndex.GetValue() - 1);
			begIndex = Buffer.FindFirstNotOfAny(delims, endIndex.GetValue());
			ExtractParameters();
		}
		else
		{
			break;
		}
	}
}

//  *******************************************************************************************************************
tOptional<int> cParamLoader::VGetParameterValueAsInt(const cString & strParameter) const
{
	tOptional<int> val;
	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = strVal.GetValue();
		val = str.ToInt();
	}
	return val;
}

//  *******************************************************************************************************************
int cParamLoader::VGetParameterValueAsInt(const cString & strParameter, const int iDefaultValue) const
{
	tOptional<int> val = VGetParameterValueAsInt(strParameter);
	if (val.IsInvalid())
	{
		return iDefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<float> cParamLoader::VGetParameterValueAsFloat(const cString & strParameter) const
{
	tOptional<float> val;
	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = strVal.GetValue();
		val = str.ToFloat();
	}
	return val;
}

//  *******************************************************************************************************************
float cParamLoader::VGetParameterValueAsFloat(const cString & strParameter, const float fDefaultValue) const
{
	tOptional<float> val = VGetParameterValueAsFloat(strParameter);
	if (val.IsInvalid())
	{
		return fDefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<bool> cParamLoader::VGetParameterValueAsBool(const cString & strParameter) const
{
	tOptional<bool> val;

	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = strVal.GetValue();
		val = str.ToBool();
	}
	return val;
}

//  *******************************************************************************************************************
bool cParamLoader::VGetParameterValueAsBool(const cString & strParameter, const bool bDefaultValue) const
{
	tOptional<bool> val = VGetParameterValueAsBool(strParameter);
	if (val.IsInvalid())
	{
		return bDefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
tOptional<cString> cParamLoader::VGetParameterValueAsString(const cString & strParameter) const
{
	tOptional<cString> val;
	for(auto iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter) == 0)
		{
			iter++;
			if(iter == m_vCommandLineArguments.end() || (*iter)[0] == '-')
			{
				SP_LOG_CUSTOM(AssertLevels::LEVEL_ERROR, 1, "Could not find parameter")(strParameter)(m_pFile->VGetFileName());
				val.clear();
				break;
			}
			val = *iter;
			break;

		}
	}
	return val;
}

//  *******************************************************************************************************************
cString cParamLoader::VGetParameterValueAsString(const cString & strParameter, const cString & strDefaultValue) const
{
	tOptional<cString> val = VGetParameterValueAsString(strParameter);
	if (val.IsInvalid())
	{
		return strDefaultValue;
	}
	return val.GetValue();
}

//  *******************************************************************************************************************
void cParamLoader::VGetParameterValueAsIntList(const cString & strParameter, vector<int> & vValue) const
{
	vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(vValueStr[i].ToInt().GetValue());
	}
}

//  *******************************************************************************************************************
void cParamLoader::VGetParameterValueAsFloatList(const cString & strParameter, vector<float> & vValue) const
{
	vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(vValueStr[i].ToFloat().GetValue());
	}
}

//  *******************************************************************************************************************
void cParamLoader::VGetParameterValueAsBoolList(const cString & strParameter, vector<bool> & vValue) const
{
	std::vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(vValueStr[i].ToBool().GetValue());
	}
}

//  *******************************************************************************************************************
void cParamLoader::VGetParameterValueAsStringList(const cString & strParameter, vector<cString> & vValue) const
{
	for(auto iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter) == 0)
		{
			iter++;
			if(iter == m_vCommandLineArguments.end() || (*iter)[0] == '-')
			{
				SP_LOG_CUSTOM(AssertLevels::LEVEL_ERROR, 1, "Could not find parameter")(strParameter)(m_pFile->VGetFileName());
				vValue.clear();
				break;
			}
			cString str = *iter;
			str.Tokenize(",", vValue);
			return;
		}
	}
}

//  *******************************************************************************************************************
bool cParamLoader::VIsParameter(const cString & strParameter) const
{
	for(auto iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter))
		{
			return true;
		}
	}
	return false;
}

//  *******************************************************************************************************************
tOptional<int> cParamLoader::GetNextParameterAsInt()
{ 
	GetNextParameter();
	tOptional<int> val =  m_Buffer.ToInt();
	return val;
}

//  *******************************************************************************************************************
tOptional<float> cParamLoader::GetNextParameterAsFloat()
{
	GetNextParameter();
	tOptional<float> val =  m_Buffer.ToFloat();
	return val;
}

//  *******************************************************************************************************************
tOptional<bool> cParamLoader::GetNextParameterAsBool()
{
	GetNextParameter();
	tOptional<bool> val =  m_Buffer.ToBool();
	return val;
}

//  *******************************************************************************************************************
void cParamLoader::GetNextParameter()
{
	do
	{
		m_Buffer = m_pFile->VReadLine();
	}
	while(m_Buffer.IsEmpty() && !m_pFile->VIsEOF());
	if(!m_Buffer.IsEmpty())
	{
		m_Buffer.TrimLeft();
		RemoveCommentsFromLine();
		m_Buffer.TrimBoth();
		if(m_Buffer.IsEmpty())
		{
			GetNextParameter();
			return;
		}
	}
	GetParameterValueAsString();
}

//  *******************************************************************************************************************
void cParamLoader::GetParameterValueAsString()
{
	const cString delims(" /;=,\t");
	tOptional<int> begIndex;
	tOptional<int> endIndex;

	begIndex = m_Buffer.FindFirstNotOfAny(delims, 0);
	if(begIndex.IsValid())
	{
		endIndex = m_Buffer.FindFirstOfAny(delims, begIndex.GetValue());
		if(endIndex.IsInvalid())
		{
			endIndex = m_Buffer.GetLength();
		}
	}

	begIndex = m_Buffer.FindFirstNotOfAny(delims, endIndex.GetValue());
	if(begIndex.IsValid())
	{
		endIndex = m_Buffer.FindFirstOfAny(delims, begIndex.GetValue());
		if(endIndex.IsInvalid())
		{
			endIndex = m_Buffer.GetLength();
		}
	}
	m_Buffer = m_Buffer.GetSubString(begIndex.GetValue(), endIndex.GetValue() - 1);
}

//  *******************************************************************************************************************
void cParamLoader::RemoveCommentsFromLine()
{
	const cString delims("/;");
	tOptional<int> index;
	index = m_Buffer.FindFirstOfAny(delims, 0);
	if(index.IsValid())
	{
		m_Buffer = m_Buffer.GetSubString(0, index.GetValue() - 1);
	}
}

//  *******************************************************************************************************************
void cParamLoader::ExtractParameters()
{
	if(!m_Buffer.IsEmpty())
	{
		const cString delims(" =\t");
		tOptional<int> begIndex;
		tOptional<int> endIndex;

		cString strParam1;
		cString strParam2;

		RemoveCommentsFromLine();
		m_Buffer.TrimBoth();
		if(!m_Buffer.IsEmpty())
		{
			if(m_Buffer[0] != '-')
			{
				m_Buffer.Insert(0, "-");
			}
			endIndex = m_Buffer.FindFirstOfAny(delims, 0);
			if(endIndex.IsInvalid())
			{
				m_vCommandLineArguments.push_back(m_Buffer);
			}
			else
			{
				strParam1 = m_Buffer.GetSubString(0, endIndex.GetValue() - 1);
				m_vCommandLineArguments.push_back(strParam1);

				begIndex = m_Buffer.FindFirstNotOfAny(delims, endIndex.GetValue());
				if(begIndex.IsValid())
				{
					strParam2 = m_Buffer.GetSubString(begIndex.GetValue(), m_Buffer.GetLength() - 1);
					m_vCommandLineArguments.push_back(strParam2);
				}
			}
		}
	}
}

//  *******************************************************************************************************************
IParamLoader * IParamLoader::CreateParamLoader()
{
	IParamLoader * pFile = DEBUG_NEW cParamLoader();
	return pFile;
}
