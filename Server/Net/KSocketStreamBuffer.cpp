///////////////////////////////////////////////////////////
//  KSocketStreamBuffer.cpp
//  Implementation of the Class KSocketStreamBuffer
//  Created on:      03-ËÄÔÂ-2013 16:45:41
//  Original author: Administrator
///////////////////////////////////////////////////////////

#include "KSocketStreamBuffer.h"




KSocketStreamBuffer::KSocketStreamBuffer(){

}


KSocketStreamBuffer::KSocketStreamBuffer(const size_t nTotalSize){

}


KSocketStreamBuffer::~KSocketStreamBuffer(){

}


size_t KSocketStreamBuffer::GetTotalSize()CONST{

	return  NULL;
}


size_t KSocketStreamBuffer::GetUsedSize()CONST{

	return  NULL;
}


size_t KSocketStreamBuffer::GetLeftSize()CONST{

	return  NULL;
}


PCHAR KSocketStreamBuffer::GetLeftPtr()CONST{

	return  NULL;
}


size_t KSocketStreamBuffer::GetUnReadDataSize()CONST{

	return  NULL;
}


BOOL KSocketStreamBuffer::GetPackage(KSPDynamicBuffer& spBuffer){

	return false;
}


BOOL KSocketStreamBuffer::AddUsedSize(const size_t nDataBytes){

	return false;
}