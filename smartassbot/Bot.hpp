//==============================================================================
//
//	Bot.hpp:
//	
//
//		
//		
//
//==============================================================================

#if !defined(SMARTASS_BOT_HPP_INCLUDED)
#	 define	 SMARTASS_BOT_HPP_INCLUDED


//	System dependencies ...
#include <map>
#include <string>
#include <functional>

//	Boost dependencies ...

//	Project dependencies ...
#include "Connection.hpp"
#include "Config.hpp"
#include "IRC.hpp"
#include "CommandHandler.hpp"

namespace smartass
{

	class Bot
	{
		public:
			// Raw read handlers
			//typedef std::function<void(const std::string&)> RawReadHandler;
			//typedef std::vector<RawReadHandler>				RawReadHandlers;
			typedef CommandHandler<std::string>				RawReadCommand;
			typedef RawReadCommand::func_t					RawReadHandler;

			// Smart read handlers
			typedef std::function<void(const std::string &)>	SmartReadHandler;
			typedef std::map<std::string, SmartReadHandler>		SmartReadHandlers;
				  


		public:
			explicit Bot(const std::string & config);
			virtual ~Bot();


		public:

			void nick(const std::string& name);
			void join(const std::string& channels);
			void part(const std::string& chann);
			void invite(const std::string& name, const std::string& channel);
			void kick(const std::string& name, const std::string& channel, const std::string & msg);
			void op(const std::string& name, const std::string& channel);
			//void pong(const std::string& to);
			void message(const std::string& receiver, const std::string& msg);
			void quit(const std::string& msg);
			void waitForEvents();
			void addRawReadHandler(const RawReadHandler & rawhandle);

		private:
			void createBasicRawReadHandlers();
			void createBasicSmartReadHandlers();

		protected:
			void WriteHandler();
			void ReadHandler(const std::string& message);

			// Various handlers for various events
			RawReadCommand		m_RawReadHandlers;
			SmartReadHandlers	m_SmartReadHandlers;

			// Config
			Config				m_Config;

			// Our connection to the outside world
			Connection			m_Connection;

			// IRC
			IRC					m_IRC;
	};

}

#endif	// SMARTASS_BOT_HPP_INCLUDED
