#include <iostream>
#include "boost/format.hpp"
#include "StartupParameters.hpp"
#include "DefaultTracer.hpp"
#include "SignalThread.hpp"

using namespace SynerEdge;

int main(int argc, char **argv)
{
	std::wcout << L"blocking SIGHUP" << std::endl;
	std::list<int> siglist;
	siglist.push_back(SIGHUP);
	SignalThread::blockSignals(siglist);

	try
	{
		DefaultTracer dt;

		boost::wformat argcfmt(L"argc: %d");
		argcfmt % argc;
		std::wcout << argcfmt << std::endl;
		StartupParameters *startUp = StartupParameters::instance();
		std::wcout << L"Storing startup args" << std::endl;
		startUp->storeStartupArgs(argc, argv);

		boost::wformat fmt(L"Trace directory: %s");

		std::wstring tracedir;
		if (startUp->env_find(L"TraceDir", tracedir))
		{
	 		fmt % tracedir;	
			std::wcout << fmt << std::endl;
		}

		int i = 0;
		for (StartupParameters::argsiterator itor = startUp->args_begin();
		    itor != startUp->args_end();
		    itor++)
		{
			boost::wformat fmt2(L"Arg[%d]=%s");
			fmt2 % i % (*itor);
			std::wcout << fmt2 << std::endl;
			++i;
		}

		std::wcout << "main id: " << pthread_self() << std::endl;

		
		SignalThread::instance(SIGUSR1);

		std::wstring str;
		std::wcin >> str;

		std::wcout << "all done" << std::endl;
	}
	catch (StartupParametersException &exp)
	{
		std::wcout << exp << std::endl;
	}

	return 0;
}
