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
    // if (x, y, z) is the north pole, we transform by angle
    // (d*cos(a), d*sin(a), 1 - d2/2)
    vec3 dAlpha(d * std::cos(alpha), d * std::sin(alpha), 0);

    // multiply by (x, y, z) frame to get great circle from (x, y, z)
    // note: frame * (0, 0, 1) = (x, y, z), & dAlpha is very close to (0, 0, 1)
    // so m_rect changes by very little
    m_rect += frame() * dAlpha;

    // should already be pretty muc/*1 - 0.5 * d * d*/h normal, but just in case
    normalize();
}

mat3 SurfPoint::frame()
{
    // diag = sqrt(x2 + y2)
    auto diag = std::sqrt(rect().x() * rect().x() + rect().y() * rect().y());

    if (!diag) return mat3::identity();

    return
    {
        {
            // y/diag, -x/diag, 0
            rect().y() / diag, -rect().x() / diag, 0
        },
        {
            // xz/diag, yz/diag, -diag
            rect().x() * rect().z() / diag,
                    rect().y() * rect().z() / diag, -diag
        },
        {
            // x, y, z
            rect().x(), rect().y(), rect().z()
        }
    };
}
