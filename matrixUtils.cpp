#include "Matrix.hpp"

float   mtls::radians( const float deg ) {
    return (deg * DEG2RAD);
}

float   mtls::degrees( const float rad ) {
    return (rad * RAD2DEG);
}

vec3    mtls::createAxisUnitVec3( size_t index ) {
    vec3 res;
    res(index) = 1;
    return (res);
}

vec3    mtls::cross( const vec3& v0, const vec3& v1 ) {
    return vec3({
        v0[1] * v1[2] - v0[2] * v1[1],
        v0[2] * v1[0] - v0[0] * v1[2],
        v0[0] * v1[1] - v0[1] * v1[0]
    });
}

mat4    &mtls::scale( mat4& m, const vec3& s ) {
    const mat4    tmp({
        s[0], 0, 0, 0,
        0, s[1], 0, 0,
        0, 0, s[2], 0,
        0, 0, 0, 1
    });
    m = tmp * m;
    return (m);
}

mat4    &mtls::translate( mat4& m, const vec3& t ) {
    const mat4    tmp({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        t[0], t[1], t[2], 1
    });
    m = tmp * m;
    return (m);
}

/*  creates a view matrix that looks at a target from a position,
    could have issues with camera looking straight up or down.
*/
mat4    mtls::lookAt( const vec3& from, const vec3& to, const vec3& tmp ) {
    vec3 forward = normalize(from - to);
    vec3 right   = normalize(cross(tmp, forward));
    vec3 up      = cross(forward, right);
    return mat4({
                 right[0],          up[0],          forward[0], 0,
                 right[1],          up[1],          forward[1], 0,
                 right[2],          up[2],          forward[2], 0,
        -dot(right, from), -dot(up, from), -dot(forward, from), 1
    });
}

/* rotate around an offset position */
mat4    &mtls::rotate( mat4& m, const vec3& r, const vec3& offset ) {
    m = mtls::translate(m, offset);
    for (size_t i = 0; i < 3; ++i)
        if (r[i] != 0)
            m = mtls::rotate(m, static_cast<double>(r[i]), createAxisUnitVec3(i));
    m = mtls::translate(m, vec3({-offset[0], -offset[1], -offset[2]}));
    return (m);
}

/* rotate using a vec3 of type vec3({ 25, 0, 3 }) which will rotate 25 degrees on x axis and 3 on z axis */
mat4    &mtls::rotate( mat4& m, const vec3& r ) {
    for (size_t i = 0; i < 3; ++i)
        if (r[i] != 0)
            m = mtls::rotate(m, static_cast<double>(r[i]), createAxisUnitVec3(i));
    return (m);
}

/* rotate around the given unit axis r */
mat4    &mtls::rotate( mat4& m, double rad, const vec3& r ) { // use quaternions in the future
    const float sin = std::sin(rad);
    const float cos = std::cos(rad);
    const mat4    tmp({
        cos+r[0]*r[0]*(1-cos),      r[0]*r[1]*(1-cos)-r[2]*sin, r[0]*r[2]*(1-cos)+r[1]*sin, 0,
        r[1]*r[0]*(1-cos)+r[2]*sin, cos+r[1]*r[1]*(1-cos),      r[1]*r[2]*(1-cos)-r[0]*sin, 0,
        r[2]*r[0]*(1-cos)-r[1]*sin, r[2]*r[1]*(1-cos)+r[0]*sin, cos+r[2]*r[2]*(1-cos),      0,
        0,                          0,                          0,                          1
    });
    m = tmp * m;
    return (m);
}

mat4    mtls::inverse( const mat4& m ) {
    mat4    inv;
    float   det;

    inv(0) = m[5]*m[10]*m[15]-m[5]*m[11]*m[14]-m[9]*m[6]*m[15]+m[9]*m[7]*m[14]+m[13]*m[6]*m[11]-m[13]*m[7]*m[10];
    inv(4) = -m[4]*m[10]*m[15]+m[4]*m[11]*m[14]+m[8]*m[6]*m[15]-m[8]*m[7]*m[14]-m[12]*m[6]*m[11]+m[12]*m[7]*m[10];
    inv(8) = m[4]*m[9]*m[15]-m[4]*m[11]*m[13]-m[8]*m[5]*m[15]+m[8]*m[7]*m[13]+m[12]*m[5]*m[11]-m[12]*m[7]*m[9];
    inv(12) = -m[4]*m[9]*m[14]+m[4]*m[10]*m[13]+m[8]*m[5]*m[14]-m[8]*m[6]*m[13]-m[12]*m[5]*m[10]+m[12]*m[6]*m[9];
    inv(1) = -m[1]*m[10]*m[15]+m[1]*m[11]*m[14]+m[9]*m[2]*m[15]-m[9]*m[3]*m[14]-m[13]*m[2]*m[11]+m[13]*m[3]*m[10];
    inv(5) = m[0]*m[10]*m[15]-m[0]*m[11]*m[14]-m[8]*m[2]*m[15]+m[8]*m[3]*m[14]+m[12]*m[2]*m[11]-m[12]*m[3]*m[10];
    inv(9) = -m[0]*m[9]*m[15]+m[0]*m[11]*m[13]+m[8]*m[1]*m[15]-m[8]*m[3]*m[13]-m[12]*m[1]*m[11]+m[12]*m[3]*m[9];
    inv(13) = m[0]*m[9]*m[14]-m[0]*m[10]*m[13]-m[8]*m[1]*m[14]+m[8]*m[2]*m[13]+m[12]*m[1]*m[10]-m[12]*m[2]*m[9];
    inv(2) = m[1]*m[6]*m[15]-m[1]*m[7]*m[14]-m[5]*m[2]*m[15]+m[5]*m[3]*m[14]+m[13]*m[2]*m[7]-m[13]*m[3]*m[6];
    inv(6) = -m[0]*m[6]*m[15]+m[0]*m[7]*m[14]+m[4]*m[2]*m[15]-m[4]*m[3]*m[14]-m[12]*m[2]*m[7]+m[12]*m[3]*m[6];
    inv(10) = m[0]*m[5]*m[15]-m[0]*m[7]*m[13]-m[4]*m[1]*m[15]+m[4]*m[3]*m[13]+m[12]*m[1]*m[7]-m[12]*m[3]*m[5];
    inv(14) = -m[0]*m[5]*m[14]+m[0]*m[6]*m[13]+m[4]*m[1]*m[14]-m[4]*m[2]*m[13]-m[12]*m[1]*m[6]+m[12]*m[2]*m[5];
    inv(3) = -m[1]*m[6]*m[11]+m[1]*m[7]*m[10]+m[5]*m[2]*m[11]-m[5]*m[3]*m[10]-m[9]*m[2]*m[7]+m[9]*m[3]*m[6];
    inv(7) = m[0]*m[6]*m[11]-m[0]*m[7]*m[10]-m[4]*m[2]*m[11]+m[4]*m[3]*m[10]+m[8]*m[2]*m[7]-m[8]*m[3]*m[6];
    inv(11) = -m[0]*m[5]*m[11]+m[0]*m[7]*m[9]+m[4]*m[1]*m[11]-m[4]*m[3]*m[9]-m[8]*m[1]*m[7]+m[8]*m[3]*m[5];
    inv(15) = m[0]*m[5]*m[10]-m[0]*m[6]*m[9]-m[4]*m[1]*m[10]+m[4]*m[2]*m[9]+m[8]*m[1]*m[6]-m[8]*m[2]*m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (det == 0) // no possible inverse
        return (m);
    return (inv * (1.0 / det));
}

extern const mat4    mtls::mat4identity = mat4({
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
});

extern const mat3    mtls::mat3identity = mat3({
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
});

extern const mat2    mtls::mat2identity = mat2({
    1, 0,
    0, 1,
});
