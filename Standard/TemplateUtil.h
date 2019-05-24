//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_TEMPLATEUTIL_H
#define STANDARDDRIVER_TEMPLATEUTIL_H

namespace Standard {

    template <typename Type>
    inline void Swap(Type &a, Type &b) {
        Type c = a;
        a = b;
        b = c;
    }

}



#endif //STANDARDDRIVER_TEMPLATEUTIL_H
