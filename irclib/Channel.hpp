//==============================================================================
//
//	Channel.hpp:
//	
//
//		
//		
//
//==============================================================================

#if !defined(IRCLIB_CHANNEL_HPP_INCLUDED)
#	 define	 IRCLIB_CHANNEL_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <list>

//	Boost dependencies ...

//	Project dependencies ...
#include "User.hpp"

namespace irclib
{
	class Channel
	{
		public:
			explicit Channel(const std::string & name);
			virtual ~Channel();

		private:

			typedef std::list<User>		Users;

			Users				m_Users;

	};

}

#endif

