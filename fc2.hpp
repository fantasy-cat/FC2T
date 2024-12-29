/**
 * @title FC2T
 * @author typedef
 * @file fc2.hpp
 * @description https://github.com/fantasy-cat/FC2T
 */
#ifndef FC2_HPP
#define FC2_HPP

/**
 * @brief versioning
 */
#define FC2_TEAM_VERSION_MAJOR 1
#define FC2_TEAM_VERSION_MINOR 4

/**
 * @brief max size of any string input. dynamically allocating this would be better. there are some unfortunate inconsistencies with this at times when it is dynamically allocated due to how some processors cache memory to improve performance.
 *
 * it usually works in favor of the system, but the larger the buffer size, your processor may not be as efficient accessing certain parts of the cache, thereby causing performance issues.
 *
 * furthermore, larger data take affect performance in some operations. some functions here use std::memcpy, which can be hindered in speed due to large buffer sizes. if you -really- need to change this, it should only be in projects that aren't demanding on functions that utilize this (like strings). finally, this is lazy.
 *
 */
#ifndef FC2_TEAM_MAX_DATA_BUFFER
#define FC2_TEAM_MAX_DATA_BUFFER ( 1024 )
#endif

#ifndef FC2_TEAM_BUFFER_SIZE
#define FC2_TEAM_BUFFER_SIZE ( 32 * 1024 )
#endif

/**
 * @brief how many seconds to wait for a response before marking the request as timed out. in reality, should not take longer than a second to get a response back. 3 seconds is extremely generous.
 */
#ifndef FC2_TEAM_REQUESTS_TIMEOUT
#define FC2_TEAM_REQUESTS_TIMEOUT 3
#endif

/**
 * @brief how many seconds to wait for an API request before marking the request as timed out. this applies to any API or HTTP related requests. sometimes it will take longer for web requests to get a response back. the server could be down or something else with your network could cause this.
 */
#ifndef FC2_TEAM_REQUESTS_API_TIMEOUT
#define FC2_TEAM_REQUESTS_API_TIMEOUT 5
#endif

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

#define FC2T_FUNCTION FC2_TEAM_FORCE_INLINE static

/**
 * @brief it would be users best interest to define one of these macros to help the project distinguish which solution to use.
 * if this is not defined, FC2T projects will always try to connect to Universe4 instead of Constellation4.
 */
#if !defined(FC2_TEAM_UNIVERSE4) && !defined(FC2_TEAM_CONSTELLATION4) && !defined(FC2_TEAM_PARALLAX2)
    #if defined(_MSC_VER)
        #pragma message("Warning: FC2_TEAM_UNIVERSE4 or FC2_TEAM_CONSTELLATION4 or FC2_TEAM_PARALLAX2 is not defined. FC2T will assume the target solution is global (all solutions).")
    #elif defined(__GNUC__) || defined(__clang__)
        #warning "FC2_TEAM_UNIVERSE4 or FC2_TEAM_CONSTELLATION4 or FC2_TEAM_PARALLAX2 is not defined. FC2T will assume the target solution is global (all solutions)."
    #else
        #pragma message("Warning: FC2_TEAM_UNIVERSE4 or FC2_TEAM_CONSTELLATION4 or FC2_TEAM_PARALLAX2 is not defined. FC2T will assume the target solution is global (all solutions).")
    #endif
#endif

/**
 * @brief SHM keys
 */
#ifndef SHM_KEY_LINUX_GLOBAL
    #define SHM_KEY_LINUX_GLOBAL 329032490
#endif
#ifndef SHM_KEY_LINUX_UNIVERSE
    #define SHM_KEY_LINUX_UNIVERSE 329032496
#endif
#ifndef SHM_KEY_LINUX_CONSTELLATION
    #define SHM_KEY_LINUX_CONSTELLATION 329032497
#endif
#ifndef SHM_KEY_LINUX_PARALLAX
    #define SHM_KEY_LINUX_PARALLAX 329032498
#endif
#ifndef SHM_KEY_WIN_GLOBAL
    #define SHM_KEY_WIN_GLOBAL "Global\\329032490"
#endif
#ifndef SHM_KEY_WIN_UNIVERSE
    #define SHM_KEY_WIN_UNIVERSE "Global\\329032496"
#endif
#ifndef SHM_KEY_WIN_CONSTELLATION
    #define SHM_KEY_WIN_CONSTELLATION "Global\\329032497"
#endif
#ifndef SHM_KEY_WIN_PARALLAX
    #define SHM_KEY_WIN_PARALLAX "Global\\329032498"
#endif
#ifndef SHM_KEY_WIN_AURORA2
    #define SHM_KEY_WIN_AURORA2 "Global\\329032499"
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

    /**
     * CreateSemaphore failed
     */
    FC2_TEAM_ERROR_FAILED_SEMAPHORE,
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
    FC2_TEAM_REQUESTS_HTTP_REQUEST,
    FC2_TEAM_REQUESTS_HTTP_ESCAPE,
    FC2_TEAM_REQUESTS_SETUP,
    FC2_TEAM_REQUESTS_INPUT,
    FC2_TEAM_REQUESTS_DRAW,
    FC2_TEAM_REQUESTS_SESSION,
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
 * @brief mouse button key codes
 * https://constelia.ai/sdk/FC2/modules/input/#click
 */
enum FC2_TEAM_MOUSE_CODE : int
{
    FC2_TEAM_MOUSE_NONE,
    FC2_TEAM_MOUSE_LEFT,
    FC2_TEAM_MOUSE_RIGHT,
    FC2_TEAM_MOUSE_MIDDLE,
};

/**
 * @brief drawing types accepted by fc2kt
 */
enum FC2_TEAM_DRAW_TYPE : int
{
    FC2_TEAM_DRAW_TYPE_NONE,
    FC2_TEAM_DRAW_TYPE_BOX,
    FC2_TEAM_DRAW_TYPE_LINE,
    FC2_TEAM_DRAW_TYPE_BOX_FILLED,
    FC2_TEAM_DRAW_TYPE_TEXT,
};

/**
 * @brief fc2t style index for details.style array
 */
enum FC2_TEAM_DRAW_STYLE : int
{
    FC2_TEAM_DRAW_STYLE_RED,
    FC2_TEAM_DRAW_STYLE_GREEN,
    FC2_TEAM_DRAW_STYLE_BLUE,
    FC2_TEAM_DRAW_STYLE_ALPHA,
    FC2_TEAM_DRAW_STYLE_THICKNESS,
    FC2_TEAM_DRAW_STYLE_FONT_SIZE,
    FC2_TEAM_DRAW_STYLE_TYPE,
};

/**
 * @brief fc2t dimensions for details.dimensions array
 */
enum FC2_TEAM_DRAW_DIMENSIONS : int
{
    FC2_TEAM_DRAW_DIMENSIONS_LEFT,
    FC2_TEAM_DRAW_DIMENSIONS_TOP,
    FC2_TEAM_DRAW_DIMENSIONS_RIGHT,
    FC2_TEAM_DRAW_DIMENSIONS_BOTTOM,
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
#include <cstddef> /** offsetof **/
#include <array> /** std::array **/
#include <algorithm> /** std::min/std::max/std::copy_if **/

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
#ifdef FC2_TEAM_CONSTELLATION4
    #define SHM_KEY SHM_KEY_LINUX_CONSTELLATION
#elif defined(FC2_TEAM_PARALLAX2)
    #define SHM_KEY SHM_KEY_LINUX_PARALLAX
#elif defined(FC2_TEAM_UNIVERSE4)
    #define SHM_KEY SHM_KEY_LINUX_UNIVERSE
#else
    #define SHM_KEY SHM_KEY_LINUX_GLOBAL
#endif
#else
#define NOMINMAX
#include <windows.h>

#ifdef FC2_TEAM_CONSTELLATION4
    #define SHM_KEY SHM_KEY_WIN_CONSTELLATION
#elif defined(FC2_TEAM_PARALLAX2)
    #define SHM_KEY SHM_KEY_WIN_PARALLAX
#elif defined(FC2_TEAM_UNIVERSE4)
    #define SHM_KEY SHM_KEY_WIN_UNIVERSE
#else
    #define SHM_KEY SHM_KEY_WIN_GLOBAL
#endif
#endif

namespace fc2
{
    namespace detail
    {
        enum FC2_TEAM_STATUS : int
        {
            /**
             * @brief still waiting for Universe4 to finish operation
             */
            FC2_TEAM_SERVER_PENDING,

            /**
             * @brief operation is completed
             */
            FC2_TEAM_SERVER_DONE,

            /**
             * @brief server timed out
             */
            FC2_TEAM_SERVER_TIMEOUT,
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
                char url[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char buffer[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief lua script
             */
            struct lua
            {
                char buffer[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief attach to process
             */
            struct attach
            {
                unsigned long id = 0;
                char name[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                bool install_ipc = true;
                int status = 0;
            };

            /**
             * @brief get module
             */
            struct module
            {
                char name[ FC2_TEAM_MAX_DATA_BUFFER ] {};
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
                char module[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char sig_pattern[FC2_TEAM_MAX_DATA_BUFFER] {};
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

                unsigned char data[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief on_team_call request
             */
            struct call
            {
                char identifier[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                FC2_LUA_TYPE typing = FC2_LUA_TYPE::FC2_LUA_TYPE_NONE;
                unsigned char data[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char args[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief http request
             */
            struct http
            {
                char url[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char post[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char response[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief encode and escape
             */
            struct http_escape
            {
                char str[ FC2_TEAM_MAX_DATA_BUFFER ] {};
                char response[ FC2_TEAM_MAX_DATA_BUFFER ] {};
            };

            /**
             * @brief start fc2k or zombiefc2
             */
            struct setup
            {
                bool result = false;
            };

            /**
             * @brief mouse input
             */
            struct input
            {
                int x = 0;
                int y = 0;
                int button = 0;
                int mode = 0;
            };

            /**
             * @brief drawing
             */
            struct draw
            {
                struct detail
                {
                    char text[128];
                    std::int32_t dimensions[4];
                    std::int32_t style[7];
                };

               detail details[ 100 ] { };
            };

            /**
             * @brief member information from the Sessions module in FC2
             *
             * this will only get the bare minimum about a member. use `getMember` on the Web API to get other information.
             * https://constelia.ai/sdk/Web%20API/methods/#getmember
             */
            struct session
            {
                /**
                 * @brief raw license key
                 */
                char license[ 20 ] {};

                /**
                 * @brief forum username
                 */
                char username[ 256 ] {};

                /**
                 * @brief this is the Sessions identifier of the user. this value will always appear in the form of SHA256 and is encrypted numerous times. this value never represents the actual identifier stored by constelia.ai. however, it will uniquely identify a user.
                 */
                char identifier[ 64 ] {};

                /**
                 * @brief Sessions directory
                 *
                 * this should actually be 260, but FC2 actually has this as 256 for some reason. let's just stay together here.
                 */
                char directory[ 256 ] {};

                /**
                 * @brief the user level
                 *
                 * 1: Member
                 * 2: Veteran Member
                 * 3: VIP
                 */
                int level = 0;

                /**
                 * @brief protection mode. this not represent minimum mode. it doesn't matter anyway as FC2T wont run in minimum mode.
                 *
                 * 0 = standard
                 * 1 = zombie
                 * 2 = kernel
                 *
                 * on Linux, this will always be 0
                 */
                int protection = 0;
            };
        };

#pragma pack(push, 1)
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
            char * data = nullptr;
        };
#pragma pack(pop)

        class shm
        {
        public:
#ifdef __linux__
            /**
             * @brief shm id
             */
            int id = -1;

            /**
             * @brief semaphore mutex to prevent simultaneous operations
             */
            sem_t sem_mutex = {};
#else
            HANDLE shm_handle = nullptr;
            HANDLE sem_mutex = nullptr;
#endif

            /**
             * @brief last caught error
             */
            FC2_TEAM_ERROR_CODES last_error = FC2_TEAM_ERROR_NO_ERROR;

            /**
             * @brief data being sent/rec
             */
            void * data;

        public:
            FC2_TEAM_FORCE_INLINE shm()
            {
#ifdef __linux__
                /**
                 * @brief find server
                 */
                id = shmget( SHM_KEY, FC2_TEAM_BUFFER_SIZE, 0666);

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
#else
                /**
                 * @brief find mapping
                 *
                 * on Windows, OpenFileMapping will succeed even if it doesn't have FILE_MAP_ALL_ACCESS permissions. this is extremely misleading. if you notice your projects not working, it is important to note that you should execute it with administrator permissions.
                 */
                shm_handle = OpenFileMappingA( FILE_MAP_ALL_ACCESS, FALSE, SHM_KEY );

                /**
                 * @brief universe4 isn't open. cant connect to server.
                 */
                if (shm_handle == nullptr || GetLastError() == ERROR_ALREADY_EXISTS)
                {
                    last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_FC2_SOLUTION_OPEN;
                    return;
                }

                /**
                 * @brief attach to data
                 */
                data = MapViewOfFile(shm_handle, FILE_MAP_ALL_ACCESS, 0, 0, FC2_TEAM_BUFFER_SIZE );

                if (data == nullptr)
                {
                    last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_MEMORY_FAILED_TO_ATTACH;
                    return;
                }

                sem_mutex = CreateMutex( nullptr, 0, nullptr );
                if (sem_mutex == nullptr)
                {
                    last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_FAILED_SEMAPHORE;
                    return;
                }

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
            FC2T_FUNCTION auto get()
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
#ifdef __linux__
                if( c->id < 0 || c->last_error != FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }
#else
                if (c->shm_handle == nullptr || c->shm_handle == INVALID_HANDLE_VALUE)
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }
#endif
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
            FC2T_FUNCTION auto send( int id, t req ) -> t
            {
                /**
                 * @brief get client
                 */
                auto c = get();

                /**
                 * @brief did something break
                */
#ifdef __linux__
                if( c->id < 0 || c->last_error != FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }

                /**
                 * @brief semaphore lock
                */
                sem_wait( &c->sem_mutex );
#else

                if( c->shm_handle == nullptr || c->shm_handle == INVALID_HANDLE_VALUE || c->last_error != FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR )
                {
                    std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                }

                /**
                 * @brief semaphore lock
                */
                WaitForSingleObject( c->sem_mutex, INFINITE );
#endif

                /**
                 * @brief create new data with our request info
                 */
                auto data = std::make_unique< char[] >( offsetof( information, data ) + sizeof ( t ) );
                {
                    memcpy( data.get(), static_cast< const void * >( &id ), sizeof( detail::information::id ));
                    memcpy( data.get() + offsetof( information, data ), static_cast< const void * >( &req ), sizeof( t ));
                }

                /**
                 * @brief send to universe4
                 */
                memcpy( c->data, data.get(), offsetof( information, data ) + sizeof ( t ) );

                /**
                 * @brief convert data
                 */
                auto information = reinterpret_cast< detail::information * >(c->data);

                /**
                 * @brief wait until completed
                 */
                unsigned long long timeout_time = std::time(nullptr) + (information->id == FC2_TEAM_REQUESTS::FC2_TEAM_REQUESTS_API || information->id == FC2_TEAM_REQUESTS::FC2_TEAM_REQUESTS_HTTP_REQUEST ? FC2_TEAM_REQUESTS_API_TIMEOUT : FC2_TEAM_REQUESTS_TIMEOUT );

                while( information->status == FC2_TEAM_STATUS::FC2_TEAM_SERVER_PENDING ) {
                    if( static_cast< unsigned long long >( std::time(nullptr) ) > timeout_time )
                    {
                        information->status = FC2_TEAM_STATUS::FC2_TEAM_SERVER_TIMEOUT;
                        c->last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_FC2_SOLUTION_OPEN;
                        break;
                    }
                }

                /**
                 * @brief semaphore unlock
                */
#ifdef __linux__
                sem_post( &c->sem_mutex );
#else
                ReleaseMutex( c->sem_mutex );
#endif

                /**
                 * @brief return data
                 */
                memcpy( &req, static_cast< char * >( c->data ) + offsetof( detail::information, data ), sizeof( t ) );

                /**
                 * @brief reset last error
                 */
                if( information->status == FC2_TEAM_STATUS::FC2_TEAM_SERVER_DONE )
                {
                    c->last_error = FC2_TEAM_ERROR_CODES::FC2_TEAM_ERROR_NO_ERROR;
                }
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
            FC2T_FUNCTION void safe_copy( char * dest, const char * src, const std::size_t size )
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

            FC2T_FUNCTION void safe_copy(char * dest, const std::string & src, const std::size_t size )
            {
                safe_copy(dest, src.c_str(), size );
            }
        }
    } // end detail

    /**
     * @brief get FC2T version compiled with
     * @return
     */
    FC2T_FUNCTION auto get_version() -> std::pair< unsigned int, unsigned int >
    {
        return std::make_pair( FC2_TEAM_VERSION_MAJOR, FC2_TEAM_VERSION_MINOR );
    }

    /**
     * @brief get the last error FC2T invoked. use this function to check if the FC2 solution has been closed or isn't open to begin with.
     * @return
     */
    FC2T_FUNCTION auto get_error( ) -> FC2_TEAM_ERROR_CODES
    {
        auto c = detail::client::get();
        return c->last_error;
    }

    /**
     * @brief this will return the time difference in Universe4 logs. if you want to test how fast fc2.hpp team is for you, use this.
     */
    FC2T_FUNCTION auto ping() -> std::pair< unsigned long long, unsigned long long >
    {
        detail::requests::ping data{};
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto epoch = now.time_since_epoch();
            auto ticks = std::chrono::duration_cast<std::chrono::microseconds>(epoch).count();

            data.ping = ticks;
        }

        auto ret = detail::client::send< detail::requests::ping >( FC2_TEAM_REQUESTS_PING, data );

        return std::make_pair( ret.ping, ret.pong );
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
    FC2T_FUNCTION auto api( const std::string & url ) -> std::string
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
    FC2T_FUNCTION auto lua( const std::string & code ) -> void
    {
        detail::requests::lua data;
        {
            detail::helper::safe_copy( data.buffer, code, sizeof data.buffer );
        }

        detail::client::send( FC2_TEAM_REQUESTS_LUA, data );
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
    FC2T_FUNCTION auto call( const std::string & identifier, FC2_LUA_TYPE typing = FC2_LUA_TYPE::FC2_LUA_TYPE_NONE, const std::string & json = "" ) -> t
    {
        detail::requests::call data;
        {
            detail::helper::safe_copy( data.identifier, identifier, sizeof data.identifier );
            if( !json.empty() )
            {
                detail::helper::safe_copy( data.args, json, sizeof data.args );
            }

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

    FC2T_FUNCTION auto call( const std::string & identifier, const std::string & json = "" )
    {
        detail::requests::call data;
        {
            detail::helper::safe_copy( data.identifier, identifier, sizeof data.identifier );
            if( !json.empty() )
            {
                detail::helper::safe_copy( data.args, json, sizeof data.args );
            }
        }

        detail::client::send( FC2_TEAM_REQUESTS_CALL, data );
    }

    /**
     * @brief installs fc2k or zombiefc2
     * @return
     */
    FC2T_FUNCTION auto setup( ) -> bool
    {
        detail::requests::setup data;
        auto ret = detail::client::send( FC2_TEAM_REQUESTS_SETUP, data );
        return ret.result;
    }

    /**
     * @brief this gets the current drawing requests inside of FC2. the original plan was to simply create an array and always have a static return result. however, this would not only increase the buffer size of FC2T, but it's less reliable.
     *
     * sync is questionable. it will help with overlay projects and any other renderers that require information to be synchronized, but it can go faulty if there is genuinely nothing to draw. you can actually freeze your renderer this way. this is so bad ughhhhhhhhhhh. ill fix this.
     *
     * @param sync
     * @return
     */
    FC2T_FUNCTION auto get_drawing( ) -> std::vector< fc2::detail::requests::draw::detail >
    {
        std::vector< fc2::detail::requests::draw::detail > output;
        detail::requests::draw data;

        auto ret = detail::client::send( FC2_TEAM_REQUESTS_DRAW, data );

        std::copy_if(
                std::begin( ret.details ),
                std::end( ret.details ),
                std::back_inserter( output ),
                [ ]( const fc2::detail::requests::draw::detail & o )
                {
                    return o.style[ FC2_TEAM_DRAW_STYLE_TYPE ] != FC2_TEAM_DRAW_TYPE_NONE;
                }
        );
        return output;
    }

    /**
     * @brief this will get the bare essential information about a member. you should use "getMember" on the Web API to get detailed information about the user running the FC2T project. https://constelia.ai/sdk/Web%20API/methods/#getmember
     * @return
     */
    FC2T_FUNCTION auto get_session( ) -> detail::requests::session
    {
        detail::requests::session data;
        auto ret = detail::client::send( FC2_TEAM_REQUESTS_SESSION, data );
        return ret;
    }

    /**
     * @brief engine module methods
     */
    namespace engine
    {
        /**
     * @brief makes Universe4 attach to a process. attachment process is different based on protection mode.
     * install_ipc is true by default. when true, FC2K or ZombieFC2 will automatically install itself if it hasn't been done already.
     *
     * @param value
     * @param install_ipc
     * @return
     */
        FC2T_FUNCTION auto attach( const std::variant< std::string, unsigned long> & value, bool install_ipc = true ) -> bool
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
        FC2T_FUNCTION auto get_module( const std::string & name, int partition = 0 ) -> std::pair< unsigned long long, unsigned long long >
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
        FC2T_FUNCTION auto pattern( const std::string & module, const std::string & pattern, unsigned int offset, bool is_x64 = true, bool relative = true, bool ds = false ) -> unsigned long long
        {
            detail::requests::pattern data;
            {
                detail::helper::safe_copy( data.module, module, sizeof data.module );
                detail::helper::safe_copy( data.sig_pattern, pattern, sizeof data.sig_pattern);

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
        FC2T_FUNCTION auto read_memory( unsigned long long address ) -> std::optional< t >
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

    }

    /**
     * @brief HTTP wrapper methods
     */
    namespace http
    {
        /**
         * @brief GET requests
         * @param url
         * @return
         */
        FC2T_FUNCTION auto get( const std::string & url ) -> std::string
        {
            detail::requests::http data;
            {
                detail::helper::safe_copy( data.url, url, sizeof data.url );
            }

            auto ret = detail::client::send( FC2_TEAM_REQUESTS_HTTP_REQUEST, data );
            return ret.response;
        }

        /**
         * @brief POST request
         * @param url
         * @param post_data
         * @return
         */
        FC2T_FUNCTION auto post( const std::string & url, const std::string & post_data ) -> std::string
        {
            detail::requests::http data;
            {
                detail::helper::safe_copy( data.url, url, sizeof data.url );
                detail::helper::safe_copy( data.post, post_data, sizeof data.post );
            }

            auto ret = detail::client::send( FC2_TEAM_REQUESTS_HTTP_REQUEST, data );
            return ret.response;
        }

        /**
         * @brief escapes a string so it can be properly encoded for GET or POST requests
         * @param str
         * @return
         */
        FC2T_FUNCTION auto escape( const std::string & str ) -> std::string
        {
            detail::requests::http_escape data;
            {
                detail::helper::safe_copy( data.str, str, sizeof data.str );
            }

            auto ret = detail::client::send( FC2_TEAM_REQUESTS_HTTP_ESCAPE, data );
            return ret.response;
        }
    }

    /**
     * @brief mouse simulation
     */
    namespace input
    {
        /**
         * @brief moves mouse by x and y amount of pixels (relative)
         * @param x
         * @param y
         */
        FC2T_FUNCTION auto move( int x, int y ) -> void
        {
            detail::requests::input data;
            {
                data.x = x;
                data.y = y;
            }

            detail::client::send( FC2_TEAM_REQUESTS_INPUT, data );
        }

        /**
         * @brief clicks a mouse button
         * @param button
         */
        FC2T_FUNCTION auto click( FC2_TEAM_MOUSE_CODE button ) -> void
        {
            detail::requests::input data;
            {
                data.mode = 1;
                data.button = button;
            }

            detail::client::send( FC2_TEAM_REQUESTS_INPUT, data );
        }

        /**
         * @brief holds down a mouse button
         * @param button
         */
        FC2T_FUNCTION auto down( FC2_TEAM_MOUSE_CODE button ) -> void
        {
            detail::requests::input data;
            {
                data.mode = 2;
                data.button = button;
            }

            detail::client::send( FC2_TEAM_REQUESTS_INPUT, data );
        }

        /**
         * @brief releases a held down mouse button
         * @param button
         */
        FC2T_FUNCTION auto up( FC2_TEAM_MOUSE_CODE button ) -> void
        {
            detail::requests::input data;
            {
                data.mode = 3;
                data.button = button;
            }

            detail::client::send( FC2_TEAM_REQUESTS_INPUT, data );
        }
    }
}

#endif //FC2_HPP
