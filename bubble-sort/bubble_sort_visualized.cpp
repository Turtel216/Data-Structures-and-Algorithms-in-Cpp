#include<SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <algorithm>
#include <random>
#include<ranges>
#include <utility>

// Run 'g++ -lSDL2 -std=c++20 bubble_sort_visualized.cpp'

// draw current state of the algorithm
void draw_state(std::vector<int>& v, SDL_Renderer* renderer,
                unsigned int red, unsigned int blue)
{
  int index = 0;
  for (int i : v)
  {
    if (index == red)
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if (index == blue)
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    else 
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawLine(renderer, index, 99, index, i);
    index ++;
  }
}

int main()
{
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(
    100 * 10, 100 * 10, 0,
    &window, &renderer
  );

  SDL_RenderSetScale(renderer, 10, 10);
  std::random_device rd;
  std::uniform_int_distribution d(1, 99);
  std::vector<int> v;

  // populate vector
  for (int i = 0; i < 100; i++)
  {
    v.push_back(d(rd));
  }

  // bubble sort algorithm
  while (!std::is_sorted(v.begin(), v.end()))
  {
    for (unsigned int i = 0; i < v.size() - 1; i++)
    {
      if (v[i] > v[i + 1]) std::swap(v[i], v[i + 1]);
      // clear screen 
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      // Draw the state of the sort 
      draw_state(v, renderer, i, i+1);
      // Show to the window
      SDL_RenderPresent(renderer);
      SDL_Delay(3);
    }
  }
  return 0;
}
