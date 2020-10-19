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
    vec3 dAlpha(d * std::cos(alpha), d * std::sin(alpha), 1 - 0.5 * d * d);

    m_rect *= frame() * dAlpha;
    normalize();
}

mat3 SurfPoint::frame()
{
    auto diag = std::sqrt(rect().x() * rect().x() + rect().y() * rect().y());

    return
    {
        {
            rect().y() / diag, -rect().x() / diag, 0
        },
        {
            rect().x() * rect().z() / diag,
                    rect().y() * rect().z() / diag, -diag
        },
        {
            rect().x(), rect().y(), rect().z()
        }
    };
}
