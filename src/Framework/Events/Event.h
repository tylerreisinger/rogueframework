#ifndef EVENT_H_
#define EVENT_H_

namespace rf
{

class Event
{
public:
	enum class Type {Quit};

	explicit Event(Type type);
	virtual ~Event() = default;

	///Return the even type
	Type type() const {return m_type;}

protected:
	Type m_type;
};

}

#endif
