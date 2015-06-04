//==============================================================================
//
//	IRC.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "IRC.hpp"

//	System dependencies ...

//	Boost dependencies ...

//	Ogre dependencies ...

//	Project dependencies ...
#include "IrcParser.hpp"


namespace smartass
{

	class IRC::impl
	{
		public:
			explicit impl(){}
			virtual ~impl(){}

		public:
			void readline(const std::string & line)
			{
				m_Parser.parseLine(line);
			}

		private:
			IrcParser	m_Parser;
	};


	IRC::IRC()
		: m_Impl(new impl())
	{

	}

	IRC::~IRC()
	{

	}

	void IRC::readline(const std::string & line)
	{
		m_Impl->readline(line);
	}

}


