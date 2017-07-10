#include "ppm.hpp"

ppm::value_type ppm::linear_to_srgb(ppm::value_type v){
	return v > 0.00313066844250063
			 ? 1.055 * pow(v, (1.0 / 2.4)) - 0.055
			 : v * 12.92;
}

ppm::value_type ppm::srgb_to_linear(ppm::value_type v){
	return v > 0.0404482362771082
			 ? 1.055 * pow((v + 0.055) / 1.055, 2.4)
			 : v / 12.92;
}
