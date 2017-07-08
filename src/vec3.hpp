#pragma once

template<class coord_t>
struct vec3{
    coord_t x, y, z;
};

template<class coord_t>
inline constexpr vec3<coord_t> operator-(const vec3<coord_t>& rhs){
    return {-rhs.x, -rhs.y, -rhs.z};
}

template<class coord_t>
inline constexpr vec3<coord_t>& operator+=(
    vec3<coord_t>& lhs, 
    const vec3<coord_t>& rhs
){
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

template<class coord_t>
inline constexpr vec3<coord_t>& operator-=(
    vec3<coord_t>& lhs,
    const vec3<coord_t>& rhs
){
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

template<class coord_t>
inline constexpr vec3<coord_t> operator+(
    const vec3<coord_t>& lhs, 
    const vec3<coord_t>& rhs
){
    return {
        lhs.x + rhs.x, 
        lhs.y + rhs.y, 
        lhs.z + rhs.z
    };
}

template<class coord_t>
inline constexpr vec3<coord_t> operator-(
    const vec3<coord_t>& lhs, 
    const vec3<coord_t>& rhs
){
    return {
        lhs.x - rhs.x, 
        lhs.y - rhs.y,
        lhs.z - rhs.z
    };
}

template<class coord_t>
inline constexpr vec3<coord_t> operator*(
    const vec3<coord_t>& lhs, 
    coord_t rhs
){
    return {
        lhs.x * rhs, 
        lhs.y * rhs,
        lhs.z * rhs
    };
}

template<class coord_t>
inline constexpr vec3<coord_t> operator*(
    coord_t lhs,
    const vec3<coord_t>& rhs
){
    return {
        rhs.x * lhs, 
        rhs.y * lhs,
        rhs.z * lhs
    };
}

template<class coord_t>
inline constexpr vec3<coord_t>& operator*=(
    vec3<coord_t>& lhs, 
    coord_t rhs
){
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

template<class coord_t>
inline constexpr vec3<coord_t> operator/(
    const vec3<coord_t>& lhs, 
    coord_t rhs
){
    return {
        lhs.x / rhs, 
        lhs.y / rhs,
        lhs.z / rhs
    };
}

template<class coord_t>
inline constexpr vec3<coord_t>& operator/=(
    vec3<coord_t>& lhs,
    coord_t rhs
){
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
}

template<class coord_t>
inline constexpr bool operator==(
    const vec3<coord_t>& lhs, 
    const vec3<coord_t>& rhs
){
    return (lhs.x == rhs.x) 
        && (lhs.y == rhs.y)
        && (lhs.z == rhs.z);
}

template<class coord_t>
inline constexpr bool operator!=(
    const vec3<coord_t>& lhs, 
    const vec3<coord_t>& rhs
){
    return (lhs.x != rhs.x) 
        || (lhs.y != rhs.y)
        || (lhs.z != rhs.z);
}
