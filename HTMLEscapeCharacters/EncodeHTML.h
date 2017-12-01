#pragma once

#include <string>
#include <vector>

class CEncodeHTML
{
	CEncodeHTML();
public:
	virtual ~CEncodeHTML();

	static int EncodeFile(const std::string &strSource, const  std::string &strDestination, bool bEncode);
	static int EncodeFileMessage(const std::string &strSource, const  std::string &strDestination, bool bEncode);
	static int EncodePath(const std::string &strSource, const std::string &strDestination, const std::vector<std::string> &strExtensions = { "" }, bool bEncode = true);

	static std::vector<std::string> GetDirectoryFiles(const std::string &strDir, const std::vector<std::string> &strExtensions);
};

