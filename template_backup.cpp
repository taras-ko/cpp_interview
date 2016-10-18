#if 0
class NyxDevice : public UnixDeviceFile
{
private:
    nyx_device_type_t m_dt; // Device Type
    nyx_device_handle_t m_dh; // Device Handle

    void nyxTry(nyx_error_t err, const char* err_msg)
    {
        if (err != NYX_ERROR_NONE)
            throw NyxError(err, err_msg);
    }

public:
    NyxDevice(nyx_device_type_t dt = NYX_DEVICE_ILLEGAL_DEVICE)
        : m_dt{dt}
        , m_dh{nullptr}
    {}

    void open() override
    {
        nyxTry(
            nyx_device_open(NYX_DEVICE_KEYS, "Main", &m_dh),
            "nyx_device_open"
        );

        nyxTry(
            nyx_device_get_event_source(m_dh, &m_fd),
            "nyx_device_get_event_source"
        );
    }

    void close() override
    {
        nyxTry(
            nyx_device_close(m_dh),
            "nyx_device_close"
        );
    }
};
#endif


#if 0
typedef DeviceController<NyxDevice> NyxDeviceController;
class Accelerometer : public NyxDeviceController
{
private:
    struct {
        float x;
        float y;
        float z;
    } m_data;
public:
    static gboolean gIoHandler(GIOChannel *source, GIOCondition condition, gpointer ctx)
    {
        auto dev = static_cast<Accelerometer *>(ctx);

        dev->m_data = { 1.0, 2.0, 3.0 };
        dev->m_value = "1.0, 2.0, 3.0";

        //g_io_channel_read_to_end(source, nullptr, nullptr, nullptr );

        return TRUE;
    }
};
#endif

GIOError
_g_io_channel_read (GIOChannel *channel,
		   gchar      *buf,
		   gsize       count,
		   gsize      *bytes_read)
{
  GError *err = NULL;
  GIOError error;
  GIOStatus status;

  g_return_val_if_fail (channel != NULL, G_IO_ERROR_UNKNOWN);
  g_return_val_if_fail (bytes_read != NULL, G_IO_ERROR_UNKNOWN);

  if (count == 0)
    {
      if (bytes_read)
        *bytes_read = 0;
      return G_IO_ERROR_NONE;
    }

  g_return_val_if_fail (buf != NULL, G_IO_ERROR_UNKNOWN);

  status = channel->funcs->io_read (channel, buf, count, bytes_read, &err);

//  error = g_io_error_get_from_g_error (status, err);

  if (err)
    g_error_free (err);

  return error;
}


