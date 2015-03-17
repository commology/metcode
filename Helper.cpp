//#include "stdafx.h"

#include <string>
#include <set>
#include <cstdlib>
#include <clocale>
#include <locale>
#include <algorithm>

#ifdef _WINDOWS
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/time.h>
#endif

#ifdef _WINDOWS
std::string BSTR2STRING(BSTR bstr)
{
	const char *ascii = _com_util::ConvertBSTRToString(bstr);
	std::string str(ascii, ::SysStringLen(bstr));
	delete []ascii;
	return str;
}
#endif

#ifdef _WINDOWS
std::wstring BSTR2WSTRING(BSTR bstr)
{
	std::wstring str(bstr);
	return str;
}
#endif

std::wstring STRING2WSTRING(std::string str)
{
#ifdef _WINDOWS
	ATL::CComBSTR bstr(str.c_str());
	std::wstring wstr = (BSTR)bstr;
#else
	wchar_t *wcs = new wchar_t[str.length() + 1];
	mbstowcs(wcs, str.c_str(), str.length() + 1);
	std::wstring wstr = wcs;
	delete []wcs;
#endif
	return wstr;
}

std::string WSTRING2STRING(std::wstring wstr)
{
#ifdef _WINDOWS
	ATL::CComBSTR bstr(wstr.c_str());
	std::string str = BSTR2STRING(bstr);
#else
	char *mbs = new char[wstr.length() * MB_CUR_MAX + 1];
	wcstombs(mbs, wstr.c_str(), wstr.length() * MB_CUR_MAX + 1);
	std::string str = mbs;
	delete []mbs;
#endif
	return str;
}

void trim(std::wstring& str, const std::wstring chars)
{
	using namespace std;
	const wstring SPACE = chars;
	wstring::size_type pos = str.find_first_not_of(SPACE);
	if (pos != wstring::npos)
	{
		str.erase(0, pos);
		pos = str.find_last_not_of(SPACE);
		if (pos != wstring::npos)
		{
			str.erase(pos + 1);
		}
	}
	else
		str.clear();
}

void trim(std::string& str, const std::string chars)
{
	using namespace std;
	const string SPACE = chars;
	string::size_type pos = str.find_first_not_of(SPACE);
	if (pos != string::npos)
	{
		str.erase(0, pos);
		pos = str.find_last_not_of(SPACE);
		if (pos != string::npos)
		{
			str.erase(pos + 1);
		}
	}
	else
		str.clear();
}

void remove(std::wstring& str, const std::wstring chars)
{
	using namespace std;

	for (unsigned int i = 0; i < chars.length(); ++i)
		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
}

void remove(std::string& str, const std::string chars)
{
	using namespace std;

	for (unsigned int i = 0; i < chars.length(); ++i)
		str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
}

bool is_digits(const std::string& s)
{
	const char *cstr = s.c_str();
	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!isdigit(cstr[c]))
			return false;
	return true;
}

bool is_digits(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();
	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!isdigit(cstr[c]))
			return false;
	return true;
}

bool is_digits_(const std::string& s)
{
	const char *cstr = s.c_str();
	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!(isdigit(cstr[c]) || cstr[c] == L'-' || cstr[c] == L'*' || cstr[c] == L'.' || cstr[c] == L'/'))
			return false;
	return true;
}

bool is_digits_(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();
	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!(isdigit(cstr[c]) || cstr[c] == L'-' || cstr[c] == L'*' || cstr[c] == L'.' || cstr[c] == L'/'))
			return false;
	return true;
}

bool is_alnum(const std::string& s)
{
	const char *cstr = s.c_str();

	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!isalnum(cstr[c]))
			return false;
	return true;
}

bool is_alnum(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();

	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!isalnum(cstr[c]))
			return false;
	return true;
}

bool is_alnum_(const std::string& s)
{
	const char *cstr = s.c_str();

	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!(isalnum(cstr[c]) || cstr[c] == L'_'))
			return false;
	return true;
}

bool is_alnum_(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();

	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!(isalnum(cstr[c]) || cstr[c] == L'_'))
			return false;
	return true;
}

bool is_alpha(const std::string& s)
{
	const char *cstr = s.c_str();

	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!isalpha(cstr[c]))
			return false;
	return true;
}

bool is_alpha(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();

	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!isalpha(cstr[c]))
			return false;
	return true;
}

bool is_alpha_(const std::string& s)
{
	const char *cstr = s.c_str();

	for (std::string::size_type c = 0; c < s.length(); c++)
		if (!(isalpha(cstr[c]) || cstr[c] == L'_'))
			return false;
	return true;
}

bool is_alpha_(const std::wstring& s)
{
	const wchar_t *cstr = s.c_str();

	for (std::wstring::size_type c = 0; c < s.length(); c++)
		if (!(isalpha(cstr[c]) || cstr[c] == L'_'))
			return false;
	return true;
}

std::wstring getTimestampString(bool includeMilliSecond)
{
	wchar_t tmp[24];
	std::wstring strTimestamp;

#ifdef _WINDOWS
	SYSTEMTIME now;
	GetSystemTime(&now);
	if (includeMilliSecond)
		wsprintf(tmp, L"%04d%02d%02d%02d%02d%02d.%03d", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds);
	else
		wsprintf(tmp, L"%04d%02d%02d%02d%02d%02d", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
	strTimestamp = tmp;
#else
	struct tm tmdate;
	struct timeval now;
	gettimeofday(&now, NULL);
	gmtime_r(&(now.tv_sec), &tmdate);
	wcsftime(tmp, 18, L"%Y%m%d%H%M%S", &tmdate);
	strTimestamp = tmp;
	if (includeMilliSecond)
	{
		swprintf(tmp, 10, L".%03d", now.tv_usec / 1000);
		strTimestamp += tmp;
	}
#endif

	return strTimestamp;
}

std::wstring formalizeFamilyName(std::wstring familyName)
{
	std::transform(familyName.begin(), familyName.end(), familyName.begin(), ::tolower);
#ifdef _MET_ACTIVEMQ_
	if (familyName == L"activemq")
		return L"ActiveMQ";
#endif
#ifdef _MET_RABBITMQ_
	if (familyName == L"rabbitmq")
		return L"RabbitMQ";
#endif
	return familyName;
}

#ifdef _WINDOWS
void ErrorMessageBox(LPCTSTR lpcszFunction, LPCTSTR lpcszParam)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpcszFunction) + lstrlen((LPCTSTR)lpcszParam) + 40) * sizeof(TCHAR));
	wnsprintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s(%s) failed with error %d: %s"),
		lpcszFunction, lpcszParam, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("System Call Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}
#endif

#ifdef _WINDOWS
bool GetIPAddr(std::set<std::wstring>& setIPAddr)
{
	setIPAddr.clear();

	//-----------------------------------------
	// Declare and initialize variables
	WSADATA wsaData;
	int iResult;
	INT iRetval;

	DWORD dwRetval;

	int i = 1;

	char* ip = "";
	char* port = "";

	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	struct sockaddr_in  *sockaddr_ipv4;
	// struct sockaddr_in6 *sockaddr_ipv6;
	LPSOCKADDR sockaddr_ip;

	TCHAR ipstringbuffer[46];
	DWORD ipbufferlength = 46;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	//--------------------------------
	// Setup the hints address info structure
	// which is passed to the getaddrinfo() function
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//--------------------------------
	// Call getaddrinfo(). If the call succeeds,
	// the result variable will hold a linked list
	// of addrinfo structures containing response
	// information
	dwRetval = getaddrinfo(ip, port, &hints, &result);
	if (dwRetval != 0)
	{
		printf("getaddrinfo failed with error: %d\n", dwRetval);
		WSACleanup();
		return false;
	}

	printf("getaddrinfo returned success\n");

	// Retrieve each address and print out the hex bytes
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		printf("getaddrinfo response %d\n", i++);
		printf("\tFlags: 0x%x\n", ptr->ai_flags);
		printf("\tFamily: ");
		switch (ptr->ai_family)
		{
		case AF_UNSPEC:
			printf("Unspecified\n");
			break;
		case AF_INET:
			printf("AF_INET (IPv4)\n");
			//sockaddr_ipv4 = (struct sockaddr_in *) ptr->ai_addr;
			//printf("\tIPv4 address %s\n", inet_ntoa(sockaddr_ipv4->sin_addr));
			//sprintf(ipaddr, "%s", inet_ntoa(sockaddr_ipv4->sin_addr));
			sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
			ipbufferlength = 46;
			iRetval = WSAAddressToString(sockaddr_ip, (DWORD)ptr->ai_addrlen, NULL, ipstringbuffer, &ipbufferlength);
			break;
		case AF_INET6:
			printf("AF_INET6 (IPv6)\n");
			// the InetNtop function is available on Windows Vista and later
			// sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
			// printf("\tIPv6 address %s\n",
			//    InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );

			// We use WSAAddressToString since it is supported on Windows XP and later
			sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
			// The buffer length is changed by each call to WSAAddresstoString
			// So we need to set it for each iteration through the loop for safety
			ipbufferlength = 46;
			iRetval = WSAAddressToString(sockaddr_ip, (DWORD)ptr->ai_addrlen, NULL, ipstringbuffer, &ipbufferlength);
			if (iRetval)
				printf("WSAAddressToString failed with %u\n", WSAGetLastError());
			else
				printf("\tIPv6 address %s\n", ipstringbuffer);
			break;
		case AF_NETBIOS:
			printf("AF_NETBIOS (NetBIOS)\n");
			break;
		default:
			printf("Other %ld\n", ptr->ai_family);
			break;
		}

		std::wstring strIP = ipstringbuffer;
		setIPAddr.insert(strIP);
	}

	freeaddrinfo(result);
	WSACleanup();

	return true;
}
#endif

#ifdef _WINDOWS
ULONG CaptureScreen(BYTE** content)
{
	unsigned int cx = GetSystemMetrics(SM_CXSCREEN), cy = GetSystemMetrics(SM_CYSCREEN);
	HDC hScreenDC = ::GetDC(NULL);
	HDC hMemDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	BitBlt(hMemDC, 0, 0, cx, cy, hScreenDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	::ReleaseDC(NULL, hScreenDC);

	size_t headerSize = sizeof(BITMAPINFOHEADER)+3 * sizeof(RGBQUAD);
	BYTE* pHeader = new BYTE[headerSize];
	LPBITMAPINFO pbmi = (LPBITMAPINFO)pHeader;
	memset(pHeader, 0, headerSize);
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biBitCount = 0;
	if (!GetDIBits(hMemDC, hBitmap, 0, 0, NULL, pbmi, DIB_RGB_COLORS))
	{
		*content = NULL;
		return 0;
	}

	BITMAPFILEHEADER bmf;
	if (pbmi->bmiHeader.biSizeImage <= 0)
		pbmi->bmiHeader.biSizeImage = pbmi->bmiHeader.biWidth*abs(pbmi->bmiHeader.biHeight)*(pbmi->bmiHeader.biBitCount + 7) / 8;
	BYTE* pData = new BYTE[pbmi->bmiHeader.biSizeImage];
	bmf.bfType = 0x4D42; bmf.bfReserved1 = bmf.bfReserved2 = 0;
	bmf.bfSize = sizeof(BITMAPFILEHEADER) + headerSize + pbmi->bmiHeader.biSizeImage;
	bmf.bfOffBits = sizeof(BITMAPFILEHEADER) + headerSize;
	if (!GetDIBits(hMemDC, hBitmap, 0, abs(pbmi->bmiHeader.biHeight), pData, pbmi, DIB_RGB_COLORS))
	{
		delete []pData;
		*content = NULL;
		return 0;
	}

	ULONG offset = 0;
	/*
	ULONG content_size = sizeof(BITMAPFILEHEADER) + headerSize + pbmi->bmiHeader.biSizeImage;
	*content = new BYTE[content_size + 1];
	memcpy(content + offset, &bmf, sizeof(BITMAPFILEHEADER));
	offset += sizeof(BITMAPFILEHEADER);
	memcpy(content + offset, pbmi, headerSize);
	offset += headerSize;
	memcpy(content + offset, pData, pbmi->bmiHeader.biSizeImage);
	offset += pbmi->bmiHeader.biSizeImage;
	*/
	
	FILE* hFile = fopen("heartbeat.bmp", "wb");
	fwrite(&bmf, sizeof(BITMAPFILEHEADER), 1, hFile);
	fwrite(pbmi, headerSize, 1, hFile);
	fwrite(pData, pbmi->bmiHeader.biSizeImage, 1, hFile);
	fclose(hFile);

	DeleteObject(hBitmap);
	DeleteDC(hMemDC);

	delete []pData;

	return offset;
}
#endif
