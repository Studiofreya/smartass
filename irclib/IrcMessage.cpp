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


namespace irclib
{


	IrcMessage::IrcMessage(
		const std::string & command, 
		const std::string & prefix, 
		ParamType && parameters,
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

	bool IrcMessage::operator==(const IrcMessage & rhs) const
	{
		return 
			m_Command		== rhs.m_Command && 
			m_Prefix		== rhs.m_Prefix && 
			m_Parameters	== rhs.m_Parameters && 
			m_Trail			== rhs.m_Trail;
	}

	bool IrcMessage::operator!=(const IrcMessage & rhs) const
	{
		return ! (*this == rhs);
	}

	std::string IrcMessage::command() const
	{
		return m_Command;
	}

	std::string IrcMessage::origin() const
	{
		return m_Prefix;
	}

	const ParamType & IrcMessage::params() const
	{
		return m_Parameters;
	}

	std::string IrcMessage::trail() const
	{
		return m_Trail;
	}
}


