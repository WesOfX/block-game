#pragma once

template<class coord_t>
struct vec2{
	typedef coord_t coord_type;
    coord_type x, y;
};

template<class coord_t>
inline constexpr vec2<coord_t> operator-(const vec2<coord_t>& rhs){
    return {-rhs.x, -rhs.y};
}

template<class coord_t>
inline constexpr vec2<coord_t>& operator+=(
    vec2<coord_t>& lhs, 
    const vec2<coord_t>& rhs
){
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template<class coord_t>
inline constexpr vec2<coord_t>& operator-=(
    vec2<coord_t>& lhs,
    const vec2<coord_t>& rhs
){
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template<class coord_t>
inline constexpr vec2<coord_t> operator+(
    const vec2<coord_t>& lhs, 
    const vec2<coord_t>& rhs
){
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template<class coord_t>
inline constexpr vec2<coord_t> operator-(
    const vec2<coord_t>& lhs, 
    const vec2<coord_t>& rhs
){
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template<class coord_t>
inline constexpr vec2<coord_t> operator*(
    const vec2<coord_t>& lhs, 
    coord_t rhs
){
    return {lhs.x * rhs, lhs.y * rhs};
}

template<class coord_t>
inline constexpr vec2<coord_t> operator*(
    coord_t lhs,
    const vec2<coord_t>& rhs
){
    return {rhs.x * lhs, rhs.y * lhs};
}

template<class coord_t>
inline constexpr vec2<coord_t>& operator*=(
    vec2<coord_t>& lhs, 
    coord_t rhs
){
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

template<class coord_t>
inline constexpr vec2<coord_t> operator/(
    const vec2<coord_t>& lhs, 
    coord_t rhs
){
    return {lhs.x / rhs, lhs.y / rhs};
}

template<class coord_t>
inline constexpr vec2<coord_t>& operator/=(
    vec2<coord_t>& lhs,
    coord_t rhs
){
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

template<class coord_t>
inline constexpr bool operator==(
    const vec2<coord_t>& lhs, 
    const vec2<coord_t>& rhs
){
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

template<class coord_t>
inline constexpr bool operator!=(
    const vec2<coord_t>& lhs, 
    const vec2<coord_t>& rhs
){
    return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}
