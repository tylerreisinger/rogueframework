#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <list>
#include <unordered_map>

namespace rf
{

template<typename Key, typename Type>
class LruCache
{
public:
	LruCache(size_t capacity, std::function<void (const Key&, const Type&)> deletionCallback = nullptr):
		m_capacity(capacity), m_deletionCallback(std::move(deletionCallback))
	{
	}

	~LruCache() = default;

	LruCache(const LruCache&) = delete;
	LruCache& operator =(const LruCache&) = delete;

	LruCache(LruCache&& other) noexcept:
		m_items(std::move(other.m_items)), m_order(std::move(other.m_order)),
		m_capacity(other.m_capacity)
	{

	}

	LruCache& operator =(LruCache&& other) noexcept
	{
		if(&other != this)
		{
			m_items = std::move(other.m_items);
			m_order = std::move(other.m_order);
			m_capacity = other.m_capacity;
		}
		return *this;
	}

	Type* getItem(const Key& key);
	void addItem(const Key& key, Type item);

	void resize(size_t newSize);

	void clear();

	size_t size() const {return m_items.size();}
	bool empty() const {return m_items.empty();}
	size_t capacity() const {return m_capacity;}

	void dropOne();

protected:

	struct CacheItem
	{
		Type value;
		typename std::list<Key>::iterator it;
	};

	std::unordered_map<Key, CacheItem> m_items;
	std::list<Key> m_order;
	std::function<void (const Key&, const Type&)> m_deletionCallback;

	size_t m_capacity;
};

template<typename Key, typename Type>
inline Type* LruCache<Key, Type>::getItem(const Key& key)
{
	auto it = m_items.find(key);
	if(it != m_items.end())
	{
		m_order.splice(m_order.begin(), m_order, it->second.it);
		//m_order.erase(it->second.it);
		//m_order.push_front(key);
		it->second.it = m_order.begin();
		return &it->second.value;
	}

	return nullptr;
}

template<typename Key, typename Type>
inline void LruCache<Key, Type>::addItem(const Key& key, Type item)
{
	m_order.push_front(key);
	CacheItem cacheItem = {std::move(item), m_order.begin()};
	m_items.insert(std::make_pair(key, cacheItem));

	if(m_items.size() > m_capacity)
	{
		dropOne();
	}
}

template<typename Key, typename Type>
inline void LruCache<Key, Type>::resize(size_t newSize)
{
	while(newSize < m_items.size())
	{
		auto& lastItem = m_order.back();
		m_items.erase(lastItem);
		m_order.pop_back();
	}
	m_capacity = newSize;
}

template<typename Key, typename Type>
inline void LruCache<Key, Type>::clear()
{
	m_items.clear();
	m_order.clear();
}

}

template<typename Key, typename Type>
inline void rf::LruCache<Key, Type>::dropOne()
{
	auto& item = m_order.back();
	if(m_deletionCallback)
	{
		m_deletionCallback(item, m_items[item].value);
	}
	m_items.erase(item);
	m_order.pop_back();
}

#endif
