//==============================================================================
//
//	Bot.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "Bot.hpp"

//	System dependencies ...
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

//	Boost dependencies ...
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

//	Project dependencies ...
#include "Logger.hpp"
#include "Connection.hpp"

namespace smartass 
{

	Bot::Bot(const std::string& configfile)
		: m_RawReadHandlers()
		, m_SmartReadHandlers()
		, m_Config(configfile)
		, m_Connection()
	{
		createBasicRawReadHandlers();
		createBasicSmartReadHandlers();

		m_Connection.setWriteHandler([&]() 
		{
			WriteHandler(); 
		});

		m_Connection.setReadHandler([&](const std::string& msg) 
		{
			ReadHandler(msg);
		});

		// Connect to server
		m_Connection.connect(m_Config.server(), m_Config.port());

		nick(m_Config.nick());
		join(m_Config.channels());

	}

	Bot::~Bot()
	{
	}


	void Bot::nick(const std::string& name)
	{
		m_Connection.write(std::string("NICK ") + name);
		m_Connection.write(std::string("USER ") + name + " * * :" + name);
	}

	void Bot::join(const std::string& channel, std::string key)
	{
		std::string cmd = std::string("JOIN ") + channel + " " + key;

		m_Connection.write(cmd);
	}

	void Bot::part(const std::string& channel)
	{
		std::string cmd = std::string("PART ") + channel;

		m_Connection.write(cmd);
	}

	void Bot::invite(const std::string& name, const std::string& channel)
	{
		std::string cmd = std::string("INVITE ") + name + " " + channel;

		m_Connection.write(cmd);
	}

	void Bot::kick(const std::string& name, const std::string& channel, const std::string & msg)
	{
		std::string cmd = std::string("KICK " + channel + " " + name);

		if ( ! msg.empty() )
		{
			cmd += " :" + msg;
		}

		m_Connection.write(cmd);
	}

	void Bot::op(const std::string& name, const std::string& channel)
	{
		std::string cmd = std::string("MODE ") + channel + " +o " + name;

		m_Connection.write(cmd);
	}

	void Bot::pong(const std::string& to)
	{
		std::string cmd = std::string("PONG ") + to;

		m_Connection.write(cmd);
	}

	void Bot::message(const std::string& receiver, const std::string& msg)
	{
		std::string cmd = std::string("PRIVMSG ") + receiver + " :" + msg;

		m_Connection.write(cmd);
	}

	void Bot::quit(const std::string& msg)
	{
		std::string cmd = std::string("QUIT :") + msg;

		m_Connection.write(cmd);
		m_Connection.close();
	}

	void Bot::waitForEvents()
	{
		m_Connection.run();
	}

	void Bot::addRawReadHandler(const RawReadHandler & func)
	{
		m_RawReadHandlers.push_back(func);
	}

	void Bot::createBasicRawReadHandlers()
	{
		// Debug the client and server
		auto serverDebugHandler = [&](const std::string & message)
		{
			// Just print whatever the server says to us
			logLine("READ ", message);
			//std::cout << "DebugRead: " << message << std::endl;
		};

		addRawReadHandler(serverDebugHandler);


		// Bridge between raw and smart handlers
		auto smartRawBridgeHandler = [&](const std::string & message)
		{
			m_IRC.readline(message);
		};

		addRawReadHandler(smartRawBridgeHandler);



		// Create basic raw handlers
		addRawReadHandler([&](const std::string& m)
		{
			std::istringstream iss(m);
			std::string from, type, to, msg;

			iss >> from >> type >> to >> msg;

			if (msg == ":!time") {
				std::time_t now = std::chrono::system_clock::to_time_t(
					std::chrono::system_clock::now());

				message(to, std::ctime(&now));
			}
		});

		addRawReadHandler([&](const std::string& m)
		{
			std::istringstream iss(m);
			std::string type, to, text;

			iss >> type;

			if (type == "PING") {
				text = "";
				while ((iss >> to)) {
					text += to + " ";
				}

				pong(text);
			}
		});

		addRawReadHandler([&](const std::string& m)
		{
			std::istringstream iss(m);
			std::string from, type, to, msg, text;

			iss >> from >> type >> to >> msg;

			if (msg == ":!echo") {
				text = "";
				while ((iss >> msg)) {
					text += msg + " ";
				}

				if (text != "") {
					message(to, text);
				}
			}
		});

	}

	void Bot::createBasicSmartReadHandlers()
	{

	}


	void Bot::WriteHandler()
	{
		std::string line, comm, msg, chann;

		while (m_Connection.alive())
		{
			std::getline(std::cin, line);
			std::istringstream iss(line);

			iss >> comm;

			if (comm == "/n")
			{
				iss >> comm;
				nick(comm);
			}
			else if (comm == "/j")
			{
				iss >> comm;
				join(comm);
			}
			else if (comm == "/m")
			{
				iss >> comm;
				msg = iss.str();
				msg.erase(0, 4+comm.size());
				message(comm, msg);
			}
			else if (comm == "/q")
			{
				iss >> comm;
				quit(comm);
			}
			else if (comm == "/op")
			{
				iss >> comm >> chann;
				op(comm, chann);
			}
		}
	}

	void Bot::ReadHandler(const std::string& message)
	{
		// Working buffer
		auto msg = message;

		// Remove carriage returns
		boost::replace_all(msg, "\r", "");

		// Split message into lines (commands) and send them
		std::vector<std::string> lines;
		boost::split(lines, msg, boost::is_any_of("\n"));

		// For each line ...
		for (auto & line : lines)
		{
			boost::trim(line);

			if (line.empty())
			{
				continue;
			}

			// ... do every message handler
			for (const auto & func: m_RawReadHandlers)
			{
				func(line);
			}

		}

	}

}
