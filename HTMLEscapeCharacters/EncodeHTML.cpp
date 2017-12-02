#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <atlbase.h>
#include <atlconv.h>

#include "EncodeHTML.h"
#include "Utils.h"

#include <iostream> 
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


CEncodeHTML::CEncodeHTML(bool bEncode, bool bSub)
	: m_bEncode(bEncode), m_bSub(bSub)
{
}


CEncodeHTML::~CEncodeHTML()
{
}

static int print_log(const char* format, ...)
{
	static char s_printf_buf[1024];
	va_list args;
	va_start(args, format);
	_vsnprintf_s(s_printf_buf, sizeof(s_printf_buf), format, args);
	va_end(args);
	OutputDebugStringA(s_printf_buf);
	return 0;
}

void CEncodeHTML::XMLWalk(tinyxml2::XMLElement* pElement)
{
	TIXMLASSERT(pElement);
	// ... do some processing on node here ... //
	if (pElement != nullptr)
	{
		if (pElement->GetText() != nullptr)
		{
			std::string strText = pElement->GetText();
			std::wstring strTextW = CA2CT(strText.c_str(), CP_UTF8);
			if (m_bEncode)
			{
				strTextW = EncodeHTML(strTextW);
			}
			else
			{
				strTextW = DecodeHTML(strTextW);
			}

			strText = CT2CA(strTextW.c_str(), CP_UTF8);
			pElement->SetText(strText.c_str());
			OutputDebugStringA(pElement->Value());
		}

		for (tinyxml2::XMLElement* pChildElement = pElement->FirstChildElement();
			pChildElement != nullptr;
			pChildElement = pChildElement->NextSiblingElement())
		{
			XMLWalk(pChildElement);
		}
	}
}


// check if directory are created
void CEncodeHTML::CreateDirectory(const std::string &strSource) const
{
	fs::path p(strSource);
	if (!fs::is_directory(p.parent_path()))
	{
		fs::create_directories(p.parent_path());
	}
}


int CEncodeHTML::EncodeFile(const std::string &strSource, const std::string &strDestination)
{
	tinyxml2::XMLDocument xmldoc;

	tinyxml2::XMLError eResult = xmldoc.LoadFile(strSource.c_str());
	if (eResult != tinyxml2::XML_SUCCESS)
		return 1;

	tinyxml2::XMLElement *pRoot = xmldoc.RootElement();
	if (pRoot == nullptr)
		return 2;

	XMLWalk(pRoot);

	CreateDirectory(strDestination);

	eResult = xmldoc.SaveFile(strDestination.c_str());
	if (eResult != tinyxml2::XML_SUCCESS)
		return 4;
	return 0;
}


int CEncodeHTML::EncodeFileMessage(const std::string &strSource, const  std::string &strDestination)
{
	int nRet = EncodeFile(strSource, strDestination);
	switch (nRet)
	{
	case 0:
		std::cout << "Encoded: " << strSource << " => " << strDestination << std::endl;
		break;
	case 1:
		std::cout << "Parsing error: " << strSource << " => " << strDestination << std::endl;
		break;
	default:
		std::cout << "Skipped: " << strSource << " => " << strDestination << std::endl;
		break;
	}
	return nRet;
}


int CEncodeHTML::EncodePath(const std::string &strSource,const std::string &strDestination,const std::vector<std::string> &strExtensions)
{
	int nRet(0);
	int nCases(0);

	nCases += fs::is_regular_file(strSource) ? 1 : 0;
	nCases += fs::is_regular_file(strDestination) ? 2 : 0;
	nCases += fs::is_directory(strSource) ? 5 : 0;
	nCases += fs::is_directory(strDestination) ? 6 : 0;

	switch (nCases)
	{
	case 0: // incorrect paths
		nRet = 9;
		break;
	case 1: // only input are file, we need file name for output
		nRet = EncodeFileMessage(strSource, strDestination);
		break;
	case 2: //input file exist. Output file doesn't exist or wrong file name?
		break;
	case 3: // input and output are files. Remove output file before convert
		nRet = EncodeFileMessage(strSource, strDestination);
		break;
	case 5: // source directory exists, but incorrect destination directory
		nRet = 10;
		break;
	case 6: // destination directory exists, but incorrect source directory
		nRet = 11;
		break;
	case 7: // exist source file and destination directory
		{
			fs::path ps(strSource);
			std::string d = strDestination + "\\" + ps.filename().generic_string().c_str();
			nRet = EncodeFileMessage(strSource, d);
		}
		break;
	case 11: // encode directories & subdirectories
		for (auto &s : GetDirectoryFiles(strSource, strExtensions,m_bSub))
		{
			std::string sub(s);
			sub.replace(0, strSource.size(), "");
			std::string d = strDestination + "\\" + sub;
			int nCallRet = EncodeFileMessage(s, d);
			nRet = max(nRet, nCallRet);
		}
		break;
	default: // unexpected situation
		nRet = -1;
		break;
	}

	return nRet;
}


