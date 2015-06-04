//==============================================================================
//
//	Connection.hpp:
//	
//
//		
//		
//
//==============================================================================

#if !defined(SMARTASS_CONNECTION_HPP_INCLUDED)
#	 define	 SMARTASS_CONNECTION_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <functional>		 // Move to impl

//	Boost dependencies ...
#include <boost/asio.hpp>	 // Move to impl

//	Project dependencies ...

namespace smartass 
{

	typedef std::function<void(const std::string&)>		ReadHandler;
	typedef std::function<void(void)>					WriteHandler;

	class Connection
	{
		public:
			Connection();
			Connection(const std::string& addr, const std::string& port);

			void connect();
			void connect(const std::string& addr, const std::string& port);
			void write(const std::string& content);
			void read(const boost::system::error_code& error, std::size_t);

			void setReadHandler(const ReadHandler& handler);
			void setWriteHandler(const WriteHandler& handler);

			void run();
			void close();
			bool alive() const;

		private:
			void async_read();

		private:
			std::string						m_Address;
			std::string						m_Port;

			boost::asio::io_service			m_Io;
			boost::asio::ip::tcp::socket	m_Socket;

			ReadHandler						m_ReadHandler;
			WriteHandler					m_WriteHandler;

			std::array<char, 4096>			m_ReadBuffer;
	};

} 

#endif	// SMARTASS_CONNECTION_HPP_INCLUDED

