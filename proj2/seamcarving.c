#include "seamcarving.h"
#include "c_img.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

// The function will compute the dual-gradient energy function, and place it in
// the struct rgb_img *grad
void calc_energy(struct rgb_img *im, struct rgb_img **grad)
{
      create_img(grad, im->height, im->width);
      // declarations
      double r_x, g_x, b_x;
      double r_y, g_y, b_y;
      double energy;

      for (int y = 0; y < im->height; y++)
      {
            for (int x = 0; x < im->width; x++)
            {
                  /*
                  r_x = get_pixel(im, y, (x + 1) % im->width, 0) -
                        get_pixel(im, y, (x - 1) % im->width, 0);
                  g_x = get_pixel(im, y, (x + 1) % im->width, 1) -
                        get_pixel(im, y, (x - 1) % im->width, 1);
                  b_x = get_pixel(im, y, (x + 1) % im->width, 2) -
                        get_pixel(im, y, (x - 1) % im->width, 2);
                  r_y = get_pixel(im, (y + 1) % im->height, x, 0) -
                        get_pixel(im, (y - 1) % im->height, x, 0);
                  g_y = get_pixel(im, (y + 1) % im->height, x, 1) -
                        get_pixel(im, (y - 1) % im->height, x, 1);
                  b_y = get_pixel(im, (y + 1) % im->height, x, 2) -
                        get_pixel(im, (y - 1) % im->height, x, 2);
                  */
                  r_x = get_pixel(im, y, (x + 1) % im->width, 0) - get_pixel(im, y, (x - 1 + im->width) % im->width, 0);
                  g_x = get_pixel(im, y, (x + 1) % im->width, 1) - get_pixel(im, y, (x - 1 + im->width) % im->width, 1);
                  b_x = get_pixel(im, y, (x + 1) % im->width, 2) - get_pixel(im, y, (x - 1 + im->width) % im->width, 2);
                  r_y = get_pixel(im, (y + 1) % im->height, x, 0) - get_pixel(im, (y - 1 + im->height) % im->height, x, 0);
                  g_y = get_pixel(im, (y + 1) % im->height, x, 1) - get_pixel(im, (y - 1 + im->height) % im->height, x, 1);
                  b_y = get_pixel(im, (y + 1) % im->height, x, 2) - get_pixel(im, (y - 1 + im->height) % im->height, x, 2);

                  energy = (uint8_t)(sqrt(pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2) +
                                          pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2)) /
                                     10);

                  set_pixel(*grad, y, x, energy, energy, energy);
            }
      }
}
void dynamic_seam(struct rgb_img *grad, double **best_arr)
{

      *best_arr = malloc(sizeof(double) * grad->height * grad->width);
      // allocates and computes the dynamic array *best_arr.
      // (*best_arr)[i*width+j] contains the minimum cost of a seam from the top of
      // grad to the point (i,j) pass in "grad" --> same one passed into calc_energy
      // which stores the energy diagram optimal path (minimize) while considering
      // 1d array in 2 dimensions
      for (int y = 0; y < grad->height; y++)
      {
            for (int x = 0; x < grad->width; x++)
            {
                  int min;
                  if (y == 0)
                  {
                        (*best_arr)[y * grad->width + x] = get_pixel(grad, y, x, 0);
                  }
                  else if (x == 0)
                  {
                        // check the top and the right
                        min = (*best_arr)[(y - 1) * grad->width + x];
                        if (min > (*best_arr)[(y - 1) * grad->width + x + 1])
                        {
                              min = (*best_arr)[(y - 1) * grad->width + x + 1];
                        }
                  }
                  else if (x == grad->width - 1)
                  {
                        // check the top and the left
                        min = (*best_arr)[(y - 1) * grad->width + x];
                        if (min > (*best_arr)[(y - 1) * grad->width + x - 1])
                        {
                              min = (*best_arr)[(y - 1) * grad->width + x - 1];
                        }
                  }
                  else
                  {
                        // check left, top, right
                        min = (*best_arr)[(y - 1) * grad->width + x];
                        if (min > (*best_arr)[(y - 1) * grad->width + x + 1])
                        {
                              min = (*best_arr)[(y - 1) * grad->width + x + 1];
                        }
                        if (min > (*best_arr)[(y - 1) * grad->width + x - 1])
                        {
                              min = (*best_arr)[(y - 1) * grad->width + x - 1];
                        }
                  }

                  (*best_arr)[y * grad->width + x] = get_pixel(grad, y, x, 0) + min;
            }
      }
}

void recover_path(double *best, int height, int width, int **path)
{
      // pass in the same array as best_arr from dynamic_seam
      // *path points to the new array that stores the path
      // height and width of the image?
      // goes from bottom up
      double min_sum;
      int cur_index, update_index;
      *path = malloc(sizeof(int) * height);

      min_sum = best[(height - 1) * width];
      for (int i = 0; i < width; i++)
      {
            if (min_sum > best[(height - 1) * width + i])
            {
                  min_sum = best[(height - 1) * width + i];
                  cur_index = (height - 1) * width + i;
            }
      }
      // now look backwards to find the path taken to get to min_sum

      for (int j = height - 1; j >= 0; j--)
      {
            (*path)[j] = cur_index % width;
            // check to see which is smallest beside you
            /*  if current index is at the left corner
                    check the above, right
                else if current index is in right,
                    check left, above, left
                else
                    check above, left, right
            */
            // left edges
            if (cur_index % width == 0)
            {
                  min_sum = best[cur_index - width];
                  update_index = cur_index - width;
                  if (min_sum > best[cur_index - width + 1])
                  {
                        min_sum = best[cur_index - width + 1];
                        update_index = cur_index - width + 1;
                  }
                  // right edges
            }
            else if (cur_index % width == width - 1)
            {
                  min_sum = best[cur_index - width];
                  update_index = cur_index - width;
                  if (min_sum > best[cur_index - width - 1])
                  {
                        min_sum = best[cur_index - width - 1];
                        update_index = cur_index - width - 1;
                  }
            }
            else
            {
                  min_sum = best[cur_index - width];
                  update_index = cur_index - width;
                  if (min_sum > best[cur_index - width + 1])
                  {
                        min_sum = best[cur_index - width + 1];
                        update_index = cur_index - width + 1;
                  }
                  if (min_sum > best[cur_index - width - 1])
                  {
                        min_sum = best[cur_index - width - 1];
                        update_index = cur_index - width - 1;
                  }
            }
            cur_index = update_index;
      }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path)
{
      create_img(dest, src->height, src->width - 1);
      double r, g, b;
      for (int y = 0; y < src->height; y++)
      {
            int reach_weird = 0;
            for (int x = 0; x < src->width; x++)
            {
                  if (x != path[y])
                  {
                        r = get_pixel(src, y, x, 0);
                        g = get_pixel(src, y, x, 1);
                        b = get_pixel(src, y, x, 2);
                        set_pixel(*dest, y, x - reach_weird, r, g, b);
                  }
                  else
                  {
                        reach_weird = 1;
                  }
            }
      }
}