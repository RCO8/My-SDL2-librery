#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Sprite
{
private:
	SDL_Renderer* sprRenderer;
	SDL_Texture* sprTexture;	//스프라이트 텍스쳐
	SDL_Surface* imageFile;		//이미지 리소스

	SDL_Palette *palette;	//팔레트
	int paletteCount = 1;

	SDL_Rect sprRct;	//파일 내에서 출력될 Rect
	SDL_Rect scrnRct;	//실제 화면에 출력될 Rect

	Uint32 Color = 0;			//투명한 배경색으로 설정하기 위한 속성
	SDL_Point rotatePoint;		//스프라이트 회전중심점

	float scaleWidth = 1, scaleHeight = 1;	//확대 배율

	void FindPaletteColor(SDL_Color c);	//팔레트 중복 검사용
public:
	Sprite(SDL_Renderer* getRenderer, const char* fileName);
	~Sprite();

	void SetSpriteClip(int x, int y, int w, int h);	//이미지 파일의 일부를 나타낼 설정
	void SetSpriteClip(SDL_Rect rct) { sprRct = rct; }
	void SetSpriteScale(float w, float h);				//크기 설정
	void SetRotatePoint(int x, int y);				//중심점 지정
	void SetColorHide(SDL_Color setColor);			//투명색 설정
	void SetColorHide(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void Drawing(int x, int y, int dir, bool mirror = 0);	//화면에 그리기
	void DrawFill() const;	//전체화면으로 채우기

	//파일의 각 너비 및 높이 반환
	int GetImageWidth() const { return imageFile->w; };
	int GetImageHeight() const { return imageFile->h; };
	//스프라이트 클립의 각 너비 및 높이 반환
	int GetClipWidth() const { return sprRct.w * scaleWidth; }
	int GetClipHeight() const { return sprRct.h * scaleHeight; }

	void SetColorBlend(Uint8 r, Uint8 g, Uint8 b);	//해당 색상으로 블렌드
	void SetColorBlend(SDL_Color setColor);	
	void SetImageAlpha(Uint8 a);		//스프라이트 투명도

	//팔레트 옵션
	void SetPaletteColor(int idx, SDL_Color c);
	void SetPaletteColor(int idx, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xff);
	void SetPaletteDirect(SDL_Palette *pal);
	SDL_Color GetPaletteColor(int idx) { if(idx < paletteCount-1) return palette->colors[idx]; };
	int GetPaletteLength() { return paletteCount-1; }
};