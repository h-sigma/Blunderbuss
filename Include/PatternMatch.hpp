//
// Created by harshdeep on 24/10/19.
//

#ifndef BLUNDERBUSS_PATTERNMATCH_HPP
#define BLUNDERBUSS_PATTERNMATCH_HPP

#include <vector>
#include <functional>

template<typename ENUM>
class PatternMatch
{
public:
    PatternMatch() = default;
    template<typename Func, ENUM ...Enums> void bindFunc(Func);
    void match(ENUM);
    template<ENUM e> void reset();
private:
    std::vector<std::function<void(ENUM)>> mMappings;
};

template<typename ENUM>
void PatternMatch<ENUM>::match(ENUM e) {
    for(auto& mapping : mMappings)
    {
        mapping(e);
    }
}

template<typename ENUM>
template<ENUM e>
void PatternMatch<ENUM>::reset() {
    for(auto& mapping : mMappings)
    {
        mapping(e);
    }
}

template<typename ENUM>
template<typename Func, ENUM... Enums>
void PatternMatch<ENUM>::bindFunc(Func func) {
    constexpr int count = sizeof...(Enums);
    static_assert(count > 0);
    mMappings.push_back([count, func](ENUM val){
        static ENUM pattern[count] {Enums...};
        static int toBeMatched = 0;
        bool itMatches = (val == pattern[toBeMatched]);
        if(itMatches)
        {
            toBeMatched++;
        }
        else
        {
            if(toBeMatched != 0 && pattern[toBeMatched - 1] == val && toBeMatched != count)
            {

            }
            else if(val == pattern[0])
            {
                toBeMatched = 1;
            }
            else
            {
                toBeMatched = 0;
            }
        }
        if(toBeMatched == count)
            func();
    });
}


#endif //BLUNDERBUSS_PATTERNMATCH_HPP
