//==============================================================================
//
//	IRC.hpp:
//	
//
//		Just another IRC parser
//
//==============================================================================

#if !defined(SMARTASS_IRC_HPP_INCLUDED)
#	 define	 SMARTASS_IRC_HPP_INCLUDED


//	System dependencies ...
#include <string>

//	Boost dependencies ...

//	Project dependencies ...


namespace smartass
{

	class IRC
	{
		public:
			explicit IRC();
			virtual ~IRC();

		public:
			void parseLine(const std::string & message);

		private:

	};

}

#endif	// SMARTASS_IRC_HPP_INCLUDED

