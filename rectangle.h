#pragma once
#include <utility>
#include <iostream>

#include "vector.h"

template<typename T>
struct Rectangle {
	std::pair<T,T> vertices[4];
};

template<typename T>
typename Rectangle<T>::std::template pair<T,T> Center(const Rectangle<T> &t);

template<typename T>
double Area(const Rectangle<T> &t);

template<typename T>
std::ostream &Print(std::ostream &os, const Rectangle<T> &t);

template<typename T>
std::istream &Read(std::istream &is, Rectangle<T> &t);

template<typename T>
std::istream &operator>>(std::istream &is, Rectangle<T> &t);

template<typename T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &t);

template<typename T>
typename Rectangle<T>::std::template pair<T,T> Center(const Rectangle<T> &t) {
	T x, y;
	x = (t.vertices[0].first + t.vertices[1].first + t.vertices[2].first + t.vertices[3].first) / 4;
	y = (t.vertices[0].second + t.vertices[1].second + t.vertices[2].second + t.vertices[3].second) / 4;

	return std::make_pair(x, y);
}

template<typename T>
double Area(const Rectangle<T> &t) {
	double hor = std::max(abs(t.vertices[0].first - t.vertices[1].first), abs(t.vertices[1].first - t.vertices[2].first));
	double ver = std::max(abs(t.vertices[0].second - t.vertices[1].second), abs(t.vertices[1].second - t.vertices[2].second));
	return hor * ver;
}

template<typename T>
std::ostream &Print(std::ostream &os, const Rectangle<T> &t) {
	for (int i = 0; i < 4; i++) {
		os << t.vertices[i];
		if (i != 2) {
			os << " ";
		}
	}
	return os;
}

template<typename T>
std::istream &Read(std::istream &is, Rectangle<T> &t) {
	for (int i = 0; i < 4; i++) {
		is >> t.vertices[i].first >> t.vertices[i].second;
	}
	double AB = Length(t.vertices[0], t.vertices[1]),
		   BC = Length(t.vertices[1], t.vertices[2]),
		   CD = Length(t.vertices[2], t.vertices[3]),
		   DA = Length(t.vertices[0], t.vertices[3]);
	if (AB != CD || BC != DA) {
		throw std::logic_error("Vectors must not be with different length.");
	}
	if (!is_parallel(t.vertices[0], t.vertices[1], t.vertices[2], t.vertices[3])){
		throw std::logic_error("Vectors must not be dont parallel.");
	}
	return is;
}

template<typename T>
std::istream &operator>>(std::istream &is, Rectangle<T> &t) {
	return Read(is, t);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Rectangle<T> &t) {
	return Print(os, t);
}
