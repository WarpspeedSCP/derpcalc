//
//  parse.hpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp

#include "real.hpp"

#include "include/boost/unordered_map.hpp"
#include "include/boost/variant.hpp"
#include "include/boost/function.hpp"

#include <stack>
#include <string>
#include <vector>
#include <utility>


void parse(const std::vector< std::pair< std::string, char > > * , std::vector< std::string > *);

#endif /* parse_hpp */
