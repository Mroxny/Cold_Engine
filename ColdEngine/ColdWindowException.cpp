#include "ColdWindowException.h"
#include <sstream>


ColdWindowException::ColdWindowException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ColdWindowException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();

	eBuffer = oss.str();
	return eBuffer.c_str();
}

const char* ColdWindowException::GetType() const noexcept
{
	return "Cold Engine Exception";
}

int ColdWindowException::GetLine() const noexcept
{
	return line;
}

const std::string& ColdWindowException::GetFile() const noexcept
{
	return file;
}

std::string ColdWindowException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}