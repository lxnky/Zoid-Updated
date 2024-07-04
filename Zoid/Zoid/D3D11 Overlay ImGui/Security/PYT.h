#pragma once
#include "Encryption/skStr.h"
#include <Windows.h>
#include <vector>
#include <string>

void Initialize_PYT(std::string license, std::string webhook, bool BSOD, bool PowerOffMoniter, bool EnableProtection, bool PCSearch);
void PYTGuard_AntiDump();
void PYTGuard_MapFile(const std::vector<unsigned char>& downloadedData);
extern bool SecurityRunning; // you can use this to check if security has been tampered with at all.
void check_security_integrity();

class PYTGuard {

public:
	std::string decoder(const std::string& encoded) 
	{
		const std::string base64_chars = skCrypt("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/").decrypt();
		std::vector<int> decoding_table(256, -1);

		for (int i = 0; i < 64; i++) {
			decoding_table[base64_chars[i]] = i;
		}

		size_t input_length = encoded.length();
		std::string decoded;

		for (size_t i = 0; i < input_length; i += 4) {
			int sextet_a = decoding_table[encoded[i]];
			int sextet_b = decoding_table[encoded[i + 1]];
			int sextet_c = decoding_table[encoded[i + 2]];
			int sextet_d = decoding_table[encoded[i + 3]];

			int triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

			decoded += static_cast<char>((triple >> 16) & 0xFF);
			if (encoded[i + 2] != '=') {
				decoded += static_cast<char>((triple >> 8) & 0xFF);
			}
			if (encoded[i + 3] != '=') {
				decoded += static_cast<char>(triple & 0xFF);
			}
		}

		return decoded;
	}

}; static PYTGuard* PYT = new PYTGuard();