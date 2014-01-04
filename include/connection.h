/**
 *  Class describing a mid-level Amqp connection
 * 
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace AMQP {

/**
 *  Class definition
 */
class Connection
{
private:
    /**
     *  The actual implementation
     *  @var    ConnectionImpl
     */
    ConnectionImpl _implementation;

public:
    /**
     *  Construct an AMQP object based on full login data
     * 
     *  The first parameter is a handler object. This handler class is
     *  an interface that should be implemented by the caller.
     * 
     *  @param  handler         Connection handler
     *  @param  login           Login data
     */
    Connection(ConnectionHandler *handler, const Login &login) : _implementation(this, handler, login) {}

    /**
     *  Construct an AMQP object with default login data
     *  @param  handler         Connection handler
     */
    Connection(ConnectionHandler *handler) : _implementation(this, handler) {}

    /**
     *  Destructor
     */
    virtual ~Connection() {}

    /**
     *  Parse the buffer into a recognized frame
     *  
     *  Every time that data comes in on the connection, you should call this method to parse
     *  the incoming data, and let it handle by the AMQP library. This method returns the number
     *  of bytes that were processed.
     *
     *  If not all bytes could be processed because it only contained a partial frame, you should
     *  call this same method later on when more data is available. The AMQP library does not do
     *  any buffering, so it is up to the caller to ensure that the old data is also passed in that
     *  later call.
     *
     *  @param  buffer      buffer to decode
     *  @param  size        size of the buffer to decode
     *  @return             number of bytes that were processed
     */
    size_t parse(char *buffer, size_t size)
    {
        return _implementation.parse(buffer, size);
    }
    
    /**
     *  Close the connection
     *  This will close all channels
     *  @return bool
     */
    bool close()
    {
        return _implementation.close();
    }

    /**
     *  Set the Quality of Service (QOS) of the entire connection
     *  @param  prefetchSize        maximum size (in octets) of messages to be prefetched
     *  @param  prefetchCount       maximum number of messages to prefetch
     *  @return bool                whether the Qos frame is sent.
     */
    bool setQos(uint32_t prefetchSize, uint16_t prefetchCount)
    {
        return _implementation.setQos(prefetchSize, prefetchCount);
    }
    
    /**
     *  Some classes have access to private properties
     */
    friend class ChannelImpl;
};

/**
 *  End of namespace
 */
}
