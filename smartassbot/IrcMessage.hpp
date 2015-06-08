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
#include <vector>
#include <functional>

//	Boost dependencies ...

//	Project dependencies ...
#include "CommandHandler.hpp"


namespace smartass
{

	class IrcMessage
	{
		public:
			explicit IrcMessage(
				const std::string & command = "", 
				const std::string & prefix = "", 
				const std::string & parameters = "", 
				const std::string & trail = "");

			virtual ~IrcMessage();

		public:
			explicit operator bool() const;

			// Details
			std::string command()	const;
			std::string origin()	const;
			std::string params()	const;
			std::string trail()		const;

		private:
			std::string m_Command;
			std::string m_Prefix;
			std::string m_Parameters;
			std::string m_Trail;
	};

	// Our messages
	typedef CommandHandler<IrcMessage>					IrcMessageCommand;
	typedef IrcMessageCommand::func_t					IrcMessageHandle;
}

#endif

