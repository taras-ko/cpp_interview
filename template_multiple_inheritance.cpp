#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#include <glib.h>
#include <glib-unix.h>

#include <string>
#include <typeinfo>
#include <iostream>

#include <map>

using namespace std;

class File
{
protected:
    int m_fd {-1};
    const char* m_label {"undefined"};
public:
    File(const char* label)
        : m_label{label}
    {}
};

class FileOperations
{
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void read() = 0;
    ~FileOperations() = default;
};

class UnixDevice: public virtual File, public FileOperations
{
public:
    using File::File;
    void read() override
    {
        cout << __func__ << File::m_fd << endl;
    }
    void open() override
    {
        cout << __func__ << File::m_fd << endl;
    }

    void close() override
    {
        cout << __func__ << File::m_fd << endl;
    }
};

class PollerOperations
{
public:
    virtual void enable() = 0;
    virtual void disable() = 0;
    ~PollerOperations() = default;
};

class Poller: public virtual File, public PollerOperations
{
public:
    void enable() override
    {
        cout << __func__ << File::m_fd << endl;
    }

    void disable() override
    {
        cout << __func__ << File::m_fd << endl;
    }
};

class GlibPoller : public Poller
{
protected:
    GSource *m_source;

public:
    static gboolean onEvent(gpointer user_data)
    {
#if 1
        auto d = static_cast<UnixDevice *>(user_data);

        if (auto device = dynamic_cast<UnixDevice *>(d))
            device->read();
        else
            cerr << "couldn't cast\n";

#else
        cout << "callback\n";
#endif
        return TRUE;
    }

    void enable() override
    {
        Poller::enable();
        g_source_attach(m_source, nullptr);
    }
    void disable() override
    {
        Poller::disable();
        g_source_destroy(m_source);
    }
};

class PeriodicGlibPoller : public GlibPoller
{
public:
    void enable() override
    {
        m_source = g_timeout_source_new(500);

        if (auto device = dynamic_cast<UnixDevice *>(this))
            g_source_set_callback(m_source, (GSourceFunc) GlibPoller::onEvent, static_cast<gpointer>(device), nullptr);
        //else // throw

        GlibPoller::enable();
    }
};

template <class D, class P>
class EventDevice : public D, public P
{
public:
    void open() override
    {
        D::open();
        P::enable();
    }
    void close() override
    {
        P::disable();
        D::close();
    }
};

int main()
{
    UnixDevice d("sdlfkj");
#if 0
    EventDevice<UnixDevice, PeriodicGlibPoller> ed;

    ed.open();
    GMainLoop *loop = g_main_loop_new(nullptr, false);

    g_main_loop_run(loop);
#endif
}
