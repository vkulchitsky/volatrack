#include "surfpoint.hpp"

using namespace volatrack;

SurfPoint::SurfPoint(const vec3& rect) : m_rect(rect) {}

SurfPoint::SurfPoint(real x, real y, real z) : m_rect(x, y, z) {}

vec3 SurfPoint::rect() const
{
    return m_rect;
}

void SurfPoint::setRect(const vec3 &rect)
{
    m_rect = rect.normalized();
}

void SurfPoint::setRect(real x, real y, real z)
{
    m_rect = vec3(x, y, z);
}

void SurfPoint::normalize()
{
    auto RR = m_rect.length();
    m_rect = m_rect / RR;
}

void SurfPoint::moveBy(real d, real alpha)
{
    m_rect *= C(d, alpha);
    normalize();
}

real SurfPoint::C(real x, real alpha)
{
    auto s = std::sin(alpha);
    auto c = std::cos(alpha);

    return 1 + (s + c) * x - 0.5 * x * x;
}
