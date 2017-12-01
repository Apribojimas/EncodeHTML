..\Debug\EncodeHTML.exe /?
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // directories and extensions
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\ ..\HTMLEscapeCharacters\output\ /e .htm,.html
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // directories 
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\ ..\HTMLEscapeCharacters\output\
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // encode current directory
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // decode current directory
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\ /d
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // exists files and extensions, and help
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\HtmlPageTest.htm ..\HTMLEscapeCharacters\output\HtmlPageTest.htm /e .htm,.html,.xml /?
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // exists files and extensions
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\HtmlPageTest.htm ..\HTMLEscapeCharacters\output\HtmlPageTest.htm /e .htm,.html,.xml
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // non ansi file names
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\HtmlPageTest.htm ..\HTMLEscapeCharacters\output\HtmlPageTest_ąčęė.htm
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // only source file
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\HtmlPageTest.htm
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // only source file & extensions
..\Debug\EncodeHTML.exe ..\HTMLEscapeCharacters\Input\HtmlPageTest.htm /e .htm,.html,.xml
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // test extensions
..\Debug\EncodeHTML.exe /e .htm,.html,.xml
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // test extension
..\Debug\EncodeHTML.exe /e .htm
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // trim string
..\Debug\EncodeHTML.exe /e 
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // test help
..\Debug\EncodeHTML.exe /h
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

@REM // test help
..\Debug\EncodeHTML.exe /? /h -h
@echo ________________
@echo Return code: %ERRORLEVEL%
pause

