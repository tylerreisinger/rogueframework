#include "Exception.h"

Exception::Exception()
{
}

Exception::Exception(const std::string& message):
	m_message(message)
{
}

Exception::Exception(const Exception& other):
	m_message(other.m_message)
{
}

Exception::Exception(Exception&& other) noexcept:
	m_message(std::move(other.m_message))
{
}

Exception& Exception::operator =(const Exception& other)
{
	m_message = other.m_message;
	return *this;
}

Exception& Exception::operator =(Exception&& other) noexcept
{
	m_message = std::move(other.m_message);
	return *this;
}
