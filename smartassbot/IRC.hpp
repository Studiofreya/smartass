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
#include "IrcMessage.hpp"
#include "IrcParser.hpp"

namespace smartass
{

	class IRC
	{
		public:
			typedef std::function<void(const std::string &)> WriteFn;

		public:
			explicit IRC();
			virtual ~IRC();

		public:
			// What can we do with IRC?
			void nick(const std::string & name);
			void user(const std::string & name);
			void join(const std::string & channel);
			void privmsg(const std::string & recipient, const std::string & text);
			void part(const std::string & channel, const std::string & partmsg);
			void quit(const std::string & quitmsg);

		public:
			void readline(const std::string & line);
			void addIrcMessageHandler(const IrcMessageHandle & msg);

			void setWriteFn(const WriteFn & fn);

		private:
			void doHandlePing(const IrcMessage & original);

		private:	
			IrcParser				m_Parser;
			IrcMessageCommand		m_OnWrite;

			WriteFn					writeFn;

	};


}

#endif	// SMARTASS_IRC_HPP_INCLUDED

