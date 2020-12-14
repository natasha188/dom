#include <iostream>
#include <memory>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
constexpr int WIDTH = 1000, HEIGHT = 720, R = 25;

std::shared_ptr<SDL_Texture> icon;
std::shared_ptr<SDL_Texture> icon2;

std::shared_ptr<SDL_Texture> Make_icon(SDL_Renderer *renderer, const char *name)
{

	std::shared_ptr<SDL_Texture> foto = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(renderer, name),
			SDL_DestroyTexture);
	if(foto == nullptr)
	{
		std::cerr << "Что-то пошло не так. Не удается загрузить картинку." <<
		SDL_GetError()<<std::endl;
		return nullptr;
	}
	return foto;
}

void DrawCircle(SDL_Renderer * ren, int x, int y, int r, int X, int Y)
{
            int delta = 1 - 2 * r;
            int error = 0;
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);

            while(y >= 0)
            {
                SDL_RenderDrawPoint(ren, X + x, Y + y);
                SDL_RenderDrawPoint(ren, X + x, Y - y);
                SDL_RenderDrawPoint(ren, X - x, Y + y);
                SDL_RenderDrawPoint(ren, X - x, Y - y);
                error = 2 * (delta + y) - 1;
                if (delta < 0 and error <= 0)
                {
                    ++x;
                    delta += 2 * x + 1;
                    continue;
                }
                if (delta > 0 and error > 0)
                {
                    --y;
                    delta -= 2 * y + 1;
                    continue;
                }
                ++x;
                --y;
                delta += 2 * (x - y);
            }
}
int main(int, char **)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    auto win = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow("DOM_Veymer",
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    WIDTH, HEIGHT,
                    SDL_WINDOW_SHOWN),
            SDL_DestroyWindow);
    if (win == nullptr) {
        std::cerr << "Что-то пошло не так. Возникла ошибка при создании окна: " <<
                SDL_GetError() << std::endl;
        return 1;
    }
    auto ren = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(win.get(), -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer);
    if (ren == nullptr) {
        std::cerr << "Что-то пошло не так. Возникла ошибка при создании рендерера: " <<
                SDL_GetError() << std::endl;
        return 1;
    }


	bool f = true;
	int icon_x = - 50, icon_y = 500;// координаты появления коровы
	bool f2 = true;
	int icon_x2 = 500, icon_y2 = 600;// координаты появления козы

	auto keys = SDL_GetKeyboardState(nullptr);

    SDL_Event event;
    bool finish = false;
    // Основной цикл
    while (not finish)
    {
        // Цикл обработки
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                finish = true;
        }

        //Небо
        SDL_SetRenderDrawColor(ren.get(), 78, 82, 222, 1);
        SDL_RenderClear(ren.get());

        //Земля
        SDL_Rect r { 0, 525, WIDTH, 220 };
        SDL_SetRenderDrawColor(ren.get(), 20, 222, 40, 1);
        SDL_RenderFillRect(ren.get(), &r);

        //Забор
        for (int i = 5; i < WIDTH; i += 40) {
        	SDL_SetRenderDrawColor(ren.get(), 255,129,28,255);// палки на заборе
            SDL_Rect r1 { i, 380, 30, 150 };
            SDL_RenderFillRect(ren.get(), &r1);
            SDL_Rect r2 { i + 30, 430, 10, 20 };
            SDL_RenderFillRect(ren.get(), &r2);
            SDL_SetRenderDrawColor(ren.get(), 255,129,28,255);// треугольник на заборе
            for (double x1 = i+14 , x2 = i+14 ,  y = 365; y < 380; x1--, x2++, y++)
            { SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
            } }

        //Дом
        SDL_Rect r1 { WIDTH / 2 - 150, 200, 400, 400 };
        SDL_SetRenderDrawColor(ren.get(), 237, 194, 225, 1);
        SDL_RenderFillRect(ren.get(), &r1);

        //Труба
        SDL_Rect r4 { WIDTH / 2 - 90, 100, 30, 60 };
        SDL_SetRenderDrawColor(ren.get(), 119, 0, 0, 255);
        SDL_RenderFillRect(ren.get(), &r4);

        //Крыша
        SDL_SetRenderDrawColor(ren.get(), 119, 0, 0, 255);
        for (double x1 = WIDTH / 2 + 50, x2 =WIDTH / 2 + 50,  y = 80; y < 200; x1 -= 1.80, x2 += 1.80, y++) {
            SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
        }

        //Окно на крыше
        DrawCircle(ren.get(), 0, R, R, WIDTH / 2 + 50, 150);

        //Окно1
        SDL_Rect r2 { WIDTH / 2 - 100, 200 + 100, 90, 120 };
        SDL_SetRenderDrawColor(ren.get(), 242, 255, 0, 1);
        SDL_RenderFillRect(ren.get(), &r2);

        SDL_SetRenderDrawColor(ren.get(), 107, 75, 26, 1);// рама вертикаль
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 - 55, 300 , WIDTH / 2 -55, 420);

        SDL_SetRenderDrawColor(ren.get(), 107, 75, 26, 1);// рама горизонталь
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 - 100, 350, WIDTH / 2 - 10, 350);

        //Окно2
        SDL_Rect r3 { WIDTH / 2 + 100, 200 + 100, 90, 120 };
        SDL_SetRenderDrawColor(ren.get(), 242, 255, 0, 1);
        SDL_RenderFillRect(ren.get(), &r3);

        SDL_SetRenderDrawColor(ren.get(), 107, 75, 26, 1);
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 145, 300 , WIDTH / 2 +145, 420);

        SDL_SetRenderDrawColor(ren.get(), 107, 75, 26, 1);
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 +100, 350, WIDTH / 2 +190, 350);

        //Дверь
        SDL_Rect r5 { WIDTH / 2 + 25 , 450, 80, 150 };
        SDL_SetRenderDrawColor(ren.get(), 116,47,0,255);
        SDL_RenderFillRect(ren.get(), &r5);

        // Ручка на двери
        SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 255);
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 90, 510 , WIDTH / 2 +90, 530);

        //Трава1
        SDL_SetRenderDrawColor(ren.get(), 11, 156, 42, 1);
        for(int i = 0; i <= 18; i += 3)
            for (int x = 15 + i,  y1 = HEIGHT - i, y2 = HEIGHT - (i+50) ; x < WIDTH - 15; x += 50 )
                SDL_RenderDrawLine(ren.get(), x, y1, x, y2);

        //Трава2
               SDL_SetRenderDrawColor(ren.get(), 11, 156, 42, 1);
               for(int i = 0; i <= 16; i += 4)
                   for (int x = 50 + i,  y1 = HEIGHT - i-30, y2 = HEIGHT - (i+80) ; x < WIDTH - 50; x += 50 )
                       SDL_RenderDrawLine(ren.get(), x, y1, x, y2);

		//Коза
		if(icon_x2 < WIDTH - 150 and f2){
			icon2 = Make_icon(ren.get(), "koza_r.png");
			icon_x2 += 5;//её скорость
		}
		else f2 = false;
		if(icon_x2 > 0 and !f2){
			icon2 = Make_icon(ren.get(), "koza_l.png");
			icon_x2 -= 5;
		}
		else f2 = true;

		if(icon2 == nullptr) return 1;
		SDL_Rect icon_rect2 {icon_x2, icon_y2, 120, 120};
		SDL_RenderCopy(ren.get(), icon2.get(), nullptr, &icon_rect2);

		//Корова
		if (f)
			icon = Make_icon(ren.get(), "korova_r.png");
		else
			icon = Make_icon(ren.get(), "korova_l.png");

		if(keys[SDL_SCANCODE_RIGHT] and icon_x < WIDTH - 100){ icon_x += 6; f = true;}
		if(keys[SDL_SCANCODE_LEFT] and icon_x > 0 ){ icon_x -= 6; f = false;}
		if(keys[SDL_SCANCODE_UP] and icon_y > 0){ icon_y -= 6; }
		if(keys[SDL_SCANCODE_DOWN] and icon_y < HEIGHT - 10){ icon_y += 6; }

		if(icon == nullptr) return 1;
		SDL_Rect icon_rect {icon_x, icon_y, 280, 190};
		SDL_RenderCopy(ren.get(), icon.get(), nullptr, &icon_rect);

        SDL_RenderPresent(ren.get());
        }
        return 0;
}
