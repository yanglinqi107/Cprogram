#pragma once
class Cell
{
private:
	bool m_status = false;
public:
	//����ϸ��������״̬
	void setStatus(bool status);

	//����ϸ��������״̬ ��-���� ��-����
	void changeStatus();

	//��ȡϸ��������״̬
	bool IsLive();
};

