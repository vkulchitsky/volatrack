#include "surfpoint.h"

using namespace volatrack;

SurfPoint::SurfPoint(const vec3& rect) : m_rect(rect) {}

SurfPoint::SurfPoint(real x, real y, real z) : m_rect(x, y, z) {}

vec3 SurfPoint::rect() const
{
    return m_rect;
}

void SurfPoint::setRect(const vec3 &rect)
{
    m_rect = rect;
}

void SurfPoint::setRect(real x, real y, real z)
{
    m_rect = {x, y, z};
}

void SurfPoint::normalize()
{
    auto RR = m_rect.length();
    m_rect = m_rect / RR;
}
