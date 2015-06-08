//==============================================================================
//
//	IrcMessage.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "IrcMessage.hpp"

//	System dependencies ...

//	Boost dependencies ...

//	Ogre dependencies ...

//	Project dependencies ...


namespace smartass
{


	IrcMessage::IrcMessage(
		const std::string & command, 
		const std::string & prefix, 
		const std::string & parameters,
		const std::string & trail)
		: m_Command(command)
		, m_Prefix(prefix)
		, m_Parameters(parameters)
		, m_Trail(trail)
	{
	}

	IrcMessage::~IrcMessage()
	{
	}

	IrcMessage::operator bool() const
	{
		return ! m_Command.empty();
	}

	std::string IrcMessage::command() const
	{
		return m_Command;
	}

	std::string IrcMessage::origin() const
	{
		return m_Prefix;
	}

	std::string IrcMessage::params() const
	{
		return m_Parameters;
	}

	std::string IrcMessage::trail() const
	{
		return m_Trail;
	}
}


