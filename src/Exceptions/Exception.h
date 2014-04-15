#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception: public std::exception
{
public:
	Exception();
	explicit Exception(const std::string& message);
	virtual ~Exception() = default;

	Exception(const Exception& other);
	Exception(Exception&& other) noexcept;
	Exception& operator =(const Exception& other);
	Exception& operator =(Exception&& other) noexcept;

	virtual const char* what() const noexcept override {return m_message.c_str();}

protected:
	void setMessage(const std::string& message) {m_message = message;}


private:
	std::string m_message;
};

#endif
