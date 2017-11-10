#ifndef DVEREB_DUALLOOKUP_H
#define DVEREB_DUALLOOKUP_H

#include <unordered_map>

struct DualLookupBase {
	// NOTE(dev): Used to determine which version of the string you want:
	//             1 / OPPOSITE:   The string it maps to, opposite of the one you pass in.
	//             2 / VALUE:      The string passed via the first  paramater of 'add.'
	//             3 / EQUIVALENT: The string passed via the second parameter of 'add.'
	enum Type {
		OPPOSITE = 1,
		VALUE,
		EQUIVALENT,
	};

protected:
	DualLookupBase() {}
};

template <class T>
class DualLookup : public DualLookupBase {
public:
	DualLookup();

	/* Add a mapped pair to the container
	 *  returns false if it already exists, regardless of direction
	 *   (i.e. value->equivilent is a duplicate of equivilent->value)
	 */
	bool add(T value, T equivilent);

	/* If found, Set result to the mapped value and true is returned.
	 * If not found, result remains unchanged and false is returned.
	 */
	bool get(T key, T &result, const Type &type = Type::OPPOSITE);

	/* If found, return true
	 * else return false */
	bool contains(const T &key);

private:
	std::unordered_map<T, T> owner;
	std::unordered_map<T, T> mirror;

	// NOTE(dev): These functions actually do the work:
	bool get_single(const T &key, T &result, const std::unordered_map<T, T> &umap);
	bool contains_single(const T &key, const std::unordered_map<T, T> &umap);
};

template <class T>
DualLookup<T>::DualLookup()
{
}

template <class T>
bool DualLookup<T>::add(T value, T equivilent)
{
	// already exists
	if(owner.find(value) != owner.end() || mirror.find(value) != mirror.end())
		return false;
	if(owner.find(equivilent) != owner.end() || mirror.find(equivilent) != mirror.end())
		return false;

	owner.insert({value, equivilent});
	mirror.insert({equivilent, value});

	return true;
}

template <class T>
bool DualLookup<T>::get(T key, T &result, const Type &type)
{
	if(get_single(key, result, owner))
	{
		//if(type == Type::OPPOSITE || type == Type::EQUIVALENT)
		if(type == Type::VALUE)
			result = key;
		return true;
	}
	if(get_single(key, result, mirror))
	{
		//if(type == Type::OPPOSITE || type == Type::VALUE)
		if(type == Type::EQUIVALENT)
			result = key;
		return true;
	}

	return false; // didn't find it
}

template <class T>
bool DualLookup<T>::contains(const T &key)
{
	if(contains_single(key, owner))
		return true;
	if(contains_single(key, mirror))
		return true;

	return false; // didn't find it
}

template <class T>
bool DualLookup<T>::get_single(const T &key, T &result, const std::unordered_map<T, T> &umap)
{
	auto i = umap.find(key);
	if(i == umap.end())
		return false;

	result = i->second;

	return true;
}

template <class T>
bool DualLookup<T>::contains_single(const T &key, const std::unordered_map<T, T> &umap)
{
	return umap.find(key) != umap.end();
}

#endif
