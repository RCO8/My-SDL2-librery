#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
private:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//스프라이트 텍스쳐
	SDL_Surface* imageFile;		//이미지 리소스

	SDL_Rect sprRct;	//파일 내에서 출력될 Rect
	SDL_Rect scrnRct;	//실제 화면에 출력될 Rect

	Uint32 Color = 0;			//투명한 배경색으로 설정하기 위한 속성
	SDL_Point rotatePoint;		//스프라이트 회전중심점

	int scaleWidth = 1, scaleHeight = 1;	//확대 배율
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetSpriteClip(int x, int y, int w, int h);	//이미지 파일의 일부를 나타낼 설정
	void SetSpriteScale(int w, int h);				//크기 설정
	void SetRotatePoint(int x, int y);				//중심점 지정
	void SetColorHide(SDL_Color setColor);			//투명색 설정
	void Drawing(int x, int y, int dir, int mirror = 0);	//화면에 그리기
	void DrawFill() const;	//전체화면으로 채우기

	//파일의 각 너비 및 높이 반환
	int GetImageWidth() const { return imageFile->w; };
	int GetImageHeight() const { return imageFile->h; };
	//스프라이트 클립의 각 너비 및 높이 반환
	int GetClipWidth() const { return sprRct.w * scaleWidth; }
	int GetClipHeight() const { return sprRct.h * scaleHeight; }

	void SetColorBlend(SDL_Color setColor);	//해당 색상으로 블렌드
	void SetImageAlpha(Uint8 a);		//스프라이트 투명도
											/*여기서 확장 및 필요한 요소*/

	//컬러 팔레트 스왑 (픽셀에 색을 선택하면 다른색으로 변환)
	//흑백, 반전
	void SetImageGrey();	//이미지 흑백화
	void SetImageNegative();	//이미지 색반전
};