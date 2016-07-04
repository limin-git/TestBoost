#pragma once


class TestProgramOptions
{
public:
    TestProgramOptions();

    void test_wstringstream();
    void test_wifstream();
    void test_notifier();
    void test_variables_map();
    void test_multitoken();
    void test_multitoken_2();
    void test_positional();
    void test_positional_2();
    void test_add_same_descriptions();

public:

    static std::wstring wstring_from_file( const wchar_t* file_name, int code_page = CP_UTF8 );
};
