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
	typedef std::vector<std::string> ParamType;

	class IrcMessage
	{

		public:
			explicit IrcMessage(
				const std::string & command = "", 
				const std::string & prefix = "", 
				ParamType && parameters = {}, 
				const std::string & trail = "");

			virtual ~IrcMessage();

		public:
			explicit operator bool() const;
			bool operator == (const IrcMessage & rhs) const;
			bool operator != (const IrcMessage & rhs) const;

			// Details
			std::string			command()	const;
			std::string			origin()	const;
			const ParamType		& params()	const;
			std::string			trail()		const;

		private:
			std::string			m_Command;
			std::string			m_Prefix;
			ParamType			m_Parameters;
			std::string			m_Trail;
	};

	// Our messages
	typedef CommandHandler<IrcMessage>					IrcMessageCommand;
	typedef IrcMessageCommand::func_t					IrcMessageHandle;
}

#endif

