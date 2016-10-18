#include <iostream>
#include <sstream>

class Logger {
private:
    std::stringstream m_buf;
    std::ostream& m_out;
    std::string m_fmt;
    static Logger m_dbg,
                  m_err,
                  m_log;
    Logger(std::ostream& out, const std::string& fmt = "")
        : m_out(out)
        , m_fmt{fmt}
    {}
public:

    Logger(Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;

    static Logger& Dbg()
    {
        return m_dbg;
    }

    static Logger& Err()
    {
        return m_err;
    }

    static Logger& Log()
    {
        return m_log;
    }

    typedef Logger& (*ManipulatorFun)(Logger&);

    Logger& operator<<(ManipulatorFun fun)
    {
        return fun(*this);
    }

    static Logger& endl(Logger& logger)
    {
        logger.m_out
            << logger.m_fmt
            << logger.m_buf.str()
            << std::endl;

        logger.m_buf.str("");

        return logger;
    }

    template <class T>
    friend Logger& operator<< (Logger& logger, const T& x);
};

template <class T>
Logger& operator<< (Logger& logger, const T& x)
{
    logger.m_buf << x;
    return logger;
}

Logger Logger::m_dbg{std::cout, "Dbg: "},
       Logger::m_err{std::cerr, "Error: "},
       Logger::m_log{std::clog, "Log: "};

#define dbg Logger::Dbg()
#define err Logger::Err()
#define log Logger::Log()

int main()
{
    dbg << "hello" << " world" << Logger::endl;
    err << "hello" << " world" << Logger::endl;
    log << "hello" << " world" << Logger::endl;

}
