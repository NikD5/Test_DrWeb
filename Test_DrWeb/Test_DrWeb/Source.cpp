#include<iostream>
#include <map>

using namespace std;


template<class TKey, class TValue>
class Dictionary
{
public:
	virtual ~Dictionary() = default;

	virtual const TValue& Get(const TKey& key) const = 0;
	virtual void Set(const TKey& key, const TValue& value) = 0;
	virtual bool IsSet(const TKey& key) const = 0;
};

template<class TKey>
class NotFoundException : public exception
{
public:
	virtual const TKey& GetKey() const noexcept = 0;
};

template<class TKey>
class NFExc : public NotFoundException<TKey>
{
public:
	virtual const TKey& GetKey() const noexcept
	{
		return k;
	}

	NFExc(const TKey& key) : k(key) { }

private:
	TKey k;
};

template<class TKey, class TValue>
class Dict : public Dictionary<TKey, TValue>
{
public:
	virtual const TValue& Get(const TKey& key) const
	{
		auto it = map.find(key);
		if (it == map.end())
			throw NFExc<TKey>(key);
		return it->second;
	}

	virtual void Set(const TKey& key, const TValue& value)
	{
		map[key] = value;
	}

	virtual bool IsSet(const TKey& key) const
	{
		return map.find(key) != map.end();
	}

private:
	map<TKey, TValue> map;
};

int main()
{
	Dict<string, int> d;
	d.Set("hello", 1);
	d.Set("hai", 11);
	d.Set("world", 21);
	d.Set("world", 12);
	try
	{
		cout << d.Get("world") << '\n';
		cout << d.Get("INCORRECT") << '\n';
		cout << d.Get("hai") << '\n';
	}
	catch (const NotFoundException<string>& e)
	{
		cout << "Error: key " << e.GetKey() << " not found." << '\n';
	}
}