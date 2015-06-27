//==============================================================================
//
//	MultiSplit.hpp:
//	
//
//		Split a string with a delimiter of 1 or more characters.
//		
//
//==============================================================================

#if !defined(MULTISPLIT_HPP_INCLUDED)
#	 define	 MULTISPLIT_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <vector>

//	Boost dependencies ...

//	Project dependencies ...


namespace irclib
{
    // Not completely tested, use with caution ...
    template<typename STR>
    void split(std::vector<STR> & out, const STR & in, const STR & delimiter)
    {
        const auto npos = STR::npos;
        const auto delsize = delimiter.size();
        size_t offset = 0;
        size_t endpos = 0;
        size_t len = 0;

        do 
        {
            endpos = in.find(delimiter, offset);
            STR tmp;

            if (endpos != npos)
            {
                len = endpos - offset;
                tmp = in.substr(offset, len);
                out.push_back(tmp);

                // Prepare next round
                offset = endpos + delsize;
            }
            else
            {
                // Final, or nothing found
                tmp = in.substr(offset);
                out.push_back(tmp);
                break;
            }

        } 
        while (endpos != npos);
        
    }
}

#endif

