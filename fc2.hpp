#ifdef __linux__
/**
 * @brief
 */
#ifndef FC2_HPP
#define FC2_HPP

/**
 * @brief versioning
 */
#define FC2_TEAM_VERSION_MAJOR 1
#define FC2_TEAM_VERSION_MINOR 0

/**
 * @brief buffer sizes
 * @todo do this last
 *
 * API responses can sometimes be very big. getMember&steam&history for example will always exceed the normal amount.
 * you can increase the buffer size by pre-defining FC2_TEAM_LARGE_BUFFER.
 *
 * you shouldn't always use FC2_TEAM_LARGE_BUFFER just because it's available. larger memory segments can increase allocation time.
 * depending on what the operation is, larger buffers can be slower if information is being searched. it depends on what your fc2 team project does in the end.
 * some systems handle larger memory segments differently than others. stick to what's modest.
 *
 * if you want to set custom sizes, you'll have to do it yourself via FC2_TEAM_CUSTOM_BUFFER
 */
#ifdef FC2_TEAM_LARGE_BUFFER
    #define FC2_TEAM_MAX_API_BUFFER (1000 * 10)
    #define FC2_TEAM_MAX_API_URL_SIZE (80 * 10)
    #define FC2_TEAM_MAX_LUA_BUFFER (1000 * 10)
#elif FC2_TEAM_SMALL_BUFFER
    #define FC2_TEAM_MAX_API_BUFFER (1000 / 2)
    #define FC2_TEAM_MAX_API_URL_SIZE (80 / 2)
    #define FC2_TEAM_MAX_LUA_BUFFER (1000 / 2)
#elif FC2_TEAM_CUSTOM_BUFFER
    /**
     * by defining this, you would generally write something like this before including fc2.hpp:
     * // #define FC2_TEAM_MAX_API_BUFFER 3500
     * etc...
     *
    */
#else
    #define FC2_TEAM_MAX_API_BUFFER (1000)
    #define FC2_TEAM_MAX_API_URL_SIZE (80)
    #define FC2_TEAM_MAX_LUA_BUFFER (1000)
    #define FC2_TEAM_MAX_PROCESS_NAME (260)
    #define FC2_TEAM_MAX_PATTERN_SIZE (160)
    #define FC2_TEAM_MAX_MEMORY_READ_SIZE (260)
    #define FC2_TEAM_MAX_IDENTIFIER_SIZE 128
#endif

    /// api request is the largest struct, base the size off of this | sizeof( 8 + sizeof( fc2::detail::requests::api ) )
#define FC2_TEAM_MAX_DATA_BUFFER ( 8 + sizeof( fc2::detail::requests::api ) )

/**
 * @brief inlining
 * @todo add more compiler support
 */
#ifdef FC2_TEAM_NO_INLINE
    #define FC2_TEAM_FORCE_INLINE
#else
#ifdef _WIN32
    #define FC2_TEAM_FORCE_INLINE __forceinline
#else
    #define FC2_TEAM_FORCE_INLINE inline __attribute__((__always_inline__))
#endif
#endif

/**
 * @brief error codes
 */
enum FC2_TEAM_ERROR_CODES
{
    /**
     * @brief no error
     */
    FC2_TEAM_ERROR_NO_ERROR,

    /**
     * universe4 needs to be open
     */
    FC2_TEAM_ERROR_NO_FC2_SOLUTION_OPEN,

    /**
     * memory failed to attach for some reason (permissions issue?)
     */
    FC2_TEAM_ERROR_MEMORY_FAILED_TO_ATTACH,
};

/**
 * @brief api request codes
 */
enum FC2_TEAM_REQUESTS : int
{
    FC2_TEAM_REQUESTS_NONE,
    FC2_TEAM_REQUESTS_PING,
    FC2_TEAM_REQUESTS_API,
    FC2_TEAM_REQUESTS_LUA,
    FC2_TEAM_REQUESTS_ATTACH,
    FC2_TEAM_REQUESTS_GET_MODULE,
    FC2_TEAM_REQUESTS_PATTERN,
    FC2_TEAM_REQUESTS_READ_MEMORY,
    FC2_TEAM_REQUESTS_CALL,
};

/**
 * @brief lua types for "call"
 */
enum FC2_LUA_TYPE : int
{
    FC2_LUA_TYPE_NONE,
    FC2_LUA_TYPE_BOOLEAN,
    FC2_LUA_TYPE_DOUBLE,
    FC2_LUA_TYPE_FLOAT,
    FC2_LUA_TYPE_INT,
    FC2_LUA_TYPE_STRING
};

/**
 * @brief includes
 */
#include <memory> /** std::unique_ptr **/
#include <thread> /** std::thread **/
#include <cstdio> /** printf **/
#include <vector> /** std::vector **/
#include <cstring> /** memcpy **/
#include <string> /** std::string **/
#include <variant> /** std::variant **/
#include <optional> /** std::optional **/

#ifdef __linux__
/**
 * @brief linux includes
 */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

/**
 * @brief shared memory key (do not modify)
 */
#define SHM_KEY 329032494
#else

#endif

namespace fc2
{
    namespace detail
    {
        enum FC2_TEAM_STATUS
        {
            /**
             * @brief still waiting for Universe4 to finish operation
             */
            FC2_TEAM_SERVER_PENDING,

            /**
             * @brief operation is completed
             */
            FC2_TEAM_SERVER_DONE,
        };

        namespace requests
        {
            /**
             * @brief ping pong
             */
            struct ping
            {
                unsigned long long ping;
                unsigned long long pong;
            };

            /**
             * @brief API request
             */
            struct api
            {
                char url[ FC2_TEAM_MAX_API_URL_SIZE ] {};
                char buffer[ FC2_TEAM_MAX_API_BUFFER ] {};
            };

            /**
             * @brief lua script
             */
            struct lua
            {
                char buffer[ FC2_TEAM_MAX_LUA_BUFFER ] {};
            };

            /**
             * @brief attach to process
             */
            struct attach
            {
                unsigned long id = 0;
                char name[ FC2_TEAM_MAX_PROCESS_NAME ] {};
                bool install_ipc = true;
                int status = 0;
            };

            /**
             * @brief get module
             */
            struct module
            {
                char name[ FC2_TEAM_MAX_PROCESS_NAME ] {};
                int partition = 0;
                int status = 0;

                unsigned long long base = 0;
                unsigned long long size = 0;
            };

            /**
             * @brief pattern scanning
             */
            struct pattern
            {
                char module[ FC2_TEAM_MAX_PROCESS_NAME ] {};
                char pattern[ FC2_TEAM_MAX_PATTERN_SIZE ] {};
                unsigned int offset = 0;
                bool is_x64 = true;
                bool relative = true;
                bool ds = false;

                unsigned long long result = 0;
            };

            /**
             * @brief read process memory
             */
            struct read_memory
            {
                unsigned long long address = 0;
                unsigned long long size = 0;
                unsigned long long bytes_read = 0;

                unsigned char data[ FC2_TEAM_MAX_MEMORY_READ_SIZE ] {};
            };

            struct call
            {
                char identifier[ FC2_TEAM_MAX_IDENTIFIER_SIZE ] {};
                FC2_LUA_TYPE typing = FC2_LUA_TYPE::FC2_LUA_TYPE_NONE;
                unsigned char data[ FC2_TEAM_MAX_MEMORY_READ_SIZE ] {};
            };
        }

        struct information
        {
            /**
             * @brief request ID / command ID
             */
            int id = 0;

            /**
             * @brief status
             */
            int status = FC2_TEAM_SERVER_PENDING;

            /**
             * @brief buffer
             */
            char data[ FC2_TEAM_MAX_DATA_BUFFER ] {};
        };

        class shm
        {
        public:
            /**
             * @brief shm id
             */
            int id = -1;

            /**
             * @brief last caught error
             */
            FC2_TEAM_ERROR_CODES last_error = FC2_TEAM_ERROR_NO_ERROR;

            /**
             * @brief data being sent/rec
             */
            void * data;

#ifdef __linux__
            /**
             * @brief semaphore mutex to prevent simultaneous operations
             */
            sem_t sem_mutex = {};
#endif

        public:
            FC2_TEAM_FORCE_INLINE shm()
            {
#ifdef __linux__
                /**
                 * @brief find server
                 */
                id = shmget( SHM_KEY, FC2_TEAM_MAX_DATA_BUFFER, 0666);

                if( id < 0 )
                {
                    /**
                     * @brief universe4 isn't open. cant connect to server.
                     */
                    last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_FC2_SOLUTION_OPEN;
                    return;
                }

                /**
                 * @brief attach to data
                 */
                data = shmat( id, nullptr, 0);
                if( (char *)data == (char*)-1 )
                {
                    /**
                     * @brief memory failed to attach
                     */
                    last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_MEMORY_FAILED_TO_ATTACH;
                    return;
                }

                /**
                 * @brief start semaphore
                 */
                sem_init(&sem_mutex, 1, 1);

                /**
                 * @brief set success
                 */
                last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR;
#endif
            }

        };

        class client
        {
        public:
            /**
             * @brief create our client
             * @return
             */
            FC2_TEAM_FORCE_INLINE static auto get()
            {
                /**
                 * @brief create object
                 */
                static auto obj = std::make_unique< shm >( );

                /**
                 * @brief get client
                 */
                static auto c = obj.get();

                /**
                 * @brief did something break
                */
                if( c->id < 0 || c->last_error != FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }
                return c;
            }

            /**
             * @brief send to universe4
             * @tparam t
             * @param id
             * @param req
             * @return
             */
            template< typename t >
            FC2_TEAM_FORCE_INLINE static auto send( int id, t req ) -> t
            {
                /**
                 * @brief get client
                 */
                auto c = get();

                /**
                 * @brief did something break
                */
                if( c->id < 0 || c->last_error != FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }

                /**
                 * @brief semaphore lock
                */
                sem_wait( &c->sem_mutex );

                /**
                 * @brief create new data with our request info
                 */
                detail::information data;
                data.id = id;
                memcpy( data.data, &req, sizeof( t ) );

                /**
                 * @brief send to universe4
                 */
                memcpy( c->data, &data, FC2_TEAM_MAX_DATA_BUFFER );

                /**
                 * @brief convert data
                 */
                auto information = reinterpret_cast< detail::information * >(c->data);

                /**
                 * @brief wait until completed
                 */
                while( information->status == FC2_TEAM_STATUS::FC2_TEAM_SERVER_PENDING ) {}

                /**
                 * @brief semaphore unlock
                */
                sem_post( &c->sem_mutex );

                /**
                 * @brief return data
                 */
                memcpy( &req, information->data, sizeof( t ) );
                return req;
            }
        };

        namespace helper
        {
            /**
             * @brief safely copy values
             * @param dest
             * @param src
             */
            FC2_TEAM_FORCE_INLINE static void safe_copy( char * dest, const char * src, const std::size_t size )
            {
                /**
                 * @brief prevent exceeding in length
                 */
                std::size_t l = strlen( src ) + 1;
                l = std::min( l, size );

                /**
                 * @brief cpy
                 */
                memcpy( dest, src, l);

                /**
                 * @brief null-terminator
                 */
                dest[ l - 1 ] = '\0';
            }

            FC2_TEAM_FORCE_INLINE static void safe_copy(char * dest, const std::string & src, const std::size_t size )
            {
                safe_copy(dest, src.c_str(), size );
            }
        }
    } // end detail

    /**
     * @brief this will return the time difference in Universe4 logs. if you want to test how fast fc2.hpp team is for you, use this.
     */
    FC2_TEAM_FORCE_INLINE static auto ping() -> void
    {
        detail::requests::ping data{};
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto epoch = now.time_since_epoch();
            auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();

            data.ping = ticks;
        }

        detail::client::send< detail::requests::ping >( FC2_TEAM_REQUESTS_PING, data );
    }

    /**
     * @brief if you don't feel like installing your own http library for the Web API, this can be useful.
     *
     * this does have a limit on the buffer size. simply be aware of that (see buffer size pre-definitions).
     * this method also does not parse the JSON data returned from the Web API, you will need to do that alone.
     *      - https://github.com/nlohmann/json (FC2 uses this library)
     *      - https://github.com/json-c/json-c (used this before for another project. prefer nlohmann)
     *
     * this is essentially a wrapper for:
     *      - https://constelia.ai/api.php?key=KEY&cmd=
     *      - the key value is automatically placed.
     *      - 'url' starts right after "cmd=" when you call this method.
     *
     * @code
     *
     *      fc2::api( "toggleScriptStatus&id=150" );
     *      fc2::api( "resetConfiguration" );
     *      fc2::api( "getMember&steam&history" ); <--- likely cause a size limit error in FC2. see buffer size predefs
     *      fc2::api( "getConfiguration" );
     *
     * @endcode
     *
     * @param url
     * @return
     */
    FC2_TEAM_FORCE_INLINE static auto api( const std::string & url ) -> std::string
    {
        detail::requests::api data;
        {
            detail::helper::safe_copy( data.url, url, sizeof data.url );
        }

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_API, data );
        return ret.buffer;
    }

    /**
     * @brief most behaviors from FC2 can be executed through Lua code honestly.
     *
     * this method will either create a dummy create or execute lua code on another actively running script.
     * FC2 team is designed to interact with FC2; doing basic requests and not caring about the return result should depend on this method.
     *
     * https://constelia.ai/sdk/FC2/
     *
     * @code
     * fc2::lua( "print( \"hello world \" )" );
     * fc2::lua( "fantasy.configuration():save()" ); // save our configuration to cloud (https://constelia.ai/sdk/FC2/modules/configuration/#save).
     * fc2::lua( R"(
     *      local input = fantasy.input()
     *      input:click( 1 ) -- left click
     *
     *      fantasy.log("we just left clicked!" )
     * )" );
     * @endcode
     *
     * @param code
     */
    FC2_TEAM_FORCE_INLINE static auto lua( const std::string & code ) -> void
    {
        detail::requests::lua data;
        {
            detail::helper::safe_copy( data.buffer, code, sizeof data.buffer );
        }

        detail::client::send( FC2_TEAM_REQUESTS_LUA, data );
    }

    /**
     * @brief makes Universe4 attach to a process. attachment process is different based on protection mode.
     * install_ipc is true by default. when true, FC2K or ZombieFC2 will automatically install itself if it hasn't been done already.
     *
     * @param value
     * @param install_ipc
     * @return
     */
    FC2_TEAM_FORCE_INLINE static auto attach( const std::variant< std::string, unsigned long> & value, bool install_ipc = true ) -> bool
    {
        detail::requests::attach data;
        {
            data.install_ipc = install_ipc;
        }

        /**
         * @brief deduce argument type and assign based on type
         */
        auto ret = std::visit( [&data] (auto && arg) {

            using t = std::decay_t< decltype( arg ) >;

            /**
             * @brief is std::string or unsigned long?
             */
            if constexpr( std::is_same_v< t, std::string > )
            {
                detail::helper::safe_copy( data.name, arg, sizeof data.name );
            }
            else if constexpr( std::is_same_v< t, unsigned long > )
            {
                data.id = arg;
            }

            /**
             * @brief send to universe4
             */
            return detail::client::send( FC2_TEAM_REQUESTS_ATTACH, data );
        }, value);

        return ret.status == 1;
    }

    /**
     * @brief gets a module from an attached process.
     *
     * sometimes with FC2K, the module size may not be returned or will be "0". this happens with Constellation4 as well. to fix this,
     * simply restart the attached process. this method will return also fail if there isn't an attached process.
     *
     * if you at one point, already called this method for a module, calling it again will always attempt to re-sync the base address and size.
     * this is different than how the lua module handles this (modules are cached already).
     *
     * @param name
     * @param partition
     * on Linux, sometimes shared libraries are stored in different permission spaces. this parameter references the index of the mapped layout.
     * if you don't understand, don't worry about it. if you need help for Linux and this method, ask on forums.
     *
     * Windows users should always ignore this parameter.
     *
     * @return
     */
    FC2_TEAM_FORCE_INLINE static auto get_module( const std::string & name, int partition = 0 ) -> std::pair< unsigned long long, unsigned long long >
    {
        detail::requests::module data;
        {
            detail::helper::safe_copy( data.name, name, sizeof data.name );
            data.partition = partition;
        }

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_GET_MODULE, data );

        /**
         * @brief module not found or attach never worked.
         */
        if( !ret.status )
        {
            return std::make_pair( 0ULL, 0ULL );
        }

        return std::make_pair( ret.base, ret.size );
    }

    /**
     * @brief pattern scan from a module retrieved from get_module (IDA-style only)
     *
     * @param module this should be the same module name from get_module.
     * @param pattern IDA-style pattern only.
     * @param offset
     * @param is_x64 set this false if the target process is x86
     * @param relative
     * @param ds data segment
     * @return
     */
    FC2_TEAM_FORCE_INLINE static auto pattern( const std::string & module, const std::string & pattern, unsigned int offset, bool is_x64 = true, bool relative = true, bool ds = false ) -> unsigned long long
    {
        detail::requests::pattern data;
        {
            detail::helper::safe_copy( data.module, module, sizeof data.module );
            detail::helper::safe_copy( data.pattern, pattern, sizeof data.pattern );

            data.offset = offset;
            data.is_x64 = is_x64;
            data.relative = relative;
            data.ds = ds;
        }

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_PATTERN, data );
        return ret.result;
    }

    /**
     * @brief reads memory address from attached process.
     * @tparam t
     * @param address
     * @return
     */
    template< typename t >
    FC2_TEAM_FORCE_INLINE static auto read_memory( unsigned long long address ) -> std::optional< t >
    {
        detail::requests::read_memory data;
        {
            data.address = address;
            data.size = sizeof( t );
        }

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_READ_MEMORY, data );

        /**
         * @brief operation failed.
         */
        if( !ret.bytes_read )
        {
            return std::nullopt;
        }

        /**
         * @brief data mismatch
         */
        if( ret.bytes_read != data.size )
        {
            return std::nullopt;
        }

        /** too unsafe **/
        // return *reinterpret_cast< t * >( ret.data );

        t output;
        memcpy( &output, ret.data, sizeof( t ) );
        return output;
    }

    /**
     * @brief makes all universe4 scripts invoke "on_team_call". this is a faster version of /luar
     * @tparam t
     * @param identifier this helps "on_team_call" identify the script or action.
     *
     * @code
     *
     * function test_script.on_team_call( identifier )
     *      if identifier == "hello_world" then
     *          fantasy.log("Hello World")
     *          return 1337
     *      end
     * end
     *
     * @endcode
     *
     * @return
     */
    template< typename t >
    FC2_TEAM_FORCE_INLINE static auto call( const std::string & identifier, FC2_LUA_TYPE typing = FC2_LUA_TYPE::FC2_LUA_TYPE_NONE ) -> t
    {
        detail::requests::call data;
        {
            detail::helper::safe_copy( data.identifier, identifier, sizeof data.identifier );
            data.typing = typing;
        }

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_CALL, data );

        /**
         * @brief compile-time typing support for std::string
         */
        if constexpr (std::is_same_v<t, std::string>)
        {
            return std::string( reinterpret_cast< char * >( ret.data ) );
        }
        else
        {
            t output;
            memcpy( &output, ret.data, sizeof( t ));
            return output;
        }
    }

    FC2_TEAM_FORCE_INLINE static auto call( const std::string & identifier )
    {
        detail::requests::call data;
        {
            detail::helper::safe_copy( data.identifier, identifier, sizeof data.identifier );
        }

        detail::client::send( FC2_TEAM_REQUESTS_CALL, data );
    }
}

#endif //FC2_HPP
#endif