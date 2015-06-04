//==============================================================================
//
//	IrcParser.hpp:
//	
//
//		Just another IRC parser
//
//==============================================================================

#if !defined(SMARTASS_IRCPARSER_HPP_INCLUDED)
#	 define	 SMARTASS_IRCPARSER_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <functional>
#include <vector>
#include <map>

//	Boost dependencies ...

//	Project dependencies ...
#include "IrcMessage.hpp"


namespace smartass
{

	class IrcParser
	{
		public:
			typedef std::function<void(const IrcMessage &)>		IrcReadHandler;
			typedef std::vector<IrcReadHandler>					IrcReadHandlers;
			typedef std::map<std::string, IrcReadHandlers>		CommandDispatcher;

		public:
			explicit IrcParser();
			virtual ~IrcParser();

		public:
			void parseLine(const std::string & message);

			// All commands
			void addIrcReadHandler(const IrcReadHandler & handler);

			// Specific commands
			void addIrcCommandHandler(const std::string & cmd, const IrcReadHandler & handler);

		private:
			void doCommandDispatch(const IrcMessage & msg);

		private:

			IrcReadHandlers		m_Handlers;
			CommandDispatcher	m_CommandHandlers;
			

	};

}

#endif	// SMARTASS_IRC_HPP_INCLUDED

