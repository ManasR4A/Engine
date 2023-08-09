#include "BitArray.h"
#include "assert.h"
#include "iostream"


// funtions for 64 bit 
#ifdef _WIN64

// constructors
BitArray::BitArray()
{
	WordLen = 64;
	WordCount = 0;
	TotalBits = 0;
	bitarray = nullptr;
}

BitArray::BitArray(size_t i_NumOfBits)
{
	WordLen = 64;
	WordCount = (i_NumOfBits / WordLen);
	TotalBits = i_NumOfBits;
	bitarray = new uint64_t[WordCount]; // not stored in custom heapManager thus does not affect the size of the big allocation of user memory in FSAs
	//SetAll();
}

// funtion to initialize the member variables after the instance is constructed.
void BitArray::CreateBitArray(const size_t i_NumOfBits)
{
	WordLen = 64;
	WordCount = (i_NumOfBits / WordLen);
	TotalBits = i_NumOfBits;
	bitarray = new uint64_t[WordCount];
	//SetAll();
}

// Clears all the bits in the bitarray
void BitArray::ClearAll()
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		bitarray[temp] = 0x0000000000000000;
		temp++;
	}
}

// Sets all the bits in the bitarray
void BitArray::SetAll()
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		bitarray[temp] = 0xfffffffffffffffe;
		//~(bitarray[temp] & 0);
		temp++;
	}
}

// Checks if all the bits in the bitarray are clear or not
bool BitArray::IsClearAll() const
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		if (bitarray[temp] != 0x0000000000000000)
			return false;
		temp++;
	}
	return true;
}

// Checks if all the bits in the bitarray are set or not. Thus indicating that the entire associated FSA is free
bool BitArray::IsSetAll() const
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		if (bitarray[temp] != 0xfffffffffffffffe)
			return false;
		temp++;
	}
	return true;
}

// Checks if the specific bit is set or not
bool BitArray::IsBitSet(const size_t i_BitNum) const
{
	if (i_BitNum <= TotalBits)
	{
		size_t word = i_BitNum / WordLen;
		size_t BitNum = i_BitNum % WordLen;
		if (bitarray != nullptr && bitarray[word] & (1ULL << BitNum)) // using 1ULL to specify that we are comparing to a 64 bit number
			return true;
		else
			return false;
	}
	return false;
}

// Clears the particular bit
void BitArray::ClearBit(const size_t i_BitNum)
{
	if(i_BitNum <= TotalBits)
	{
		// calculating which word would the inputed bit will be in
		size_t word = i_BitNum / WordLen;
		size_t BitNum = i_BitNum % WordLen;
		BitNum--;
	
		// Clearing the BitNum th bit of the Word
		bitarray[word] &= ~(1ULL << BitNum);
	}
}

// sets the particular bit
void BitArray::SetBit(const size_t i_BitNum)
{
	assert(i_BitNum <= TotalBits);

	// calculating which word would the inputed bit will be in
	size_t word = i_BitNum / WordLen;
	size_t BitNum = i_BitNum % WordLen;

	// Setting the BitNum th bit of the Word
	bitarray[word] |= (1ULL << BitNum);
}

/* return the bit value of the first set bit from the bit array 
thus giving the position of the first free block in the associated FSA.
If returns 0, no free block is available in associated FSA. */
size_t BitArray::GetFirstSetBit() const
{
	// see which first word is not completely clear
	size_t tempword = 1;
	while (tempword < WordCount)
	{
		if (bitarray[tempword] != 0)
			break;
		tempword++;
	}

	// only if a word that isn't clear is found
	if (tempword <= WordCount)
	{
		unsigned long o_index;
		_BitScanForward64(&o_index, bitarray[tempword]); // got bit in the word
		
		// If the bit gotten isn't the one of the bits that is not being used in the last word
		if (((tempword - 1) * WordLen) + o_index <= TotalBits)
			return ((tempword - 1) * WordLen) + o_index + 1;
		else
			return 0;
	}
	else
		return 0;
}

#else
// functions for 32 bit
#ifdef _WIN32

// constructors
BitArray::BitArray()
{
	WordLen = 32;
	WordCount = 0;
	TotalBits = 0;
	bitarray = nullptr;
}

BitArray::BitArray(size_t i_NumOfBits)
{
	WordLen = 32;
	WordCount = (i_NumOfBits / WordLen) + 1;
	TotalBits = i_NumOfBits;
	bitarray = new uint32_t[WordCount]; // not stored in custom heapManager thus does not affect the size of the big allocation of user memory in FSAs
}

// funtion to initialize the member variables after the instance is constructed.
void BitArray::CreateBitArray(const size_t i_NumOfBits)
{
	WordLen = 32;
	WordCount = (i_NumOfBits / WordLen) ;
	TotalBits = i_NumOfBits;
	bitarray = new uint32_t[WordCount];
}

// Clears all the bits in the bitarray
void BitArray::ClearAll()
{
	size_t temp = 0;
	while (temp < WordCount )
	{
		bitarray[temp] = 0x0000;
		temp++;
	}
}

// Sets all the bits in the bitarray
void BitArray::SetAll()
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		bitarray[temp] = 0xfffe;
		temp++;
	}
}

// Checks if all the bits in the bitarray are clear or not
bool BitArray::IsClearAll() const
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		if (bitarray[temp] != 0x0000)
			return false;
		temp++;
	}
	return true;
}

// Checks if all the bits in the bitarray are set or not. Thus indicating that the entire associated FSA is free
bool BitArray::IsSetAll() const
{
	size_t temp = 0;
	while (temp < WordCount)
	{
		if (bitarray[temp] != 0xfffe)
			return false;
		temp++;
	}
	return true;
}

// Checks if the specific bit is set or not
bool BitArray::IsBitSet(const size_t i_BitNum) const
{
	assert(i_BitNum <= TotalBits);
	size_t word = i_BitNum / WordLen;
	size_t BitNum = i_BitNum % WordLen;
	if (bitarray != nullptr && bitarray[word] & (1 << BitNum)) // using 1ULL to specify that we are comparing to a 64 bit number
		return true;
	else
		return false;
}

// Clears the particular bit
void BitArray::ClearBit(const size_t i_BitNum)
{
	assert(i_BitNum <= TotalBits);

	// calculating which word would the inputed bit will be in
	size_t word = i_BitNum / WordLen;
	size_t BitNum = i_BitNum % WordLen;
	BitNum--; // To convert from my code indexing to array indexing

	// Clearing the BitNum th bit of the Word
	bitarray[word] &= ~(1 << BitNum);
}

// sets the particular bit
void BitArray::SetBit(const size_t i_BitNum)
{
	assert(i_BitNum <= TotalBits);

	// calculating which word would the inputed bit will be in
	size_t word = i_BitNum / WordLen;
	size_t BitNum = i_BitNum % WordLen;

	// Setting the BitNum th bit of the Word
	bitarray[word] |= (1 << BitNum);
}

/* return the bit value of the first set bit from the bit array
thus giving the position of the first free block in the associated FSA.
If returns 0, no free block is available in associated FSA. */
size_t BitArray::GetFirstSetBit() const
{
	// see which first word is not completely clear
	size_t tempword = 1;
	while (tempword <= WordCount)
	{
		if (bitarray[tempword] != 0x0000)
			break;
		tempword++;
	}

	// only if a word that isn't clear is found
	if (tempword <= WordCount)
	{
		unsigned long o_index;
		_BitScanForward(&o_index, bitarray[tempword]); // got bit in the word

		// If the bit gotten isn't the one of the bits that is not being used in the last word
		if (((tempword - 1) * WordLen) + o_index <= TotalBits)
			return ((tempword - 1) * WordLen) + o_index + 1; // +1 is just to convert from array index to indexing used in code.
		else
			return 0;
	}
	else
		return 0;
}

#endif // _WIN32
#endif // _WIN64




// destructor
BitArray::~BitArray()
{
	if(bitarray != nullptr) // only delete[] if bitarray has an array
		delete[] bitarray;
}
