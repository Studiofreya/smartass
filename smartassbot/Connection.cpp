//==============================================================================
//
//	Connection.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "Connection.hpp"

//	System dependencies ...
#include <stdexcept>
#include <thread>
#include <functional>

//	Boost dependencies ...
#include <boost/bind.hpp>

//	Project dependencies ...
#include "Logger.hpp"


namespace smartass 
{
	Connection::Connection() 
		: m_Socket(m_Io)
	{

	}

	Connection::Connection(const std::string& addr, const std::string& port) 
		: m_Address(addr)
		, m_Port(port)
		, m_Socket(m_Io)
	{
		connect();
	}


	void Connection::connect()
	{
		boost::asio::ip::tcp::resolver resolver(m_Io);
		boost::asio::ip::tcp::resolver::query query(m_Address, m_Port);
		boost::system::error_code error = boost::asio::error::host_not_found;

		auto iter = resolver.resolve(query);
		decltype(iter) end;

		while (iter != end) 
		{
			if (!error)
			{
				break;
			}

			m_Socket.close();
			logLine("Info", "Trying to connect: " + m_Address + ":" + m_Port);

			m_Socket.connect(*iter++, error);

			if (error)
			{
				logLine("ERROR", error.message());
			}
		}

		if (error)
		{
			throw std::runtime_error(error.message());
		}

		logLine("Info", "Connected!");
	}

	void Connection::connect(const std::string & addr, const std::string & port)
	{
		m_Address = addr;
		m_Port = port;

		connect();
	}

	void Connection::run()
	{
		std::thread write_handler_thread(m_WriteHandler);

		async_read();

		m_Io.run();
		write_handler_thread.join();
	}

	bool Connection::alive() const
	{
		return m_Socket.is_open();
	}

	void Connection::close()
	{
		logLine("INFO", "Closing connection to " + m_Address + ":" + m_Port);

		m_Socket.close();
		m_Io.stop();
	}


	void Connection::write(const std::string& content)
	{
		logLine("WRITE", content);
		boost::asio::write(m_Socket, boost::asio::buffer(content + "\r\n"));
	}

	void Connection::read(const boost::system::error_code& error, std::size_t count)
	{
		if (error)
		{
			// Got error...
			logLine("ERROR", "Connection said something..." + error.message());

			if (
				error == boost::asio::error::connection_reset ||
				error == boost::asio::error::broken_pipe ||
				error == boost::asio::error::not_found
				)
			{
				connect();
			}
			else
			{
				close();
			}
		}
		else
		{
			m_ReadHandler(std::string(m_ReadBuffer.data(), count));

			async_read();
		}
	}

	void Connection::setReadHandler(const ReadHandler& handler)
	{
		m_ReadHandler = handler;
	}

	void Connection::setWriteHandler(const WriteHandler& handler)
	{
		m_WriteHandler = handler;
	}

	void Connection::async_read()
	{
		m_Socket.async_read_some(boost::asio::buffer(m_ReadBuffer),
			boost::bind(&Connection::read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
			)
		);
	}

}

