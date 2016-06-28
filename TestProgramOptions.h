#pragma once


class TestProgramOptions
{
public:
    TestProgramOptions();

    void test_wstringstream();
    void test_wifstream();

    void test_duplicate_options();

public:

    static std::wstring wstring_from_file( const wchar_t* file_name, int code_page = CP_UTF8 );
};
