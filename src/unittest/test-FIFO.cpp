//==============================================================================
// test-FIFO.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

class Thread : public OAL::Thread {
private:
	RefPtr<Stream> _pStream;
public:
	Thread(Stream* pStream) : _pStream(pStream) {}
	virtual void Run() override;
};

void Thread::Run()
{
	char buff[4096];
	for (int i = 0; i < 100; i++) {
		::printf("write\n");
		_pStream->Write(buff, sizeof(buff));
	}
}

Gurax_TesterEntry(FIFO)
{
	RefPtr<Stream_FIFO> pStream(new Stream_FIFO(4096));
	RefPtr<Thread> pThread(new Thread(pStream->Reference()));
	pThread->Start();
	char buff[128];
	for (int i = 0; i < 100; i++) {
		size_t bytesRead = pStream->Read(buff, sizeof(buff));
		::printf("read: %zd\n", bytesRead);
	}
}

}
