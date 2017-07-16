//
//  token.hpp
//  derpcalc
//
//  Created by Raghav on 7/11/17.
//  Copyright © 2017 WarpDev. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <regex>

void tokenise(std::string, std::vector< std::pair< std::string, char > > *);

#endif /* token_hpp */
