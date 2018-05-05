#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"
#include <vector>

class hitable_list : public hitable {
    std::vector<hitable*> list;
public:
    using size_type = decltype(list)::size_type;
    hitable_list() = default;
    hitable_list(size_type length) : list(length) {}
    hitable*& operator[](size_type i) { return list[i]; }
    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

inline bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    bool hit_any = false;
    float t_closest = t_max;
    hit_record tmp;
    for (hitable* const hp : list) {
        if (hp->hit(r, t_min, t_closest, tmp)) {
            hit_any = true;
            t_closest = tmp.t;
            rec = tmp;
        }
    }
    return hit_any;
}

#endif // HITABLE_LIST_H
