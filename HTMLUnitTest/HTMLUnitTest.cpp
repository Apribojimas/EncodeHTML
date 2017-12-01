#include "stdafx.h"
#include "CppUnitTest.h"

#include <initializer_list>

#include "..\HTMLEscapeCharacters\EncodeHTML.h"
#include "..\HTMLEscapeCharacters\Utils.h"
#include "..\HTMLEscapeCharacters\ParseParameters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HTMLUnitTest
{
	TEST_CLASS(HTMLUnitTest)
	{
	public:

		TEST_METHOD(EncodePath)
		{
			// TODO: Your test code here
			Assert::AreEqual(CEncodeHTML::EncodePath("..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm"), 0);
			Assert::AreEqual(CEncodeHTML::EncodePath("..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output"), 0);
			Assert::AreEqual(CEncodeHTML::EncodePath("..\\HTMLEscapeCharacters\\Input\\", "..\\HTMLEscapeCharacters\\output\\"), 0);

			// unsupported and incorrect paths
			Assert::AreEqual(CEncodeHTML::EncodePath("", ""), 9);
			Assert::AreEqual(CEncodeHTML::EncodePath(".", ".\\output"), 10); // incorrect output directory
			Assert::AreEqual(CEncodeHTML::EncodePath("..\\HTMLEscapeCharacters\\Input\\h*.htm", "..\\HTMLEscapeCharacters\\output"), 11); // unsupported wildcards
			Assert::AreEqual(CEncodeHTML::EncodePath("..\\HTMLEscapeCharacters\\Input\\*.*", "..\\HTMLEscapeCharacters\\output\\"), 11); // unsupported wildcards
		}

		TEST_METHOD(GetDirectoryFiles)
		{
			// TODO: Your test code here
			Assert::AreEqual((int)CEncodeHTML::GetDirectoryFiles("..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", { ".htm", ".html" }).size(), 1);

			Assert::AreEqual((int)CEncodeHTML::GetDirectoryFiles(".", { ".htm", ".html" }).size(), 0);
			Assert::AreEqual((int)CEncodeHTML::GetDirectoryFiles("..\\HTMLEscapeCharacters\\Input\\h*.htm", { ".htm", ".html" }).size(), 0);
			Assert::AreEqual((int)CEncodeHTML::GetDirectoryFiles("..\\HTMLEscapeCharacters\\Input\\", { ".htm", ".html" }).size(), 2);
		}

		TEST_METHOD(DecodeTest)
		{
			Assert::AreEqual((int)DecodeHTML(std::wstring()).size(), 0);
			Assert::AreEqual((int)DecodeHTML(std::wstring(L"&#33; &#122; Kuku &#32; &#8482;")).size(), 12);
			Assert::AreEqual((int)DecodeHTML(std::wstring(L"&#3;")).size(), 4);
		}

		TEST_METHOD(ParseParameters)
		{
			{ // exists files and extensions, and help
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm", "/e", ".htm,.html,.xml","/?" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{ // exists files and extensions
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm", "/e", ".htm,.html,.xml" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 0);
			}

			{ // exists files
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 0);
			}

			{ // only source file
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 0);
			}

			{ // only source file & extensions
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "/e", ".htm,.html,.xml" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 0);
			}


			{ // test extensions
				char * argv[] = { ".", "/e", ".htm,.html,.xml" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{ // test extension
				char * argv[] = { ".", "/e", ".htm" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{ // trim string
				char * argv[] = { ".", "/e " };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{ // test help
				char * argv[] = { ".", "/h" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{
				char * argv[] = { ".", "/?", "/h", "-h" };
				CParseParameters p(_countof(argv), argv);

				Assert::AreEqual(p.Validate(), 1);
			}

			{
				CParseParameters p(0, nullptr);
				Assert::AreEqual(p.Validate(), 1);
			}
		}

		TEST_METHOD(ExecuteTest)
		{
			{ // directories
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input", "..\\HTMLEscapeCharacters\\output" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // directories and extensions
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\", "..\\HTMLEscapeCharacters\\output\\", "/e", ".htm,.html" };
				Assert::AreEqual(Execute(_countof(argv), argv), 0);
			}

			{ // encode current directory
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // decode current directory
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\", "/d" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // exists files and extensions, and help
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm", "/e", ".htm,.html,.xml","/?" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // exists files and extensions
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest.htm", "/e", ".htm,.html,.xml" };
				Assert::AreEqual(Execute(_countof(argv), argv), 0);
			}

			{ // non ansi file names
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "..\\HTMLEscapeCharacters\\output\\HtmlPageTest_аижл.htm" };
				Assert::AreEqual(Execute(_countof(argv), argv), 0);
			}

			{ // only source file
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm" };
				Assert::AreEqual(Execute(_countof(argv), argv), 0);
			}

			{ // only source file & extensions
				char * argv[] = { ".", "..\\HTMLEscapeCharacters\\Input\\HtmlPageTest.htm", "/e", ".htm,.html,.xml" };
				Assert::AreEqual(Execute(_countof(argv), argv), 0);
			}

			{ // test extensions
				char * argv[] = { ".", "/e", ".htm,.html,.xml" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // test extension
				char * argv[] = { ".", "/e", ".htm" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // trim string
				char * argv[] = { ".", "/e " };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{ // test help
				char * argv[] = { ".", "/h" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{
				char * argv[] = { ".", "/?", "/h", "-h" };
				Assert::AreEqual(Execute(_countof(argv), argv), 1);
			}

			{
				Assert::AreEqual(Execute(0, nullptr), 1);
			}
		}
	};
}