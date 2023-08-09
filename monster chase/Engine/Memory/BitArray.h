#pragma once
#include "istream"

class BitArray
{
public:
	
	// Constructors
	BitArray();
	BitArray(size_t i_NumOfBits);

	// create the BitArray on a trigger
	void CreateBitArray(const size_t i_NumOfBits);

	// set / clear all the bits in the bit array
	void ClearAll();
	void SetAll();

	// returns if all the bits are set or clear or not
	bool IsClearAll() const; 
	bool IsSetAll() const;

	// checks if the inputed bit is set or not.
	bool IsBitSet(const size_t i_BitNum) const;

	// Sets or Clears the defined bit in the bitarray
	void ClearBit(const size_t i_BitNum);
	void SetBit(const size_t i_BitNum);

	// Gets the index of the first set bit from the bit array
	size_t GetFirstSetBit() const;

	// destructor to remove the memory of 
	~BitArray();

private:

	size_t WordCount; // stores the number of uintn_t that make up the bit array
	size_t WordLen; // stores the length of the registers based on the build configuration
	size_t TotalBits;

	// In BitArray 1 = Bit represents the free block & 0 = Bit represents a block that is allocated

#ifdef _WIN64
	uint64_t * bitarray;

#else
#ifdef _WIN32
	uint32_t * bitarray;
#endif // _WIN32
#endif // _WIN64

};



// TEMP FOR EASY COPY PASTE USE

#ifdef _WIN64

#else
#ifdef _WIN32

#endif // _WIN32
#endif // _WIN64
