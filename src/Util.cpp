#include <Util.h>
#include <ctime>
#include <chrono>

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include <array>
#include <vector>

#include <openssl/evp.h>

std::string B64Encode(const void* input, int length) {
    const auto pl = 4 * ((length + 2) / 3);
    std::vector<unsigned char> result(pl + 1, 0);
    auto output = reinterpret_cast<char*>(result.data()); //+1 for the terminating null that EVP_EncodeBlock adds on
    const auto ol = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(output), reinterpret_cast<const unsigned char*>(input), length);
    return std::string((char*)result.data(), result.size());
}

std::string B64Decode(const void* input, int length) {
    const auto pl = 3 * length / 4;
    std::vector<unsigned char> result(pl + 1, 0);
    auto output = result.data();
    const auto ol = EVP_DecodeBlock(output, reinterpret_cast<const unsigned char*>(input), length);
    return std::string((char*)result.data(), result.size());
}

std::string Time2Str(time_t time)
{
	struct tm* timeInfo = std::gmtime(&time);
	char formattedDate[80];
	std::strftime(formattedDate, 80, "%Y-%m-%d %H:%M:%S", timeInfo);
	return std::string(formattedDate);
}

unsigned long long GetCurrentEpochMillis()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	auto timeSinceEpoch = now.time_since_epoch();
	return duration_cast<milliseconds>(timeSinceEpoch).count();
}

std::string HMACSHA256(const std::string& msg, const std::string& secret)
{
    std::array<unsigned char, EVP_MAX_MD_SIZE> hash{};
    unsigned int hashLen;

    HMAC(
        EVP_sha256(),
        secret.data(),
        static_cast<int>(secret.size()),
        reinterpret_cast<unsigned char const*>(msg.data()),
        static_cast<int>(msg.size()),
        hash.data(),
        &hashLen
    );

    return B64Encode(hash.data(), hashLen);
}