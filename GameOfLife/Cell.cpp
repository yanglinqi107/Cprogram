#include "pch.h"
#include "Cell.h"

void Cell::setStatus(bool status)
{
	m_status = status;
}

void Cell::changeStatus()
{
	m_status = !m_status;
}

bool Cell::IsLive()
{
	return m_status;
}
