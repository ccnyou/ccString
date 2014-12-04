// ccString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Resource.h"
#include "ccString.hpp"

#include <string>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

void Test();

int _tmain(int argc, TCHAR* argv [], TCHAR* envp [])
{
    Test();
    return 0;
}

void Test()
{
	std::wstring strStdStringW(L"1,2,3");
	std::string strStdString = "1,2,3";

	std::vector<std::wstring> result2;
	std::vector<std::string> result3;

	StringSplit(strStdStringW, L",", &result2);
	StringSplit(strStdString, ",", &result3);
	StringJoin(L"--", result2, &strStdStringW);
	StringJoin("--", result3, &strStdString);

	std::cout << strStdString << std::endl;
	std::wcout << strStdStringW << std::endl;
}
