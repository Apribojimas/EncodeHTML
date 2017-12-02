#pragma once

#include <string>
#include <vector>

#include "TinyXML\tinyxml2.h"

class CEncodeHTML
{
	bool m_bEncode;
	bool m_bSub; //subdirectories

public:
	CEncodeHTML(bool bEncode, bool bSub);
	virtual ~CEncodeHTML();

	int EncodeFile(const std::string &strSource, const  std::string &strDestination);
	int EncodeFileMessage(const std::string &strSource, const  std::string &strDestination);
	int EncodePath(const std::string &strSource, const std::string &strDestination, const std::vector<std::string> &strExtensions = { "" });

private:
	void XMLWalk(tinyxml2::XMLElement* pElement);
	void CreateDirectory(const std::string &strSource) const;
};

