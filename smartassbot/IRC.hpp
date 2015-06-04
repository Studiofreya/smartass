//==============================================================================
//
//	IRC.hpp:
//	
//
//		
//		
//
//==============================================================================

#if !defined(SMARTASS_IRC_HPP_INCLUDED)
#	 define	 SMARTASS_IRC_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <memory>

//	Boost dependencies ...

//	Ogre dependencies ...

//	Project dependencies ...

namespace smartass
{

	class IRC
	{
		public:
			explicit IRC();
			virtual ~IRC();

		public:
			void readline(const std::string & line);

		private:	
			class impl;
			std::unique_ptr<impl>	m_Impl;

	};


}

#endif	// SMARTASS_IRC_HPP_INCLUDED

