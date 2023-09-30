#include "RequestHandler.h"
RequestHandler::RequestHandler() 
{
	m_tpool.start();
}
RequestHandler::~RequestHandler() 
{
	m_tpool.stop();
}
void RequestHandler::pushRequest(FuncType f, std::shared_ptr<int[]> arr, long left, long right)
{
	m_tpool.push_task(f, arr, left, right);
}