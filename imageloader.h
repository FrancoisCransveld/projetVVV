/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*------Ce code à été en partie modifié par Francois Cransveld en mai 2022-----
	
	-modification de ce fichier:
		-L'ajout d'une variable booleen RGBA dans la structure Image 
*/
#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED
#include <stdbool.h>
//Represents an image
typedef struct Image_t {
		
		/* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
		 * color of each pixel in image.  Color components range from 0 to 255.
		 * The array starts the bottom-left pixel, then moves right to the end
		 * of the row, then moves up to the next column, and so on.  This is the
		 * format in which OpenGL likes images.
		 */
		unsigned char* pixels;
		int width;
		int height;
		bool RGBA;//variable booleen ajoutée par Francois Cransveld pour gérer la différence de format avec entre les ancienne version bitmap et la Version BITMAPV5HEADER qui comprend 32 bits divisé en 4 canal R(rouge) G(vert) B(bleu) A(alpha)
} Image;

//Reads a bitmap image from file.
Image* loadBMP(const char* filename);



#endif
