#include "stdafx.h"
#include "ParseParameters.h"
#include "Utils.h"

#include <iostream> 

CParseParameters::CParseParameters(int argc, char *argv[])
	: m_bEncode(true)
{
	for (int i = 1; i < argc; i++)
	{
		m_vTokens.push_back(Trim(std::string(argv[i])));
	}
}


CParseParameters::~CParseParameters()
{
}


int CParseParameters::Message_Help(void) const
{
	std::cout << "Replace all HTML text data with escape characters." << std::endl
		<< std::endl
		<< "EncodeHTML source [destination] [/?] [/h] [/d] [/e .htm,.xml,...]" << std::endl
		<< std::endl
		<< "source       Specifies the file or directory to be copied and encoded." << std::endl
		<< "destination  Specifies the directory and/or filename for the new file(s)." << std::endl
		<< "[/?] [/h]    Help." << std::endl
		<< "[/e]         Indicates a file extensions" << std::endl
		<< "[/d]         Decode" << std::endl
		;
	return 1;
}

int CParseParameters::Message_Incorrect(void) const
{
	std::cout << "The syntax of the command is incorrect." << std::endl;
	return 1;
}

int CParseParameters::Message_Extension(void) const
{
	std::cout << "Missing extensions." << std::endl;
	return 1;
}


const std::string& CParseParameters::GetOption(const std::string &strOptions) const
{
	std::vector<std::string>::const_iterator itr = std::find(m_vTokens.begin(), m_vTokens.end(), strOptions);
	if (itr != m_vTokens.end() && ++itr != m_vTokens.end())
	{
		return *itr;
	}

	static const std::string strEmpty("");
	return strEmpty;
}

bool CParseParameters::OptionExists(const std::string &strOptions) const
{
	return std::find(m_vTokens.begin(), m_vTokens.end(), strOptions) != m_vTokens.end();
}

int CParseParameters::Validate(void)
{
	int nParamsCount(0);

	if (OptionExists("/?") || OptionExists("/h") || OptionExists("-h"))
	{
		return Message_Help();
	}

	if (OptionExists("/e"))
	{
		std::string ext(GetOption("/e"));
		if (ext.empty())
		{
			Message_Incorrect();
			return Message_Extension();
		}
		else
		{ // parse extensions
			m_vExtensions = Split(ext, ",");
		}

		if (m_vTokens.size() == 1) // exist only extensions?
		{
			return Message_Incorrect();
		}
		nParamsCount += 2;
	}

	if (OptionExists("/d"))
	{
		m_bEncode = false;
		nParamsCount += 1;
	}

	switch (m_vTokens.size() - nParamsCount)
	{
	case 0:
		return Message_Incorrect();
	case 1: // only source, destination will be same place
		m_strSource = m_strDestination = m_vTokens[0];
		break;
	case 2:
		m_strSource = m_vTokens[0];
		m_strDestination = m_vTokens[1];
		break;
	default:
		return Message_Incorrect();
	}

	return 0;
}

std::string CParseParameters::GetSource() const
{
	return m_strSource;
}

std::string CParseParameters::GetDestination() const
{
	return m_strDestination;
}

std::vector <std::string> CParseParameters::GetExtensions() const
{
	return m_vExtensions;
}

bool CParseParameters::GetEncode() const
{
	return m_bEncode;
}
