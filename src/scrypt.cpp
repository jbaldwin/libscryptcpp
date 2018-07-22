#include "scryptcpp/scrypt.h"

namespace scrypt
{

auto hash(
    const std::string& password,
    uint32_t N,
    uint8_t r,
    uint8_t p
) -> std::optional<std::string>
{
    std::string output(SCRYPT_MCF_LEN, '0');
    int rc = libscrypt_hash(output.data(), password.data(), N, r, p);
    if(rc > 0) // 0 is failure, > 0 is success
    {
        return output;
    }
    return {};
}

auto check(
    std::string mcf,
    const std::string& password
) -> bool
{
    int rc = libscrypt_check(mcf.data(), password.data());

    // Error to decrypt/check.
    if(rc < 0)
    {
        throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + " failed to check password.");
    }

    if(rc == 0)
    {
        return false; // Password is incorrect.
    }

    return true; // Password is correct.
}

} // namespace scrypt