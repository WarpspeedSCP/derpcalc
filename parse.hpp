//
//  parse.hpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp

#include <boost/unordered_map.hpp>
#include <boost/variant.hpp>

#include <stack>
#include <string>
#include <vector>
#include <utility>

void parse(const std::vector<std::pair<std::__cxx11::string, char> > & , std::vector< std::string > *);

#endif /* parse_hpp */
