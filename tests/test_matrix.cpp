/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
* Description : Runs tests for the p2Mat22 and p2Mat33 classes
* Last succeed run : 04.04.2018
* Author : Duncan Bourquard
*/

#include <iostream>

#include <p2matrix.h>

void printResult(bool isOk)
{
	if (isOk)
		std::cout << "OK \n\n";
	else
		std::cout << "NOT OK \n\n";
}


int main()
{
	std::cout << "--------------------------------------------------------\n";
	std::cout << "------------------- TEST OF P2MAT22 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";
	{
		p2Mat22 mat1 = p2Mat22(p2Vec2(3.0f, 5.0f), p2Vec2(2.0f, 4.0f));
		p2Mat22 mat2 = p2Mat22(p2Vec2(1.0f, 4.0f), p2Vec2(3.0f, 6.0f));

		// p2Mat22 : +
		{
			p2Mat22	mat3 = mat1 + mat2;
			std::cout << "p2Mat22 : +\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(4.0f, 9.0f), p2Vec2(5.0f, 10.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : +=
		{
			p2Mat22	mat3 = mat1;
			mat3 += mat2;
			std::cout << "p2Mat22 : +=\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(4.0f, 9.0f), p2Vec2(5.0f, 10.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : -
		{
			p2Mat22	mat3 = mat1 - mat2;
			std::cout << "p2Mat22 : -\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(2.0f, 1.0f), p2Vec2(-1.0f, -2.0f));
			printResult(mat3 == result);
		}
	
		// p2Mat22 : -=
		{
			p2Mat22	mat3 = mat1;
			mat3 -= mat2;
			std::cout << "p2Mat22 : -=\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(2.0f, 1.0f), p2Vec2(-1.0f, -2.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : * p2Mat22
		{
			p2Mat22	mat3 = mat1 * mat2;
			std::cout << "p2Mat22 : * p2Mat22\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(11.0f, 21.0f), p2Vec2(21.0f, 39.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : *= p2Mat22
		{
			p2Mat22	mat3 = mat1;
			mat3 *= mat2;
			std::cout << "p2Mat22 : *= p2Mat22\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(11.0f, 21.0f), p2Vec2(21.0f, 39.0f));
			printResult(mat3 == result);
		}
	
		// p2Mat22 : * p2Vec2
		{
			p2Vec2 v = p2Vec2(3.0f, 2.0f);
			p2Vec2 v2 = mat1 * v;
			std::cout << "p2Mat22 : * p2Vec2\n";
			std::cout << "| " << v2.x << " | " << v2.y << " |\n";
			p2Vec2 result = p2Vec2(13.0f, 23.0f);
			printResult(v2 == result);
		}

		// p2Mat22 : * float
		{
			float multiplier = 1.66f;
			p2Mat22	mat3 = mat1 * multiplier;
			std::cout << "p2Mat22 : * Float\n";
			std::cout << "Multiplier : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(4.98f, 8.3f), p2Vec2(3.32f, 6.64f));
			printResult(mat3 == result);
		}

		// p2Mat22 : *= float
		{
			float multiplier = 1.66f;
			p2Mat22	mat3 = mat1;
			mat3 *= multiplier;
			std::cout << "p2Mat22 : *= Float\n";
			std::cout << "Multiplier : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(4.98f, 8.3f), p2Vec2(3.32f, 6.64f));
			printResult(mat3 == result);
		}

		// p2Mat22 : / float
		{
			float multiplier = 2.0f;
			p2Mat22	mat3 = mat1 / multiplier;
			std::cout << "p2Mat22 : / Float\n";
			std::cout << "Divider : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(1.5f, 2.5f), p2Vec2(1.0f, 2.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : /= float
		{
			float multiplier = 2.0f;
			p2Mat22	mat3 = mat1;
			mat3 /= multiplier;
			std::cout << "p2Mat22 : /= Float\n";
			std::cout << "Divider : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(1.5f, 2.5f), p2Vec2(1.0f, 2.0f));
			printResult(mat3 == result);
		}

		// p2Mat22 : Invert
		{
			p2Mat22 mat3 = mat1.Invert();
			std::cout << "p2Mat22 : Invert\n";
			mat3.printDebug();
			p2Mat22 result = p2Mat22(p2Vec2(2.0f, -2.5f), p2Vec2(-1.0f, 1.5f));
			printResult(mat3 == result);
		}

		// p2Mat22 : Determinant
		{
			float det = mat1.GetDeterminant();
			std::cout << "p2Mat22 : Determinant\n";
			std::cout << "Det : " << det << "\n";
			float result = 2.0f;
			printResult(det == result);
		}
	}


	std::cout << "--------------------------------------------------------\n";
	std::cout << "------------------- TEST OF P2MAT33 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";
	{
		p2Mat33 mat1 = p2Mat33(p2Vec3(3.0f, 5.0f, 3.0f), p2Vec3(-2.0f, 4.0f, 1.5f), p2Vec3(1.0f, -3.5f, 1.5f));
		p2Mat33 mat2 = p2Mat33(p2Vec3(1.0f, -4.0f, 6.0f), p2Vec3(3.0f, 6.0f, 1.0f), p2Vec3(1.0f, 4.0f, -1.5f));

		// p2Mat22 : +
		{
			p2Mat33	mat3 = mat1 + mat2;
			std::cout << "p2Mat33 : +\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(4.0f, 1.0f, 9.0f), p2Vec3(1.0f, 10.0f, 2.5f), p2Vec3(2.0f, 0.5f, 0.0f));
			printResult(mat3 == result);
		}

		// p2Mat33 : +=
		{
			p2Mat33	mat3 = mat1;
			mat3 += mat2;
			std::cout << "p2Mat33 : +=\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(4.0f, 1.0f, 9.0f), p2Vec3(1.0f, 10.0f, 2.5f), p2Vec3(2.0f, 0.5f, 0.0f));
			printResult(mat3 == result);
		}

		// p2Mat33 : -
		{
			p2Mat33	mat3 = mat1 - mat2;
			std::cout << "p2Mat33 : -\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(2.0f, 9.0f, -3.0f), p2Vec3(-5.0f, -2.0f, 0.5f), p2Vec3(0.0f, -7.5f, 3.0f));
			printResult(mat3 == result);
		}

		// p2Mat33 : -=
		{
			p2Mat33	mat3 = mat1;
			mat3 -= mat2;
			std::cout << "p2Mat33 : -=\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(2.0f, 9.0f, -3.0f), p2Vec3(-5.0f, -2.0f, 0.5f), p2Vec3(0.0f, -7.5f, 3.0f));
			printResult(mat3 == result);
		}

		// p2Mat33 : * p2Mat33
		{
			p2Mat33	mat3 = mat1 * mat2;
			std::cout << "p2Mat33 : * p2Mat33\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(17.0f, -32.0f, 6.0f), p2Vec3(-2.0f, 35.5f, 19.5f), p2Vec3(-6.5f, 26.25f, 6.75f));
			printResult(mat3 == result);
		}

		// p2Mat33 : *= p2Mat33
		{
			p2Mat33	mat3 = mat1;
			mat3 *= mat2;
			std::cout << "p2Mat33 : *= p2Mat33\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(17.0f, -32.0f, 6.0f), p2Vec3(-2.0f, 35.5f, 19.5f), p2Vec3(-6.5f, 26.25f, 6.75f));
			printResult(mat3 == result);
		}

		// p2Mat33 : * p2Vec3
		{
			p2Vec3 v = p2Vec3(3.0f, 2.0f, 1.0f);
			p2Vec3 v2 = mat1 * v;
			std::cout << "p2Mat33 : * p2Vec3\n";
			std::cout << "| " << v2.x << " | " << v2.y << " |  " << v2.z << " |\n";
			p2Vec3 result = p2Vec3(6.0f, 19.5f, 13.5f);
			printResult(v2 == result);
		}

		// p2Mat33 : * float
		{
			float multiplier = 3.0f;
			p2Mat33	mat3 = mat1 * multiplier;
			std::cout << "p2Mat33 : * Float\n";
			std::cout << "Multiplier : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(9.0f, 15.0f, 9.0f), p2Vec3(-6.0f, 12.0f, 4.5f), p2Vec3(3.0f, -10.5f, 4.5f));
			printResult(mat3 == result);
		}

		// p2Mat33 : *= float
		{
			float multiplier = 3.0f;
			p2Mat33	mat3 = mat1;
			mat3 *= multiplier;
			std::cout << "p2Mat33 : *= Float\n";
			std::cout << "Multiplier : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(9.0f, 15.0f, 9.0f), p2Vec3(-6.0f, 12.0f, 4.5f), p2Vec3(3.0f, -10.5f, 4.5f));
			printResult(mat3 == result);
		}

		// p2Mat33 : / float
		{
			float multiplier = 2.0f;
			p2Mat33	mat3 = mat1 / multiplier;
			std::cout << "p2Mat33 : / Float\n";
			std::cout << "Divider : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(1.5f, 2.5f, 1.5f), p2Vec3(-1.0f, 2.0f, 0.75f), p2Vec3(0.5f, -1.75f, 0.75f));
			printResult(mat3 == result);
		}

		// p2Mat33 : /= float
		{
			float multiplier = 2.0f;
			p2Mat33	mat3 = mat1;
			mat3 /= multiplier;
			std::cout << "p2Mat33 : /= Float\n";
			std::cout << "Divider : " << multiplier << "\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(1.5f, 2.5f, 1.5f), p2Vec3(-1.0f, 2.0f, 0.75f), p2Vec3(0.5f, -1.75f, 0.75f));
			printResult(mat3 == result);
		}

		// p2Mat33 : Invert
		{
			p2Mat33 mat3 = mat1.Invert();
			std::cout << "p2Mat33 : Invert\n";
			mat3.printDebug();
			p2Mat33 result = p2Mat33(p2Vec3(0.172414f, -0.275862f, -0.0689655f), p2Vec3(0.0689655f, 0.0229885f, -0.16092f), p2Vec3(0.045977f, 0.237548f, 0.337165f));
			std::cout << "Should be : \n";
			result.printDebug();
		}

		// p2Mat33 : Determinant
		{
			float det = mat1.GetDeterminant();
			std::cout << "p2Mat33 : Determinant\n";
			std::cout << "Det : " << det << "\n";
			float result = 65.25f;
			printResult(det == result);
		}
	}


	std::cout << "end!\n";

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
