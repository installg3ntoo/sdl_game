#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    constexpr int window_width = 800;
    constexpr int window_height = 600;
    constexpr const char *message = "Hola Mundo";

    static_cast<void>(argc);
    static_cast<void>(argv);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "No se pudo inicializar SDL: %s",
            SDL_GetError());
        return 1;
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer(
            message,
            window_width,
            window_height,
            SDL_WINDOW_RESIZABLE,
            &window,
            &renderer))
    {
        SDL_LogError(
            SDL_LOG_CATEGORY_APPLICATION,
            "No se pudo crear la ventana: %s",
            SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        int output_width = 0;
        int output_height = 0;
        SDL_GetRenderOutputSize(renderer, &output_width, &output_height);

        constexpr float character_size = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        const float text_width =
            static_cast<float>(SDL_strlen(message)) * character_size;
        const float text_x =
            (static_cast<float>(output_width) - text_width) / 2.0F;
        const float text_y =
            (static_cast<float>(output_height) - character_size) / 2.0F;

        SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderDebugText(renderer, text_x, text_y, message);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
