///////////////////////////////////////////////////////////
//  KSocketStreamBuffer.h
//  Implementation of the Class KSocketStreamBuffer
//  Created on:      03-ËÄÔÂ-2013 16:45:41
//  Original author: Administrator
///////////////////////////////////////////////////////////

#if !defined(EA_80A63649_5108_47e2_A919_3776AA316F27__INCLUDED_)
#define EA_80A63649_5108_47e2_A919_3776AA316F27__INCLUDED_

class KSocketStreamBuffer //: private KUnCopyable
{
public:
	KSocketStreamBuffer();
	KSocketStreamBuffer(const size_t nTotalSize);
	~KSocketStreamBuffer();
	size_t GetTotalSize() CONST;
	size_t GetUsedSize() CONST;
	size_t GetLeftSize() CONST;
	PCHAR GetLeftPtr() CONST;
	size_t GetUnReadDataSize() CONST;
	//BOOL GetPackage(KSPDynamicBuffer& spBuffer);
	BOOL AddUsedSize(const size_t nDataBytes);

private:
	/**
	 * the real buffer ptr managed by KSocketStreamBuffer.
	 */
	PCHAR m_pBuffer;
	/**
	 * the total size of m_pBuffer.</font>
	 */
	size_t m_nTotalSize;
	/**
	 * the begin pos of un-read data.
	 */
	size_t m_nDataHeadPos;
	/**
	 * the next pos of un-read data's end pos.
	 */
	size_t m_nDataTailPos;

};
#endif // !defined(EA_80A63649_5108_47e2_A919_3776AA316F27__INCLUDED_)
