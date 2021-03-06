#ifndef SygStartupParameter_hh
#define SygStartupParameter_hh

#include <fstream>
#include <string>
#include <list>
#include <map>
#include <cassert>

#include "boost/utility.hpp"
#include "boost/thread.hpp"
#include "boost/thread/once.hpp"
#include "boost/thread/mutex.hpp"

#include "Observer.hpp"

namespace SynerEdge
{

class StartupParametersException
{
public:
	StartupParametersException(const std::wstring &msg) : _msg(msg) {}
	~StartupParametersException() {}

	std::wstring getMsg() const { return _msg; }
private:
	std::wstring _msg;
};

std::wostream &operator<<(std::wostream &out, const StartupParametersException &exp);

class StartupParameters : private boost::noncopyable, public Observable
{
public:
	typedef std::list<std::wstring>::const_iterator argsiterator;
	typedef std::map<std::wstring, std::wstring>::const_iterator enviterator;

	virtual ~StartupParameters();

	static StartupParameters *instance();

	ObservableEvent<BaseEventArgs> parametersWereReparsed;

	void storeStartupArgs(int argc, char **argv);
	void rereadEnvironment();

	argsiterator args_begin();
	argsiterator args_end();
	size_t args_count();

	bool env_find(const std::wstring &param, std::wstring &out);

	void reparseInputStream(Observable *obs, const int &signo);

private:
	StartupParameters();
	void parseInputStream(std::wifstream &env);

	static StartupParameters *_instance;
	static boost::once_flag _sentry;

	std::list<std::wstring> _args;
	std::map<std::wstring, std::wstring> _env;
	std::wstring _traceDir;
	boost::mutex _mtx;

	static void createInstance();

	// These methods intentionally left undefined
	StartupParameters(const StartupParameters &);
	StartupParameters &operator=(const StartupParameters &);
};

};

#endif
