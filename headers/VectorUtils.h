//
// Created by Patrick Tumulty on 5/17/22.
//

#ifndef RHC_VECTORUTILS_H
#define RHC_VECTORUTILS_H

#include <vector>
#include <queue>

class VectorUtils
{
public:
    /**
     * Remove common values shared between v1 and v2, from v1
     *
     * @tparam T type
     * @param v1 vector 1
     * @param v2 vector 2
     */
    template<class T>
    static void removeCommon(std::vector<T> * v1, const std::vector<T>& v2)
    {
        std::queue<T> q;

        for (const T& value : v2)
        {
            q.push(value);
        }

        while (!q.empty())
        {
            auto it = std::find(v1->begin(), v1->end(), q.front());
            if (it != v1->end())
            {
                v1->erase(it);
            }
            q.pop();
        }
    }
};


#endif //RHC_VECTORUTILS_H
