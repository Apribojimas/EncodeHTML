#pragma once

#include <iostream>
#include <vector>

class CParseParameters
{
	std::vector <std::string> m_vTokens;
	std::vector <std::string> m_vExtensions;
	std::string m_strSource;
	std::string m_strDestination;
	bool m_bEncode;
	bool m_bSub; //subdirectories

public:
	CParseParameters(int argc, char *argv[]);
	virtual ~CParseParameters();

	const std::string& GetOption(const std::string &strOptions) const;
	bool OptionExists(const std::string &strOptions) const;

	int Message_Help(void) const;
	int Message_Incorrect(void) const;
	int Message_Extension(void) const;

	int Validate(void);

	std::string GetSource() const;
	std::string GetDestination() const;
	std::vector <std::string> GetExtensions() const;
	bool GetEncode() const;
	bool GetSubdirectories() const;

};

