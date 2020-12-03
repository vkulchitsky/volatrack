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

void SurfPoint::rotateBy(const quat &q)
{
    rotateBy(q.rotMat());
}

void SurfPoint::rotateBy(const mat4 &rotMat)
{
    vec4 rect4(m_rect, 0);
    rect4 = rotMat * rect4;
    m_rect = {rect4.x(), rect4.y(), rect4.z()};
}

real SurfPoint::angleWith(const SurfPoint &other)
{
    auto thisL2 = m_rect.lengthSquared();
    auto otherL2 = other.rect().lengthSquared();
    auto dotProduct = vec3::dotProduct(m_rect, other.rect());

    auto cosine = dotProduct * dotProduct / (thisL2 * otherL2);

    return std::acos(cosine);
}

std::vector<SurfPoint> SurfPoint::makeGrid(Size dim)
{
    std::vector<SurfPoint> res;

    for (Index i = 0; i < dim; ++i)
    {
        for (Index j = 0; j < dim; ++j)
        {
            for (Index k = 0; k < dim; ++k)
            {
                if (i > 0 && i < dim - 1)
                {
                    if (j > 0 && j < dim - 1)
                    {
                        if (k > 0 && k < dim - 1) continue;
                    }
                }

                SurfPoint sp((i + 0.5) / dim, (j + 0.5) / dim, (k + 0.5) / dim);
                sp.normalize();
                res.push_back(sp);
            }
        }
    }

    return res;
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
