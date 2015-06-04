//==============================================================================
//
//	Config.hpp:
//	
//
//		Simple configuration parser for Smartass bot
//		
//
//==============================================================================

#if !defined(SMARTASS_CONFIG_HPP_INCLUDED)
#	 define	 SMARTASS_CONFIG_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <map>

//	Boost dependencies ...

//	Project dependencies ...


namespace smartass
{
	class Config
	{
		public:
			explicit Config(const std::string & filename);
			virtual ~Config();

		public:
			std::string server() const;
			std::string port() const;
			std::string nick() const;
			std::string channels() const;

		private:

			std::string getIfExists(const std::string & key) const;

		private:
			// Config
			typedef std::map<std::string, std::string>		ConfigItems;

			ConfigItems		m_Config;


	};

}

#endif	// SMARTASS_CONFIG_HPP_INCLUDED

