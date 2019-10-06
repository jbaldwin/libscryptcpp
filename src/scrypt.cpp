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
) -> ResultEnum
{
    int rc = libscrypt_check(mcf.data(), password.data());

    // Error to decrypt/check.
    if(rc < 0)
    {
        return ResultEnum::ERROR_DECRYPT_FAILURE;
    }

    return (rc == 0)
        ? ResultEnum::PASSWORD_DOES_NOT_MATCH
        : ResultEnum::PASSWORD_MATCHES;
}

} // namespace scrypt
