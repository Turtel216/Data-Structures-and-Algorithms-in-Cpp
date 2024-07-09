#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <random>
#include <ranges>

// Run 'g++ -lSDL2 -std=c++20 insertion_sort_visualized.cpp'

// draw current state of the algorithm
void draw_state(std::vector<int> &v, SDL_Renderer *renderer, unsigned int red,
                unsigned int blue) {
  int index = 0;
  for (int i : v) {
    if (index == red)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if (index == blue)
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawLine(renderer, index, 99, index, i);
    index++;
  }
}

int main() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_CreateWindowAndRenderer(100 * 10, 100 * 10, 0, &window, &renderer);

  SDL_RenderSetScale(renderer, 10, 10);
  std::random_device rd;
  std::uniform_int_distribution d(1, 99);
  std::vector<int> v;

  // populate vector
  for (int i = 0; i < 100; i++) {
    v.push_back(d(rd));
  }

  int key, j;
  for (int i = 1; i < v.size(); i++) {
    key = v[i];
    j = i - 1;

    while (j >= 0 && v[j] < key) {
      v[j + 1] = v[j];
      j--;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      // Draw the state of the sort
      draw_state(v, renderer, i, j);
      // Show to the window
      SDL_RenderPresent(renderer);
      std::cout << "\007" << std::flush;
      SDL_Delay(7);
    }
    v[j + 1] = key;
  }

  return 0;
}
