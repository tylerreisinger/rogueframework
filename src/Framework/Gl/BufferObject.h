#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_

#include "GlObject.h"

#include "Framework/GlHeaders.h"

#include <vector>
#include <array>
#include <memory>

#include "Framework/Flags.h"
#include "Enums.h"

#include "Context.h"

#include "Framework/Exceptions/GlException.h"

namespace rf
{
namespace gl
{

class Context;

class BufferObject : public GlObject
{
public:
	template <typename T>
	class Mapping
	{
		friend class BufferObject;

		~Mapping();

		Mapping(const Mapping&) = delete;
		Mapping& operator =(const Mapping&) = delete;

		Mapping(Mapping&&) noexcept;
		Mapping& operator =(Mapping&&) noexcept;

		T& operator [](intptr_t index) {return m_buffer[index];}

		T* data() {return m_buffer;}
		size_t size() const {return m_size;}


		void release();

	protected:
		Mapping(BufferObject* bufferObject, T* buffer, size_t size);

		BufferObject* m_bufferObject = nullptr;
		T* m_buffer = nullptr;
		size_t m_size = 0;
	};

	enum class UsageType
	{
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY,
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY
	};

	enum class MappingOptions
	{
		Read = GL_MAP_READ_BIT,
		Write = GL_MAP_WRITE_BIT,
		Flush = GL_MAP_FLUSH_EXPLICIT_BIT,
		Invalidate = GL_MAP_INVALIDATE_BUFFER_BIT,
		Unsyncronized = GL_MAP_UNSYNCHRONIZED_BIT,
		InvalidateRange = GL_MAP_INVALIDATE_RANGE_BIT
	};

	explicit BufferObject(UsageType usage, Context* context);
	virtual ~BufferObject();

	BufferObject(const BufferObject&) = delete;
	BufferObject& operator =(const BufferObject&) = delete;

	BufferObject(BufferObject&& other) noexcept;
	BufferObject& operator =(BufferObject&& other) noexcept;

	friend void swap(BufferObject& buffer1, BufferObject& buffer2);

	void clear(size_t bufferSize = 0);

	void setData(const void* data, size_t sizeInBytes);

	template<typename T>
	void setData(const std::vector<T>& data) {setData(data.data(), data.size() * sizeof(T));}
	template <typename T, size_t N>
	void setData(const std::array<T, N>& data) {setData(data.data(), N * sizeof(T));}

	void setSubData(const void* data, size_t sizeInBytes, intptr_t offset);

	template<typename T>
	void setSubData(const std::vector<T>& data, intptr_t offset) {setSubData(data.data(), data.size() * sizeof(T), offset);}
	template<typename T, size_t N>
	void setSubData(const std::array<T, N>& data, intptr_t offset) {setSubData(data.data(), N * sizeof(T), offset);}

	template <typename T>
	Mapping<T> map(intptr_t startOffset, size_t count, const Flags<MappingOptions>& access);
	template <typename T>
	Mapping<T> map(const Flags<MappingOptions>& access) {return map<T>(0, m_size, access);}

	void* mapRaw(intptr_t startOffset, size_t count, const Flags<MappingOptions>& access);
	void* mapRaw(const Flags<MappingOptions>& access) {return mapRaw(0, m_size, access);}
	void flushMappedBufferRange(intptr_t startOffset, size_t size);
	void unmap();

	void getData(intptr_t offset, size_t count, char* outBuffer);
	template<typename T>
	std::unique_ptr<T []> getData(intptr_t offset, size_t count) const;
	template<typename T>
	void getData(intptr_t offset, size_t count, std::vector<T>& dataOut);

#if GL_TARGET_VERSION >= 301
	void copyBuffer(const BufferObject& buffer);
	void copyBuffer(const BufferObject& buffer, intptr_t sourceOffset, intptr_t destOffset, size_t count);
#endif

	size_t size() const {return m_size;}
	UsageType getUsageType() const {return m_usage;}
	void setUsageType(UsageType value) {m_usage = value;}

	virtual BufferBindTarget getTarget() const = 0;

	virtual void destroy() override;

protected:
	BufferObject() {};
	UsageType m_usage = UsageType::StaticDraw;
	size_t m_size = 0;
};

template<typename T>
inline BufferObject::Mapping<T> BufferObject::map(intptr_t startOffset, size_t count,
		const Flags<MappingOptions>& access)
{
	void* buffer = mapRaw(startOffset, count, access);
	return BufferObject::Mapping<T>(this, reinterpret_cast<T*>(buffer), count);
}

template<typename T>
inline std::unique_ptr<T []> BufferObject::getData(intptr_t offset, size_t count) const
{
	std::unique_ptr<T []> buffer(new T[count]);
	glGetBufferSubData(getTarget(), offset, count * sizeof(T), buffer.get());
	CHECK_GL_ERROR(glGetBufferSubData);
	return std::move(buffer);
}

template<typename T>
inline void BufferObject::getData(intptr_t offset, size_t count,
		std::vector<T>& dataOut)
{
	dataOut.resize(dataOut.size() + count);
	glGetBufferSubData(getTarget(), offset, count * sizeof(T), dataOut.data());
	CHECK_GL_ERROR(glGetBufferSubData);
}


template<typename T>
inline BufferObject::Mapping<T>::Mapping(BufferObject* bufferObject, T* buffer, size_t size):
	m_bufferObject(bufferObject), m_buffer(buffer), m_size(size)
{
}

template<typename T>
inline BufferObject::Mapping<T>::~Mapping()
{
	if(m_bufferObject != nullptr)
	{
		m_bufferObject->unmap();
	}
}

template<typename T>
inline BufferObject::Mapping<T>::Mapping(Mapping&& mapping) noexcept
{
	m_bufferObject = mapping.m_bufferObject;
	m_buffer = mapping.m_buffer;
	mapping.m_bufferObject = nullptr;
	mapping.m_buffer = nullptr;
}

template<typename T>
inline BufferObject::Mapping<T>& BufferObject::Mapping<T>::operator =(Mapping&& mapping) noexcept
{
	m_bufferObject = mapping.m_bufferObject;
	m_buffer = mapping.m_buffer;
	mapping.m_bufferObject = nullptr;
	mapping.m_buffer = nullptr;
	return *this;
}

template<typename T>
inline void BufferObject::Mapping<T>::release()
{
	m_bufferObject = nullptr;
	m_buffer = nullptr;
}

}
}

#endif
