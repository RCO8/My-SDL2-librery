#include "Sprite.h"

//스프라이트 불러와서 데이터에 저장
Sprite::Sprite(SDL_Renderer* getRenderer, const char* fileName) : sprRenderer(getRenderer)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	imageFile = IMG_Load(fileName);	//이미지파일 로드
	if (imageFile == NULL)
	{
		SDL_Log("SDL Load Image Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	//만약에 파일이 png, jpg, wepb라면 함수로 형태 교체
	sprTexture= SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//이미지를 텍스쳐로
	if (sprTexture == NULL)
	{
		SDL_Log("SDL Texture Error : %s\n", SDL_GetError());
		this->~Sprite();
	}

	//팔레트 생성
	pixels = imageFile->format;
	palette = SDL_AllocPalette(256);	//최대 팔레트의 용량
	if (!(palette))
	{
		SDL_Log("SDL Palette Error!! %s", SDL_GetError());
		this->~Sprite();
	}

	SDL_LockSurface(imageFile);
	for (int y = 0; y < GetImageHeight(); y++)
		for (int x = 0; x < GetImageWidth(); x++)
		{
			Uint32 pixel = *(Uint32*)((Uint8*)imageFile->pixels + y * imageFile->pitch + x * sizeof(Uint32));
			SDL_Color color;
			SDL_GetRGBA(pixel, pixels, &color.r, &color.g, &color.b, &color.a);
			//만약 같은색이 있다면 스킵
			FindPaletteColor(color);
		}
	SDL_UnlockSurface(imageFile);
	
	SetSpriteClip(0, 0, GetImageWidth(), GetImageHeight());
	SetRotatePoint(0, 0);
}
//스프라이트 제거
Sprite::~Sprite()
{
	IMG_Quit();
	SDL_FreePalette(palette);
	SDL_FreeSurface(imageFile);
	SDL_DestroyTexture(sprTexture);
	SDL_DestroyRenderer(sprRenderer);
}
//같은 색이 중복되지 않게
void Sprite::FindPaletteColor(SDL_Color c)
{
	for (int i = 0; i < paletteCount; i++)
	{
		if (palette->colors[i].r == c.r && palette->colors[i].g == c.g
		 && palette->colors[i].b == c.b && palette->colors[i].a == c.a)
			return;//넘어감
	}
	palette->colors[paletteCount - 1] = c;
	SDL_Log("Palette : %d, %d, %d, %d",
		palette->colors[paletteCount - 1].r,palette->colors[paletteCount-1].g,
		palette->colors[paletteCount - 1].b, palette->colors[paletteCount - 1].a);
	paletteCount++;
}

//이미지 파일의 일부를 나타낼 설정
void Sprite::SetSpriteClip(int x, int y, int w, int h)
{
	sprRct.x = x;
	sprRct.y = y;
	sprRct.w = w;
	sprRct.h = h;
}
//크기 설정
void Sprite::SetSpriteScale(float w, float h)
{
	//SDL_ScaleModeLinear	흐리게
	//SDL_ScaleModeNearest	픽셀 선명화
	SDL_SetTextureScaleMode(sprTexture, SDL_ScaleModeNearest);	//축척 모드 실수형으로 정의
	SDL_SetTextureBlendMode(sprTexture, SDL_BLENDMODE_BLEND);	//칼라 모드 알파와 같이

	scaleWidth = w;
	scaleHeight = h;
}
//중심점 지정
void Sprite::SetRotatePoint(int x, int y)
{
	rotatePoint.x = x;
	rotatePoint.y = y;
}
//투명색 설정
void Sprite::SetColorHide(SDL_Color setColor)
{
	Color = SDL_MapRGB(imageFile->format, setColor.r, setColor.g, setColor.b);	//파일의 색을 Color에 지정
	SDL_SetColorKey(imageFile, SDL_TRUE, Color);	//파일의 배경색으로 지정
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//다시 파일을 Renderer로 갱신
}
void Sprite::SetColorHide(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Color = SDL_MapRGB(imageFile->format, r, g, b);
	SDL_SetColorKey(imageFile, SDL_TRUE, Color);
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);
}
//화면에 그리기
void Sprite::Drawing(int x, int y, int dir, bool mirror)
{
	scrnRct.x = x;
	scrnRct.y = y;
	scrnRct.w = sprRct.w * scaleWidth;
	scrnRct.h = sprRct.h * scaleHeight;

	if (dir >= 360) dir -= 360;
	if (dir <= -360) dir += 360;

	SDL_RenderSetScale(sprRenderer, scaleWidth, scaleHeight);

	SDL_RenderCopyEx(sprRenderer, sprTexture, &sprRct, &scrnRct,
		dir, &rotatePoint, mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
//전체화면으로 채우기
void Sprite::DrawFill() const	{ SDL_RenderCopy(sprRenderer, sprTexture, NULL, NULL); }
//스프라이트를 해당 색상으로 블렌드
void Sprite::SetColorBlend(Uint8 r, Uint8 g, Uint8 b)	{ SDL_SetTextureColorMod(sprTexture, r, g, b); }
void Sprite::SetColorBlend(SDL_Color setColor)	{ SDL_SetTextureColorMod(sprTexture, setColor.r, setColor.g, setColor.b); }
//스프라이트 투명화
void Sprite::SetImageAlpha(Uint8 a)	{ SDL_SetTextureAlphaMod(sprTexture, a); }

void Sprite::SetPaletteColor(int idx, SDL_Color c)
{
	//받은 색상을 픽셀에 적용
	SDL_LockSurface(imageFile);
	for (int y = 0; y < GetImageHeight(); ++y) {
		for (int x = 0; x < GetImageWidth(); ++x) {
			Uint32 pixel = *(Uint32*)((Uint8*)imageFile->pixels + y * imageFile->pitch + x * sizeof(Uint32));
			// 예시로 RGB(0,255,255)인 픽셀을 RGB(0,255,0)으로 변경Uint8 r, g, b;
			Uint8 R, G, B;
			SDL_GetRGB(pixel, imageFile->format, &B, &G, &R);
			if (R == palette->colors[idx].r && G == palette->colors[idx].g && B == palette->colors[idx].b) {
				pixel = SDL_MapRGB(imageFile->format, c.r, c.g, c.b);
			}
			*(Uint32*)((Uint8*)imageFile->pixels + y * imageFile->pitch + x * sizeof(Uint32)) = pixel;
		}
	}
	SDL_UnlockSurface(imageFile);

	palette->colors[idx] = c;
	SDL_SetPaletteColors(palette, &palette->colors[idx], idx, idx + 1);
	SDL_SetSurfacePalette(imageFile, palette);
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);
}
void Sprite::SetPaletteColor(int idx, Uint8 r, Uint8 g, Uint8 b)
{
	//받은 색상을 픽셀에 적용
	SDL_LockSurface(imageFile);
	for (int y = 0; y < GetImageHeight(); ++y) {
		for (int x = 0; x < GetImageWidth(); ++x) {
			Uint32 pixel = *(Uint32*)((Uint8*)imageFile->pixels + y * imageFile->pitch + x * sizeof(Uint32));
			// 예시로 RGB(0,255,255)인 픽셀을 RGB(0,255,0)으로 변경Uint8 r, g, b;
			Uint8 R, G, B;
			SDL_GetRGB(pixel, imageFile->format, &B, &G, &R);
			if (R == palette->colors[idx].r && G == palette->colors[idx].g && B == palette->colors[idx].b) {
				pixel = SDL_MapRGB(imageFile->format, r, g, b);
			}
			*(Uint32*)((Uint8*)imageFile->pixels + y * imageFile->pitch + x * sizeof(Uint32)) = pixel;
		}
	}
	SDL_UnlockSurface(imageFile);

	palette->colors[idx] = { r,g,b,a };
	SDL_SetPaletteColors(palette, &palette->colors[idx], idx, idx + 1);
	SDL_SetSurfacePalette(imageFile, palette);
	sprTexture = SDL_CreateTextureFromSurface(sprRenderer, imageFile);
}
void Sprite::SetPaletteDirect(SDL_Palette pal)
{
	SDL_Log("보수중...");
	SDL_SetSurfacePalette(imageFile, palette);
}