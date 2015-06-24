//==============================================================================
//
//	CommandHandler.hpp:
//	
//
//		Handles commands
//		
//
//==============================================================================

#if !defined(SMARTASS_COMMANDHANDLER_HPP_INCLUDED)
#	 define	 SMARTASS_COMMANDHANDLER_HPP_INCLUDED


//	System dependencies ...
#include <functional>
#include <list>

//	Boost dependencies ...

//	Project dependencies ...


namespace irclib
{
	using namespace std::placeholders;


	template<typename T>
	class CommandHandler
	{
		public:
			typedef	T										msg_t;
			typedef typename std::function<void(const T &)>	func_t;
			typedef typename std::list<func_t>				list_t;

		public:
			explicit CommandHandler()
				: m_Handlers()
			{
			}

			// Add
			void addHandle(const func_t & f)
			{
				m_Handlers.push_back(f);
			}

			// Remove
			void removeHandle(const func_t & f)
			{
				m_Handlers.remove(f);
			}

			// Execute
			void operator()(const msg_t & msg) const
			{
				for(const auto & h : m_Handlers)
				{
					h(msg);
				}
			}


		private:

			list_t		m_Handlers;

	};

}

#endif	// SMARTASS_COMMANDHANDLER_HPP_INCLUDED

