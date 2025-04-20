#ifndef FTJSON_TPP
#define FTJSON_TPP

#include "FtJSON.hpp"

#include <sstream>

template <typename T>
FtJSON::Value::Value(const T &value) : _str(FtJSON::stringify(value)) {}

template <typename T>
FtJSON::Value &FtJSON::Value::operator=(const T &rhs)
{
	_str = FtJSON::stringify(rhs);
	return *this;
}

template <typename T>
bool FtJSON::Value::operator==(const T &rhs) const
{
	return *this == Value(rhs);
}

template <typename T>
bool FtJSON::Value::operator!=(const T &rhs) const
{
	return !(*this == Value(rhs));
}

template <typename T>
T FtJSON::Value::parse() const
{
	return FtJSON::parse<T>(_str);
}

template <typename T>
std::vector<T> FtJSON::Value::parse_vector() const
{
	return FtJSON::parse_vector<T>(_str);
}

template <typename T>
std::string FtJSON::stringify(const std::vector<T> &vec)
{
	std::string result = "[";

	for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (it != vec.begin())
			result += ",";
		result += FtJSON::stringify(*it);
	}

	result += "]";
	return result;
}

template <typename T>
std::string FtJSON::stringify(const T &value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <>
inline bool FtJSON::parse<bool>(const std::string &str)
{
	if (str.substr(0, 4) == "true")
		return true;
	else if (str.substr(0, 5) == "false")
		return false;
	else
		throw Exception("Invalid FtJSON boolean");
}

template <>
inline std::string FtJSON::parse<std::string>(const std::string &str)
{
	size_t pos = 0;
	return _parse_string(str, pos);
}

template <>
inline FtJSON::Array FtJSON::parse<FtJSON::Array>(const std::string &str)
{
	size_t pos = 0;
	return _parse_array(str, pos);
}

template <>
inline FtJSON::Object FtJSON::parse<FtJSON::Object>(const std::string &str)
{
	size_t pos = 0;
	return _parse_object(str, pos);
}

template <typename T>
T FtJSON::parse(const std::string &str)
{
	size_t pos = 0;
	return _parse<T>(str, pos);
}

template <typename T>
std::vector<T> FtJSON::parse_vector(const std::string &str)
{
	std::vector<T> vec;

	FtJSON::Array array = FtJSON::parse<FtJSON::Array>(str);

	for (FtJSON::Array::const_iterator it = array.begin(); it != array.end(); ++it)
		vec.push_back(it->parse<T>());

	return vec;
}

template <typename T>
T FtJSON::_parse(const std::string &str, size_t &pos, bool next)
{
	std::istringstream iss(str.substr(pos));

	T value;
	iss >> value;

	if ((!next && !iss.eof()) || iss.fail())
		throw Exception("Invalid FtJSON value");

	pos += iss.tellg();
	return value;
}

#endif
