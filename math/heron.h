#pragma once

#include "test/global_includes.h"

//begintemplate heron
//description Heron's formula calculator along with a checker for whether a point is inside of a triangle
template <typename S>
struct p {
    S x, y;
    friend istream& operator>>(istream& in, p& obj) { in >> obj.x >> obj.y; return in; }
    friend ostream& operator<<(ostream& out, const p obj) { out << "(x=" << obj.x << ", y=" << obj.y << ")"; return out; }
};
struct Heron {
    double prec;
    Heron(double prec0) : prec(prec0) {}
    bool roughlyEqual(double a, double b) {
        return abs(a - b) < prec;
    }
    template <typename T> double dis(p<T> a, p<T> b) { // Distance between line segment (a, b)
        T da = b.x - a.x, db = b.y - a.y;
        return sqrt(da * da + db * db);
    }
    template <typename T> double heron(p<T> a, p<T> b, p<T> c) { // Area of triangle (a, b, c)
        double da = dis(a, b), db = dis(b, c), dc = dis(a, c), semi = (da + db + dc) / 2.;
        return sqrt(semi * (semi - da) * (semi - db) * (semi - dc));
    }
    template <typename T> bool contains(p<T> a, p<T> b, p<T> c, p<T> pt, bool strict) { // Checks whether triangle (a, b, c) contains point pt
        double tot = heron(a, b, c), area1 = heron(a, b, pt), area2 = heron(b, c, pt), area3 = heron(a, c, pt);
        // debug(tot, a.x, a.y, b.x, b.y, c.x, c.y);
        return (!strict || (area1 != 0 && area2 != 0 && area3 != 0))
               && roughlyEqual(area1 + area2 + area3, tot);
    }
};
//endtemplate heron

//TODO: Heron's formula test