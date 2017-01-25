#pragma once

#include <system_error>
#include <Windows.h>

class WindowsException : public std::system_error
{
private:
	LPSTR message;

public:
	WindowsException();

	WindowsException(DWORD code);

	~WindowsException();

	virtual const char* what() const noexcept;
};