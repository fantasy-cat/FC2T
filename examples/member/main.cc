/**
 * @file main.cc
 * @author typedef
 * @brief tests the get_session function
 */
#include <fc2.hpp>

int main()
{
    /**
     * @brief this returns the fc2::detail::requests::session. this struct might subject to change. always use the documentation for the latest information.
     */
    auto session = fc2::get_session();

    /**
     * @brief output
     */
    std::printf(
            "Name: %s\nLicense Key: %s\nSessions Directory: %s\nIdentifier: %s\nLevel: %d\nProtection: %d",
            session.username,
            session.license,
            session.directory,
            session.identifier,
            session.level,
            session.protection
    );
    return 0;
}