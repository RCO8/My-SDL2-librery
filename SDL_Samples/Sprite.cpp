#include "Sprite.h"

//스프라이트 불러와서 데이터에 저장
Sprite::Sprite(SDL_Renderer* getRenderer, const char* fileName) : sprRenderer(getRenderer)
{
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	imageFile = IMG_Load(fileName);	//이미지파일 로드
	if (imageFile == NULL)
	{
		SDL_Log("SDL Load BMP Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	//만약에 파일이 png, jpg, wepb라면 함수로 형태 교체
	sprTexture= SDL_CreateTextureFromSurface(sprRenderer, imageFile);	//이미지를 텍스쳐로
	if (sprTexture == NULL)
	{
		SDL_Log("SDL Texture Error : %s\n", SDL_GetError());
		this->~Sprite();
	}
	
	SetRotatePoint(0, 0);
}
//스프라이트 제거
Sprite::~Sprite()
{
	IMG_Quit();
	SDL_FreeSurface(imageFile);
	SDL_DestroyTexture(sprTexture);
	SDL_DestroyRenderer(sprRenderer);
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
void Sprite::SetSpriteScale(int w, int h)
{
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
//화면에 그리기
void Sprite::Drawing(int x, int y, int dir, int mirror)
{
	scrnRct.x = x;
	scrnRct.y = y;
	scrnRct.w = sprRct.w * scaleWidth;
	scrnRct.h = sprRct.h * scaleHeight;

	if (dir >= 360) dir -= 360;
	if (dir <= -360) dir -= 360;

	SDL_RenderCopyEx(sprRenderer, sprTexture, &sprRct, &scrnRct,
		dir, &rotatePoint, mirror ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
//전체화면으로 채우기
void Sprite::DrawFill() const
{
	SDL_RenderCopy(sprRenderer, sprTexture, NULL, NULL);
}
//스프라이트를 해당 색상으로 블렌드
void Sprite::SetColorBlend(SDL_Color setColor)
{
	SDL_SetTextureColorMod(sprTexture, setColor.r, setColor.g, setColor.b);
}
//스프라이트 투명화
void Sprite::SetImageAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(sprTexture, a);
}
/*여기서 확장 및 필요한 요소*/
//다른 확장자 파일(생성자에서 수정 필요)
//흑백, 반전
//이미지 흑백화
void Sprite::SetImageGrey()
{
	
}
//이미지 색상반전
void Sprite::SetImageNegative()
{
	
}
//컬러 팔레트 스왑 (픽셀에 색을 선택하면 다른색으로 변환)