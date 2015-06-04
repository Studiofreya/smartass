//==============================================================================
//
//	IrcMessage.hpp:
//	
//
//		Basic message from an IRC network
//		
//
//==============================================================================

#if !defined(SMARTASS_IRCMESSAGE_HPP_INCLUDED)
#	 define	 SMARTASS_IRCMESSAGE_HPP_INCLUDED


//	System dependencies ...
#include <string>

//	Boost dependencies ...

//	Project dependencies ...


namespace smartass
{

	class IrcMessage
	{
		public:
			explicit IrcMessage(
				const std::string & command, 
				const std::string & prefix, 
				const std::string & parameters, 
				const std::string & trail);

			virtual ~IrcMessage();

		public:
			std::string command() const;


		private:
			std::string m_Command;
			std::string m_Prefix;
			std::string m_Parameters;
			std::string m_Trail;
	};

}

#endif

