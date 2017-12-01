Create a command line tool or library for a chosen platform in C++ that could replace all HTML text data with escape characters. Feel free to use a 3rd party library for HTML parsing and printing.

- Should be able to work with single HTML files as well as directories (output directory should preserve input directory's structure)
- Generate a rename map in a chosen format
- Prefer using C++11 features where applicable
- Publish it on Github

Transformation example:
<html>
    <body>
        <h1>abc</h1>
        <p>123</p>
    </body>
</html>
->
<html>
    <body>
        <h1>&#97;&#98;&#99;</h1>
        <p>&#49;&#50;&#51;</p>
    </body>
</html>

Rename map example:
{
    "abc": "&#97;&#98;&#99;",
    "123": "&#49;&#50;&#51;"
}

