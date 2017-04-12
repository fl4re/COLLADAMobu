//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

int main () {
    using namespace boost::numeric::ublas;
    matrix<double> m (3, 3);
    matrix_range<matrix<double> > mr (m, range (0, 3), range (0, 3));
    for (unsigned i = 0; i < mr.size1 (); ++ i)
        for (unsigned j = 0; j < mr.size2 (); ++ j)
            mr (i, j) = 3 * i + j;
    std::cout << mr << std::endl;
}
