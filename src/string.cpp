/*
 * StringCpp.cpp
 *
 *  Created on: Jan 4, 2012
 *      Author: behnam
 */
#include <iostream>
#include <string.h>//c style api
#include <string>//c++ style api
#include <sstream>
#include <iterator>
#include <vector>
#include <string_view>
#include <algorithm>
#include <locale.h>
void stringDatraTypes()
{
/*
    ============================= ASCII =============================
    ASCII uses 7 bits to represent a character. By using 7 bits, we can have a maximum of 2^7 (= 128)
    distinct combinations. Which means that we can represent 128 characters maximum.
    The last bit (8th) is used for avoiding errors as parity bit. Most ASCII characters are printable
    characters of the alphabet such as abc, ABC, 123, ?&!, etc. The others are control
    characters such as carriage return, line feed, tab, etc. ASCII was meant for English only.

    ============================= ANSI =============================
    The main difference between ANSI and ASCII is the number of characters they can represent.
    ASCII was the first to be developed and when its limitations were reached, ANSI was one of the
    ways created to expand the number of characters that can be represented in an encoding.
    In ANSI, 8 bits are used; increasing the maximum number of characters to be represented up to 256.
    This is expanded even further because of how ANSI uses code pages with different character sets.
    There are a number of ANSI code pages that are meant for other languages like Japanese, Chinese,
    and many others. The application processing the file just needs to know which code page is in use
    in order to decipher the files properly.

    There are many variants of Extended ASCII characters (8-bit system) to cover regional characters
    and symbols. One example is the extended ASCII characters which includes various letters needed for
    writing languages of Western Europe and certain special characters. This encoding is called ISO Latin-1
    or ISO 8859-1, (ISO refers to International Organization for Standardization), which is the default
    character set in most browsers. The ISO 8859-1 character set includes the original ASCII character
    set (values 0 to 127), plus an extended character set (codes from 160-255) which contains the characters
    used in Western European countries and some commonly used special characters. Many Windows systems use
    another related 8-bit encoding, and this Microsoft specific encoding is referred to as ANSI, or Windows-1252.
    It is similar to ISO 8859-1 except that character codes 128-159 in ISO 8859-1 are reserved for controls
    whereas ANSI uses most of them for printable characters. ANSI stands for American National Standards Institute.
    The ANSI character set includes the standard ASCII character set (values 0 to 127), plus an extended
    character set (values 128 to 255).

    //https://www.excelanytime.com/excel/index.php?option=com_content&view=article&id=116:ascii-code-extended-ascii-characters-8-bit-system-and-ansi-code&catid=78&Itemid=474
    ============================= ASCII Extended (extended ASCII" or "8-bit ASCII) =============================
    Some clever people started using the 8th bit (the bit used for parity) to encode more characters to support
    their language (to support "é", in French, for example). Just using one extra bit doubled the size of the
    original ASCII table to map up to 256 characters (2^8 = 256 characters).

    ============================= Unicode =============================
    ASCII Extended solves the problem for languages that are based on the Latin alphabet but not other languages
    that are completely different (Greek, Russian, Chinese) We would have needed an entirely new character set.
    Unicode doesn't contain every character from every language:
    https://unicode-table.com/

    You need to "encode" this abstract representation. That's where an encoding comes into play
    (https://en.wikipedia.org/wiki/Character_encoding).
    Character encoding: is used to map every character to series of bits, number  or electrical pulse
    (Morse code, ASCII, Unicode)

    ============================= Encodings: UTF-8 vs UTF-16 vs UTF-32 =============================
    UTF-8 and UTF-16 are variable length encodings.
    In UTF-8, a character may occupy a minimum of 8 bits.
    In UTF-16, a character length starts with 16 bits.
    UTF-32 is a fixed length encoding of 32 bits.

    https://en.wikipedia.org/wiki/Comparison_of_Unicode_encodings


    ============================= strings in windows =============================

    ====================== 8-bit AnsiStrings ======================
    char: 8-bit character - underlying C/C++ data type
    CHAR: alias of char - Windows data type
    LPSTR: null-terminated string of CHAR (Long Pointer)
    LPCSTR: constant null-terminated string of CHAR (Long Pointer)
    
    char is supposed to hold a character, usually an 8-bit character.
    wchar_t is supposed to hold a wide character, and then, things get tricky:
    On Linux, a wchar_t is 4 bytes, while on Windows, it's 2 bytes.
    neither char nor wchar_t is directly tied to unicode!.


    ====================== 16-bit UnicodeStrings ======================
    wchar_t: 16-bit character - underlying C/C++ data type
    WCHAR: alias of wchar_t - Windows data type
    LPWSTR: null-terminated string of WCHAR (Long Pointer)
    LPCWSTR: constant null-terminated string of WCHAR (Long Pointer)

    ====================== depending on UNICODE define ======================
    TCHAR: alias of WCHAR if UNICODE is defined; otherwise CHAR
    LPTSTR: null-terminated string of TCHAR (Long Pointer)
    LPCTSTR: constant null-terminated string of TCHAR (Long Pointer)


    | Item              | 8-bit        | 16-bit      | Varies          |
    |-------------------|--------------|-------------|-----------------|
    | character         | CHAR         | WCHAR       | TCHAR           |
    | string            | LPSTR        | LPWSTR      | LPTSTR          |
    | string (const)    | LPCSTR       | LPCWSTR     | LPCTSTR         |


    LPCTSTR = L‌ong P‌ointer to a C‌onst T‌CHAR STR‌ing. 
    a long pointer is the same as a pointer. There were two flavors of pointers under 16-bit windows.

    LPSTR = char*
    LPCSTR = const char*
    LPWSTR = wchar_t*
    LPCWSTR = const wchar_t* (This type is declared in WinNT.h as follows: typedef CONST WCHAR *LPCWSTR;)
    LPTSTR = char* or wchar_t* depending on _UNICODE
    LPCTSTR = const char* or const wchar_t* depending on _UNICODE
    
    
    This type is declared in WinNT.h as follows:

    #ifdef UNICODE
       typedef LPCWSTR LPCTSTR; 
    #else
       typedef LPCSTR LPCTSTR;
    #endif


    std::string is a basic_string templated on a char, and std::wstring on a wchar_t.

    Type	                        Definition
    std::string	                std::basic_string<char>
    std::wstring	        std::basic_string<wchar_t>
    std::u8string (C++20)	std::basic_string<char8_t>
    std::u16string (C++11)	std::basic_string<char16_t>
    std::u32string (C++11)	std::basic_string<char32_t>

    //https://stackoverflow.com/questions/28917431/what-do-t-and-l-mean-in-c-and-how-can-i-pass-them 	
    ===================== Checklist for Windows string programming =====================
    1)_T(), and its Win32 equivilent TEXT(), are preprocessor macros that prepend the input value with L if
    _UNICODE or UNICODE are defined, respectively.
    The _T() macro was added when you needed to support Windows NT and later (which support Unicode) and Windows 9x/ME
    (which do not). These days any code using these macros is obsolete, since all modern Windows versions are Unicode-based.

    _T("Hello") //if defined UNICODE, change "Hello" into UNICODE; otherwise, keep it in ANSI.
    
    The plain versions without the underscore affect the character set the Windows header files treat as default. 
    So if you define UNICODE, then GetWindowText will map to GetWindowTextW instead of GetWindowTextA, for example. 
    Similarly, the TEXT macro will map to L"..." instead of "...".
    The versions with the underscore affect the character set the C runtime header files treat as default. 
    So if you define _UNICODE, then _tcslen will map to wcslen instead of strlen, for example. Similarly, 
    the _TEXT macro will map to L"..." instead of "...".
    
    UNICODE is used by Windows headers, whereas _UNICODE is used by C-runtime/MFC headers.

     2) Use _TCHAR and _T() with C functions. Use TCHAR and TEXT() with the Win32 API.
     CString is based on the TCHAR data type.", so use TEXT()

     3) Use LPTSTR and LPCTSTR instead of char * and const char *

     LPCSTR is a pointer to a const string
     LPCTSTR is a pointer to a const TCHAR string, (TCHAR being either a wide char or char depending on
     whether UNICODE is defined in your project)
     LPTSTR is a pointer to a (non-const) TCHAR string

     For C++ strings, use std::wstring instead of std::string
   
    You don't need to use <const > in <const char *> when you define c style strings.
    The reason is you don't want to increase or decrease the  length  of your string as it has fixed sized memory.
    Just because it is <char *> it doesn't mean it is in heap, and we don't call delete.
    it is null terminated character \0.
    Char are initialized with single quotation '' If you use double quotation ""  it is char *
*/

    char* name0 = "behnam";
    char name1[6] = { 'b','e', 'h', 'n', 'a','m' };

    //this will print lots of strange character until it hit the null termination  character 0
    std::cout << "name1: " << name1 << std::endl;

    char name2[7] = { 'b','e', 'h', 'n', 'a','m','\0' }; //or = { 'b','e', 'h', 'n', 'a','m', 0 };
    std::cout << "name2: " << name2 << std::endl;

/*
    =================================== Character/ String literals ===================================
*/

    auto c0 = 'A'; // char
    auto c1 = u8'A'; // char
    auto c2 = L'A'; // wchar_t
    auto c3 = u'A'; // char16_t
    auto c4 = U'A'; // char32_t

    // Multicharacter literals
    auto m0 = 'abcd'; // int, value 0x61626364

    // String literals
    auto s0 = "hello"; // const char*
    auto s1 = u8"hello"; // const char*, encoded as UTF-8
    auto s2 = L"hello"; // const wchar_t*
    auto s3 = u"hello"; // const char16_t*, encoded as UTF-16
    auto s4 = U"hello"; // const char32_t*, encoded as UTF-32


    const char* multiline = R"(line1
        line2
        line3)";

    (void)c0;


    std::cout << "sizeof(char): " << sizeof(char) << std::endl;
    std::cout << "sizeof(wchar_t): " << sizeof(wchar_t) << std::endl;
    std::cout << "sizeof(char16_t): " << sizeof(char16_t) << std::endl;
    std::cout << "sizeof(char32_t): " << sizeof(char32_t) << std::endl;
    std::cout << "sizeof(std::string): " << sizeof(std::string) << std::endl;
    std::cout << "sizeof(std::wstring): " << sizeof(std::wstring) << std::endl;
    std::cout << "sizeof(std::u32string): " << sizeof(std::u32string) << std::endl;

    using namespace std::string_literals;
    // s is function which turn char array string into c++ string
    std::string name5 = "Behnam"s + "Asadi"s;

}

void splitingByDelimiter()
{
    std::vector<std::string> spilitedString;
    std::string s = "scott>=tiger>=mushroom";
    std::string delimiter = ">=";

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        //std::cout << token << std::endl;
        spilitedString.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    for(std::size_t i=0;i<spilitedString.size();i++)
        std::cout << spilitedString[i] << std::endl;
}

//string to number and number to string
void stringNumberConversion()
{
    std::string strNumber=std::to_string(10.3);
    float f=std::atof(strNumber.c_str());//10.3
    int i =std::stoi(strNumber.c_str());//10
    double d =std::stod(strNumber.c_str() );//10.3
}

void cStyleString()
{
/*
A string is a sequence of chars, strings are typically represented as char arrays that have a null terminator.
'\0' character (which has ASCII code 0).
Since C-style strings are arrays, you can use the [] operator to change individual characters in the string:
*/
//////////////////////////// c style string definition //////////////////////////// 

	char name0[10] = { 'b','e','h','n','a','m','\0' }; //stack variable, compiler output: char name0[10] = {'b', 'e', 'h', 'n', 'a', 'm', '\0', '\0', '\0', '\0'};
	char name1[] = { 'b','e','h','n','a','m','\0' };//stack variable, compiler output: char name1[7] = {'b', 'e', 'h', 'n', 'a', 'm', '\0'};
	char name2[] = "behnam";//stack variable, compiler output: char name2[7] = "behnam";
	char* name3 = "behnam";// heap variable

	char name4[6] = { 'b','e', 'h', 'n', 'a','m' };
	//this will print lots of strange character until it hit the null termination  character 0
	std::cout << "name4: " << name4 << std::endl;


//////////////////////////// c style string elements access and modifications //////////////////////////// 

	char string1[] = "string";
	string1[1] = 'p';
	std::cout << string1 << std::endl;


	//but the following code is wrong
	//	string1 = "rope";


	char const* p2 = "Mary";
	// not allowed.
	//*p2 = 'C';
	p2 = "Margarethe";  // allowed

	char* const p1 = "John";
	*p1 = 'C'; // allowed
	// not allowed
	//p1 = "Margarethe";


//////////////////////////// c style string copy //////////////////////////// 
	char* cstr;
	std::string str("Please split this phrase into tokens");

	cstr = new char[str.size() + 1];
	strcpy(cstr, str.c_str());
	delete[] cstr;


	char string2[] = "Copy this!";
	char string2Dest[50];
	strcpy(string2Dest, string2);

	//////////////////////////// c style string split based on delimiter //////////////////////////// 
	/*
	Splits str[] according to given delimiters and returns next token. It needs to be called in a loop to get all tokens. 
	It returns NULL when there are no more tokens.
	char * strtok(char str[], const char *delims);
	*/
    char my_str[] = "Geeks-for-Geeks";
	// Returns first token 
    char* token = strtok(my_str, "-");

	// Keep printing tokens while one of the  delimiters present in str[]. 
	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, "-");
	}
	   	  

	char* sentence = "- This, a sample string.";
    char* delimiter = " ,.-";
	char* p;
    p = strtok(sentence, delimiter);
	while (p != NULL)
	{
		std::cout << p << std::endl;
		p = strtok(NULL, " ");
	}	
}

static uint32_t s_AllocCount = 0;

void* operator new (size_t size) 
{
	s_AllocCount++;
	std::cout << "Allocating: " << size <<" bytes" <<std::endl;
    return malloc(size);
}

void printName(const std::string &name  ) 
{
    std::cout<<name <<std::endl;
}

void printName(const std::string_view& name)
{
	std::cout << name << std::endl;
}

void string_viewExample() 
{
    /*
         Dynamic memory allocation and deallocation (malloc, free and new, delete) are very slow operations
         when compared to automatic memory allocation and deallocation.
         In other words, the heap is much slower than the stack. If a static or non-large array has compile-time
         constant length, instead of a vector object, string, ... use a C-language array, std::array, or an array.
         If the array is large, such advantages are diminished and it becomes more important to avoid using too much stack space.

         To track memory allocation we overload new operator:
         void* operator new (size_t size)
     */


     //This will allocate memory
    std::string name = "Behnam Asadi";
    printName(name);
    std::cout << s_AllocCount << " allocated" << std::endl;

    //This one as well	
    //printName("Behnam Asadi");

    std::string firstName = name.substr(0, 6);
    std::cout << s_AllocCount << " allocated" << std::endl;
    std::string lastName = name.substr(7, 11);
    std::cout << s_AllocCount << " allocated" << std::endl;

    printName(name.substr(0, 6));
    std::cout << s_AllocCount << " allocated" << std::endl;

    /*
    string_view const char * to an exsiting string (and size of the string)  owned by someone else.
    */
    std::size_t sizeOfString, startingPoint;
    sizeOfString = 6;//Behnam
    startingPoint = 7;

    std::string_view firstNameView(name.c_str(), sizeOfString);
    std::cout << s_AllocCount << " allocated" << std::endl;

    printName(firstNameView);
    std::cout << s_AllocCount << " allocated" << std::endl;

    sizeOfString = 5;//Asadi
    std::string_view lastNameView(name.c_str() + startingPoint, sizeOfString);
    std::cout << s_AllocCount << " allocated" << std::endl;


    std::cout << s_AllocCount << " allocated" << std::endl;
    printName(lastNameView);
    std::cout << s_AllocCount << " allocated" << std::endl;

    /*
    if instead of:
        std::string name = "Behnam Asadi";
    we use:
        char * name = "Behnam Asadi";
    we will have 0 allocation

    */
}

void shortStringOptimization()
{

    std::size_t stringSize = sizeof(std::string);
    std::cout<< stringSize <<std::endl;

    for (std::size_t i = 0; i < stringSize; i++)
    {
        std::string s(i, 'X');
        std::cout << i<<":" <<s << std::endl;
    }
}

/// Try to find in the word the sentence - case insensitive
bool findStringCaseInsensitive(const std::string& sentence, const std::string& word)
{
	auto it = std::search(
		sentence.begin(), sentence.end(),
		word.begin(), word.end(),
		[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
	);
	return (it != sentence.end());
}




#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

//this is warning free
std::wstring StringToWideString(std::string str)
{
    if (str.empty())
    {
        return std::wstring();
    }
    size_t len = str.length() + 1;
    std::wstring ret = std::wstring(len, 0);
#if defined WIN32
    size_t size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, &str[0], (int)str.size(), &ret[0], (int)len);
    ret.resize(size);
#else
    size_t size = 0;
    _locale_t lc = _create_locale(LC_ALL, "en_US.UTF-8");
    errno_t retval = _mbstowcs_s_l(&size, &ret[0], len, &str[0], _TRUNCATE, lc);
    _free_locale(lc);
    ret.resize(size - 1);
#endif
    return ret;
}

#endif



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

std::string WidestringToString(std::wstring wstr)
{
	if (wstr.empty())
	{
		return std::string();
	}
#if defined WIN32
	int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string ret = std::string(size, 0);
	WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, &wstr[0], (int)wstr.size(), &ret[0], size, NULL, NULL);
#else
	size_t size = 0;
	_locale_t lc = _create_locale(LC_ALL, "en_US.UTF-8");
	errno_t err = _wcstombs_s_l(&size, NULL, 0, &wstr[0], _TRUNCATE, lc);
	std::string ret = std::string(size, 0);
	err = _wcstombs_s_l(&size, &ret[0], size, &wstr[0], _TRUNCATE, lc);
	_free_locale(lc);
	ret.resize(size - 1);
#endif
	return ret;
}
#endif


#include <locale>
#include <codecvt>
#include <string>
//this will give you warning regarding depricated API
void WidestringStringConversion()
{

//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//std::string narrow = converter.to_bytes(wide_utf16_source_string);
//std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
}

int main()
{

    //stringNumberConversion();
    //splitingByDelimiter();

	return 0;
}




