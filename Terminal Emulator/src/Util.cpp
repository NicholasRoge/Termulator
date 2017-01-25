#include "Util.h"

using std::error_code;
using std::system_category;


WindowsException::WindowsException()
: WindowsException(GetLastError())
{
}

WindowsException::WindowsException(DWORD code)
: system_error(error_code(code, system_category()))
{
	this->message = nullptr;
}

WindowsException::~WindowsException()
{
	if (this->message != nullptr)
	{
		LocalFree(this->message);
	}
}

const char* WindowsException::what() const noexcept
{
	const char* what = system_error::what();
	if (strlen(what))
	{
		return what;
	}

	if (!this->message)
	{
		DWORD flags = 0;
		flags |= FORMAT_MESSAGE_ALLOCATE_BUFFER;
		flags |= FORMAT_MESSAGE_FROM_SYSTEM;
		flags |= FORMAT_MESSAGE_IGNORE_INSERTS;

		FormatMessageA(
			flags,
			nullptr,
			this->code().value(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&this->message,
			0,
			nullptr
		);
	}

	return this->message;
}