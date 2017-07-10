#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <math.h>

namespace ppm{
	typedef float value_type;
	using pixel = std::array<value_type, 3>;
	template<std::size_t rows, std::size_t columns>
	using image = std::array<std::array<pixel, columns>, rows>;
	template<std::size_t rows, std::size_t columns>
	void convert_color_space(
		image<rows, columns>& img, 
		const std::function<value_type(value_type)>& transform_function
	){
		for(auto& r: img) for(auto& p: r) for(auto& v: p)
			v = transform_function(v);
	}
	value_type linear_to_srgb(value_type v);
	value_type srgb_to_linear(value_type v);
};

template<std::size_t rows, std::size_t columns>
std::ostream& operator<<(
	std::ostream& os,
	const ppm::image<rows, columns>& img
){
	os << "P6\n"
	   << std::to_string(columns)
	   << ' '
	   << std::to_string(rows)
	   << '\n'
	   << std::to_string(std::numeric_limits<unsigned char>::max())
	   << '\n';
	for(auto& r: img) for(auto& p: r) for(auto& v: p)
		os << (unsigned char)std::min((unsigned)(v * 256), 255u);
	return os;
}

template<std::size_t rows, std::size_t columns>
std::istream& operator>>(
	std::istream& is,
	ppm::image<rows, columns>& img
){
	std::string burn;
	for(auto i = 0; i < 4; i++) is >> burn;
	is.get(); // idk why this is needed
	for(auto& r: img) for(auto& p: r) for(auto& v: p)
		v = (ppm::value_type)is.get() / 256;
	return is;
}
