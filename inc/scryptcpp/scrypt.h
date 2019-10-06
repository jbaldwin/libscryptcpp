#pragma once

#include <string>
#include <optional>

extern "C"
{
#include "libscrypt/libscrypt.h"
} // extern "C"

namespace scrypt
{

enum class ResultEnum
{
    PASSWORD_MATCHES,
    PASSWORD_DOES_NOT_MATCH,
    ERROR_DECRYPT_FAILURE
};

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
 * Using the scrypt hash algorithm takes a generated MCF from 'hash()'
 * and a password and checks to see if the two match.
 * @param mcf The MCF generated from hash().  Note that the underlying scrypt
 *            library will edit the mcf in place so a copy is required to pass
 *            into check().  Move the mcf into this function if you do not
 *            want to take a copy and can give up ownership.
 * @param password The password to check to see if it matches the MCF.
 * @return The result status of the check, see ResultEnum for possible results.
 */
auto check(
    std::string mcf,
    const std::string& password
) -> ResultEnum;

} // namespace scrypt
