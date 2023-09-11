#pragma once

struct Vector2
{
	int x, y;
};

class Sprite
{
private:
	Vector2 startPos;	//��������Ʈ �׸��� ������ǥ
	Vector2 centerPos;	//��������Ʈ �߽���
	int width, height;
	int frame, maxFrame;	//��������Ʈ �����϶� ����ϴ� ������
	char filename[30];
public:
	Sprite();
	void AddonSprite();
	void SetCenterPos(int x, int y);
	void FrameLoop(int startFrame, int endFrame, int count);	//count���� start���� end���� �ݺ�
	void FrameSpin(int startFrame, int endFrame, int count);	//start���� end���� ���鼭 �ݺ�
	void FrameTimeline(int* getFrame);

	Vector2 GetPosition() const { return centerPos; }
};

Sprite::Sprite()
{
	//ó���� ��������Ʈ ������ �ҷ����� ������ ���� 1�� ����
}

void Sprite::SetCenterPos(int x, int y)
{
	centerPos.x = x;
	centerPos.y = y;
}

void Sprite::AddonSprite()
{

}

void Sprite::FrameLoop(int startFrame, int endFrame, int count)
{
	int tmp = 0;
	
	while (tmp < count)
	{
		//������ �ݺ�
		for (int idx = startFrame; idx = endFrame; idx++)
		{
			//��� ��������Ʈ
		}

		if(count > 0)	tmp++;	//���ѹݺ�
	}
}

void Sprite::FrameSpin(int startFrame, int endFrame, int count)
{
	int tmp = 0;
	int idx;

	while (tmp < count)
	{
		for (idx = startFrame; idx < endFrame; idx++)
		{

		}
		for (idx = endFrame; idx > startFrame; idx--)
		{

		}
		if (count > 0) tmp++;
	}
}

void Sprite::FrameTimeline(int* getFrame)
{
	//getFrame�� �ε��� ����ŭ ���
	int frameLength = sizeof(getFrame) / sizeof(int);
}