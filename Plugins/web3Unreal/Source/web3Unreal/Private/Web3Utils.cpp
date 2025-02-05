#include "Web3Utils.h"

/*
 * Converts c style char array to c++ string representing the byte array in hex
 */
std::string UWeb3Utils::hexStr(unsigned char* data, int len)
{
	std::string s(len * 2, ' ');
	for (int i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}

/*
 * Converts a string with hex chars representing a hex value to its corresponding byte array
 */
void UWeb3Utils::ByteArrayFromHexStr(FString hexString, unsigned char byteArray[])
{
	FString hexStringUpper = hexString.ToUpper();
	int byteArrayIndex = 0;
	for (auto iter = hexStringUpper.begin(); iter != hexStringUpper.end(); ++iter)
	{
		wchar_t char_i = *iter;
		++iter;
		if (!(iter != hexStringUpper.end()))
		{
			throw "Hex string is not made up of complete bytes!";
		}

		wchar_t char_iPlus1 = *iter;
		//map the character to 0xletter then shift the higher one over and bitwise or them
		auto byte_0 = hexCharToByteMap.at(char_i);
		auto byte_1 = hexCharToByteMap.at(char_iPlus1);
		unsigned char byteToAdd = (byte_0 << 4) | byte_1;
		byteArray[byteArrayIndex] = byteToAdd;
		++byteArrayIndex;
	}
}
/*
 * Converts TArray of bytes to c++ string representing the byte array in hex
 */
FString UWeb3Utils::ByteArrayToFString(TArray<uint8> arr)
{
	std::vector<uint8> msg;
	for (auto iter = arr.begin(); iter != arr.end(); ++iter)
	{
		uint8 char_i = *iter;
		msg.push_back(char_i);
	}
	auto msgStr = hexStr(&msg[0], msg.size());
	return FString(msgStr.c_str());
}