#pragma once
class Cell
{
private:
	bool m_status = false;
public:
	//设置细胞的生命状态
	void setStatus(bool status);

	//更改细胞的生命状态 生-》死 死-》生
	void changeStatus();

	//获取细胞的生命状态
	bool IsLive();
};

