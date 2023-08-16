#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int new_color = (image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) / 3;
            image[row][col].rgbtRed = new_color;
            image[row][col].rgbtGreen = new_color;
            image[row][col].rgbtBlue = new_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        int swap_col = width - 1;
        for (int col = 0; col < width; col++)
        {
            if (swap_col <= col)
            {
                break;
            }
            int temp_red = image[row][col].rgbtRed;
            int temp_green = image[row][col].rgbtGreen;
            int temp_blue = image[row][col].rgbtBlue;
            image[row][col].rgbtRed = image[row][swap_col].rgbtRed;
            image[row][col].rgbtGreen = image[row][swap_col].rgbtGreen;
            image[row][col].rgbtBlue = image[row][swap_col].rgbtBlue;
            image[row][swap_col].rgbtRed = temp_red;
            image[row][swap_col].rgbtGreen = temp_green;
            image[row][swap_col].rgbtBlue = temp_blue;
            swap_col--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int red_average = 0;
            int green_average = 0;
            int blue_average = 0;
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
            {
                int add_col = 0;
                int row_add = 0;
                red_average = image[row][col].rgbtRed;
                green_average = image[row][col].rgbtGreen;
                blue_average = image[row][col].rgbtBlue;
                if ((row == height - 1 || row == 0) && (col == 0 || col == width - 1))
                {
                    if (col == 0)
                    {
                        add_col = 1;
                    }
                    else if (col == width - 1)
                    {
                        add_col = -1;
                    }
                    if (row == 0)
                    {
                        row_add = 1;
                    }
                    else if (row == height - 1)
                    {
                        row_add = -1;
                    }
                    red_average += image[row][col + add_col].rgbtRed + image[row + row_add][col].rgbtRed + image[row + row_add][col + add_col].rgbtRed;
                    green_average += image[row][col + add_col].rgbtGreen + image[row + row_add][col].rgbtGreen + image[row + row_add][col + add_col].rgbtGreen;
                    blue_average += image[row][col + add_col].rgbtBlue + image[row + row_add][col].rgbtBlue + image[row + row_add][col + add_col].rgbtBlue;
                    image[row][col].rgbtRed = red_average / 4;
                    image[row][col].rgbtGreen = green_average / 4;
                    image[row][col].rgbtBlue = blue_average / 4;
                }
                else 
                {
                    if (col == 0 || col == width - 1)
                    {
                        if (col == 0)
                        {
                            add_col = 1;
                        }
                        else if (col == width - 1)
                        {
                            add_col = -1;
                        }
                        red_average += image[row][col + add_col].rgbtRed + image[row - 1][col].rgbtRed + image[row - 1][col + add_col].rgbtRed + image[row + 1][col].rgbtRed + image[row + 1][col + add_col].rgbtRed;
                        green_average += image[row][col + add_col].rgbtGreen + image[row - 1][col].rgbtGreen + image[row - 1][col + add_col].rgbtGreen + image[row + 1][col].rgbtGreen + image[row + 1][col + add_col].rgbtGreen;
                        blue_average += image[row][col + add_col].rgbtBlue + image[row - 1][col].rgbtBlue + image[row - 1][col + add_col].rgbtBlue + image[row + 1][col].rgbtBlue + image[row + 1][col + add_col].rgbtBlue;
                    }
                    else if (row == 0 || row == height - 1)
                    {
                        if (row == 0)
                        {
                            row_add = 1;
                        }
                        else if (row == height - 1)
                        {
                            row_add = -1;
                        }
                        red_average += image[row][col - 1].rgbtRed + image[row][col + 1].rgbtRed + image[row + row_add][col].rgbtRed + image[row + row_add][col - 1].rgbtRed + image[row + row_add][col + 1].rgbtRed;
                        green_average += image[row][col - 1].rgbtGreen + image[row][col + 1].rgbtGreen + image[row + row_add][col].rgbtGreen + image[row + row_add][col - 1].rgbtGreen + image[row + row_add][col + 1].rgbtGreen;
                        blue_average += image[row][col - 1].rgbtBlue + image[row][col + 1].rgbtBlue + image[row + row_add][col].rgbtBlue + image[row + row_add][col - 1].rgbtBlue + image[row + row_add][col + 1].rgbtBlue; 
                    }
                    image[row][col].rgbtRed = red_average / 6;
                    image[row][col].rgbtGreen = green_average / 6;
                    image[row][col].rgbtBlue = blue_average / 6;
                }
            }
            else
            {
                for (int cur_row = row - 1; cur_row <= row + 1; cur_row++)
                {    
                    for (int cur_col = col - 1; cur_col <= col + 1; cur_col++)
                    {
                        red_average += image[cur_row][cur_col].rgbtRed;
                        green_average += image[cur_row][cur_col].rgbtGreen; 
                        blue_average += image[cur_row][cur_col].rgbtBlue;  
                    }
                }
                image[row][col].rgbtRed = red_average / 9;
                image[row][col].rgbtGreen = green_average / 9;
                image[row][col].rgbtBlue = blue_average / 9;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx_array[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_array[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;
            int row_index = 0;
            int col_index = 0;
            for (int cur_row = row - 1; cur_row <= row + 1; cur_row++, row_index++)
            {
                for (int cur_col = col - 1; cur_col <= col + 1; cur_col++, col_index++)
                {
                    if ((cur_row >= 0 && cur_row < height) && (cur_col >= 0 && cur_col < width))
                    {
                        gx_red += image[cur_row][cur_col].rgbtRed * gx_array[row_index][col_index];
                        gx_green += image[cur_row][cur_col].rgbtGreen * gx_array[row_index][col_index];
                        gx_blue += image[cur_row][cur_col].rgbtBlue * gx_array[row_index][col_index];
                        gy_red += image[cur_row][cur_col].rgbtRed * gy_array[row_index][col_index];
                        gy_green += image[cur_row][cur_col].rgbtGreen * gy_array[row_index][col_index];
                        gy_blue += image[cur_row][cur_col].rgbtBlue * gy_array[row_index][col_index];
                    }
                }
            }
            int new_red_value = round(sqrt((gx_red ^ 2) + (gy_red ^ 2)));
            int new_green_value = round(sqrt((gx_green ^ 2) + (gy_green ^ 2)));
            int new_blue_value = round(sqrt((gx_blue ^ 2) + (gy_blue ^ 2)));
            if (new_red_value > 255)
            {
                new_red_value = 255;
            }
            if (new_green_value > 255)
            {
                new_green_value = 255;
            }
            if (new_blue_value > 255)
            {
                new_blue_value = 255;
            }
            image[row][col].rgbtRed = new_red_value;
            image[row][col].rgbtGreen = new_green_value;
            image[row][col].rgbtBlue = new_blue_value;
        }
    }
    return;
}
