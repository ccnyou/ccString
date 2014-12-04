#pragma once
#include <vector>
#include <string>

// 是否可以使用CString
#define CSTRING_AVAILABLE 0

//////////////////////////////////////////////////////////////////////////
template<class String> struct GetCharType;

template<class String>
int StringGetLength(const String& strSrc);

template<class StringArray>
void StringArrayClear(StringArray* pStringArray);

template<class String>
int StringFind(const String& strSrc, const String& strTarget, int nStartPos);

template<class String>
String StringGetSubstring(const String& strSrc, int nStartPos, int nCount);

template<class String, class StringArray>
void StringArrayPushBack(StringArray* pStringArray, const String& strTarget);

template<class StringArray>
int StringArrayGetSize(const StringArray& stringArray);

template<class String, class StringArray>
void StringArrayGetAt(const StringArray& stringArray, int nIndex, String* pResult);

#if CSTRING_AVAILABLE
template<>
inline int StringGetLength(const CString& strSrc);

template<>
inline int StringFind(const CString& strSrc, const CString& strTarget, int nStartPos);

template<>
inline CString StringGetSubstring(const CString& strSrc, int nStartPos, int nCount);

template<>
struct GetCharType<CString>;
#endif
//////////////////////////////////////////////////////////////////////////

template<class String, class ArrayString>
bool StringSplit(const String& strSrc, const typename GetCharType<String>::Type* pPattern, ArrayString* pResult)
{
	bool bRet = false;
	String strTemp;
	String strSubstring;
	String strPattern;
	int nLength = 0;
	int nPatternLength = 0;

	if (pResult == NULL || pPattern == NULL)
	{
		goto Exit0;
	}

	strPattern = pPattern;
	strTemp = strSrc + strPattern;
	nLength = StringGetLength(strTemp);
	nPatternLength = StringGetLength(strPattern);
	StringArrayClear(pResult);

	for (int i = 0; i < nLength; i++)
	{
		int pos = StringFind(strTemp, strPattern, i);
		strSubstring = StringGetSubstring(strTemp, i, pos - i);
		StringArrayPushBack(pResult, strSubstring);
		i = pos + nPatternLength - 1;
	}

	bRet = true;

Exit0:
	return bRet;
}

template<class String, class ArrayString>
bool StringJoin(const typename GetCharType<String>::Type* pSeparator, const ArrayString& stringArray, String* pResult)
{
	bool bRet = false;
	String strResult;
	String strTemp;
	String strSeparator;
	int nIndex = 0;
	int nStringsCount = 0;

	strSeparator = pSeparator;
	nStringsCount = StringArrayGetSize(&stringArray);
	if (pResult == NULL || nStringsCount < 1)
	{
		goto Exit0;
	}

	StringArrayGetAt(stringArray, 0, &strResult);
	for (nIndex = 1; nIndex < nStringsCount; nIndex++)
	{
		StringArrayGetAt(stringArray, nIndex, &strTemp);
		strResult += strSeparator + strTemp;
	}

	*pResult = strResult;
	bRet = true;

Exit0:
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
template<class String>
int StringGetLength(const String& strSrc)
{
	return strSrc.length();
}

#if CSTRING_AVAILABLE
template<>
inline int StringGetLength(const CString& strSrc)
{
	return strSrc.GetLength();
}
#endif
//////////////////////////////////////////////////////////////////////////
template<class String>
int StringFind(const String& strSrc, const String& strTarget, int nStartPos)
{
	return (int)strSrc.find(strTarget, nStartPos);
}

#if CSTRING_AVAILABLE
template<>
inline int StringFind(const CString& strSrc, const CString& strTarget, int nStartPos)
{
	return strSrc.Find(strTarget, nStartPos);
}
#endif
//////////////////////////////////////////////////////////////////////////
template<class String>
String StringGetSubstring(const String& strSrc, int nStartPos, int nCount)
{
	String strRet;
	strRet = strSrc.substr(nStartPos, nCount);
	return strRet;
}

#if CSTRING_AVAILABLE
template<>
inline CString StringGetSubstring(const CString& strSrc, int nStartPos, int nCount)
{
	CString strRet;
	strRet = strSrc.Mid(nStartPos, nCount);
	return strRet;
}
#endif
//////////////////////////////////////////////////////////////////////////
template<class String, class StringArray>
void StringArrayPushBack(StringArray* pStringArray, const String& strTarget)
{
	if (pStringArray)
	{
		pStringArray->push_back(strTarget);
	}
}

template<class StringArray>
int StringArrayGetSize(const StringArray& stringArray)
{
	return (int) stringArray->size();
}

template<class String, class StringArray>
void StringArrayGetAt(const StringArray& stringArray, int nIndex, String* pResult)
{
	if (pResult)
	{
		*pResult = stringArray[nIndex];
	}
}

template<class StringArray>
void StringArrayClear(StringArray* pStringArray)
{
	if (pStringArray)
	{
		pStringArray->clear();
	}
}

//////////////////////////////////////////////////////////////////////////
template<class String>
struct GetCharType
{
	typedef char Type;
};

#if CSTRING_AVAILABLE
template<>
struct GetCharType<CString>
{
	typedef TCHAR Type;
};
#endif

template<>
struct GetCharType<std::wstring>
{
	typedef WCHAR Type;
};
//////////////////////////////////////////////////////////////////////////
