#pragma once


template<typename T>
std::istream &operator>>(std::istream &is, std::pair<T, T> &v) {
	is >> v.first >> v.second;
	return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<T,T> &v) {
	os << "[" << v.first << ", " << v.second << "]";
	return os;
}
