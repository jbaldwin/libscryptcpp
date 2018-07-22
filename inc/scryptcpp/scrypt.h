#pragma once

#include <string>
#include <optional>

extern "C"
{
#include "libscrypt/libscrypt.h"
}

namespace scrypt
{

/**
 * Using the scrypt hash algorithm takes a password and generates an 'mcf' data using
 * a random salt.
 * @param password The password to salt+hash.
 * @param N Defined as the CPU and RAM cost of the hash.
 *          This must be a power of 2.
 * @param r RAM cost.
 * @param p CPU cost defined in parallelism.
 * @return The MCF representation of the salted+hashed password.  This can be stored in a database
 *         and then used with 'check()' to determine is a password is correct.
 */
auto hash(
    const std::string& password,
    uint32_t N = SCRYPT_N,
    uint8_t r = SCRYPT_r,
    uint8_t p = SCRYPT_p
) -> std::optional<std::string>;

/**
 * Using the scrypt hash algorithm takes a generated MCF from 'hash()' and a password and checks
 * to see if the two match.
 * @throws std::runtime_error If the check completely fails to decrypt.
 * @param mcf The MCF generated from hash().
 * @param password The password to check to see if it matches the MCF.
 * @return True if the password is a match, false otherwise.
 */
auto check(
    std::string mcf,
    const std::string& password
) -> bool;

} // namespace scrypt