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
* Description : Runs tests for the p2Vec2 and p2Vec3 classes
* Last succeed run : 03.04.2018
* Author : Duncan Bourquard
*/

#include <iostream>

#include <p2vector.h>

void printResult(bool isOk)
{
	if (isOk)
		std::cout << "OK \n\n";
	else
		std::cout << "NOT OK \n\n";
}


int main()
{
	p2Vec2 v1 = p2Vec2(1.0f, 2.0f);
	p2Vec2 v2 = p2Vec2(3.0, 4.0f);
	p2Vec2 v3, result;
	float fResult;

	float multiplier = 2.0f;

	std::cout << "--------------------------------------------------------\n";
	std::cout << "--------------- TEST DES VECTEURS 2 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";

	// p2Vec2 : +
	{
		//Operation
		v3 = v1 + v2;
		std::cout << "addition + : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(4.0f, 6.0f);
		printResult(v3 == result);
	}
	
	// p2Vec2 : +=	
	{
		//Operation
		v3 = v1;
		v3 += v2;
		std::cout << "addition += : " << v3.x << ", " << v3.y << ";\n";

		//Check
		result = p2Vec2(4.0f, 6.0f);
		printResult(v3 == result);
	}

	// p2Vec2 : -
	{
		//Operation
		v3 = v1 - v2;
		std::cout << "soustraction - : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(-2.0f, -2.0f);
		printResult(v3 == result);
	}

	// p2Vec2 : -=
	{
		//
		v3 = v1;
		v3 -= v2;
		std::cout << "backtoNormal -= : " << v3.x << ", " << v3.y << ";\n";

		//Operation
		result = p2Vec2(-2.0f, -2.0f);
		printResult(v3 == result);
	}

	std::cout << "\n\n";

	// p2Vec2 : *
	{
		//Operation
		v3 = v1 * multiplier;
		std::cout << "multiplier *= : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(2.0f, 4.0f);
		printResult(v3 == result);
	}

	// p2Vec2 : *=
	{
		//Operation
		v3 = v1;
		v3 *= multiplier;
		std::cout << "multiplier * : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(2.0f, 4.0f);
		printResult(v3 == result);
	}

	// p2Vec2 : /
	{
		//Operation
		v3 = v1 / multiplier;
		std::cout << "division / : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(0.5f, 1.0f);
		printResult(v3 == result);
	}

	// p2Vec2 : /=
	{
		//Operation
		v3 = v1;
		v3 /= multiplier;
		std::cout << "division /= : " << v3.x << ", " << v3.y << ";\n";
		//Check
		result = p2Vec2(0.5f, 1.0f);
		printResult(v3 == result);
	}

	std::cout << "\n\n";

	// p2Vec2 : Dot
	{
		std::cout << "dot product : " << p2Vec2::Dot(v1, v2) << ";\n";
		fResult = 11.0f;
		printResult(p2Vec2::Dot(v1, v2) == fResult);
	}
	
	// p2Vec2 : Lerp
	{
		float lerp = 0.3;
		p2Vec2 lerpResult = p2Vec2::Lerp(v1, v2, lerp);
		std::cout << "Lerp of " << lerp << " : " << lerpResult.x << "; " << lerpResult.y << ";\n";
		result = p2Vec2(1.6f, 2.6f);
		printResult(p2Vec2::Lerp(v1, v2, lerp) == result);
	}

	// p2Vec2 : Proj
	{
		v3 = p2Vec2::Proj(v1, v2);
		std::cout << "Proj : " << v3.x << " ; " << v3.y << ";\n";

		result = p2Vec2(6.6f, 8.8f);
		std::cout << "Should be : " << result.x << "; " << result.y << ".\n";
	}

	// p2Vec2 : Refl
	{
		v3 = p2Vec2::Refl(v1, v2);
		std::cout << "Refl : " << v3.x << " ; " << v3.y << ";\n";

		result = p2Vec2(-1.64f, -1.52f);
		std::cout << "Should be : " << result.x << "; " << result.y << ".\n";
	}
	
	// p2Vec2 : AngleBetween
	{
		float angle = p2Vec2::AngleBetween(v1, v2);
		std::cout << "AngleBetween : " << angle << "\n";
		std::cout << "Should be around : 0.179853 \n\n";
	}
	// p2Vec2 : Magnitude
	{
		std::cout << "magnitude : " << v1.GetMagnitude() << ";\n";
		std::cout << "Should be around : 2.2360\n\n";
	}

	// p2Vec2 : Normalize
	{
		v3 = v1.Normalized();
		std::cout << "Normalized : " << v3.x << ", " << v3.y << ";\n";
		std::cout << "Should be around :  0.447214, 0.894427\n\n";
	}
	
	std::cout << "\n\n";

	p2Vec3 v4 = v1.to3();
	p2Vec3 v5 = v2.to3();
	// p2Vec2 : to3
	{
		std::cout << "to3 : \n";
		p2Vec3 threeResult = p2Vec3(1.0f, 2.0f, 0.0f);
		printResult(threeResult == v4);
	}

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "--------------- TEST DES VECTEURS 3 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";

	p2Vec3 v3_1 = p2Vec3(1.0f, 2.0f, 3.0f);
	p2Vec3 v3_2 = p2Vec3(4.0f, 5.0f, 6.0f);
	p2Vec3 v3_3, v3_result;

	// p2Vec3 : +
	{
		v3_3 = v3_1 + v3_2;
		std::cout << "addition + : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(5.0f, 7.0f, 9.0f);
		printResult(v3_3 == v3_result);
	}

	// p2Vec3 : +=
	{
		v3_3 = v3_1;
		v3_3 += v3_2;
		std::cout << "addition += : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(5.0f, 7.0f, 9.0f);
		printResult(v3_3 == v3_result);
	}

	// p2Vec3 : -
	{
		v3_3 = v3_1 - v3_2;
		std::cout << "soustraction - : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(-3.0f, -3.0f, -3.0f);
		printResult(v3_3 == v3_result);
	}

	// p2Vec3 : -=
	{
		v3_3 = v3_1;
		v3_3 -= v3_2;
		std::cout << "soustraction -= : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(-3.0f, -3.0f, -3.0f);
		printResult(v3_3 == v3_result);
	}

	std::cout << "\n\n";

	// p2Vec3 : *
	{
		v3_3 = v3_1 * multiplier;
		std::cout << "multiplier * : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(2.0f, 4.0f, 6.0f);
		printResult(v3_3 == v3_result);

	}

	// p2Vec3 : *=
	{
		v3_3 = v3_1;
		v3_3 *= multiplier;
		std::cout << "multiplier *= : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(2.0f, 4.0f, 6.0f);
		printResult(v3_3 == v3_result);

	}

	// p2Vec3 : /
	{
		v3_3 = v3_1 / multiplier;
		std::cout << "division / : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(0.5f, 1.0f, 1.5f);
		printResult(v3_3 == v3_result);
	}

	// p2Vec3 : /=
	{
		v3_3 = v3_1;
		v3_3 /= multiplier;
		std::cout << "division /= : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
		v3_result = p2Vec3(0.5f, 1.0f, 1.5f);
		printResult(v3_3 == v3_result);
	}
	
	std::cout << "\n\n";

	// p2Vec3 : Dot
	{
		std::cout << "dot product : " << p2Vec3::Dot(v3_1, v3_2) << ";\n";
		float result = 32.0f;
		printResult(result == p2Vec3::Dot(v3_1, v3_2));
	}

	// p2Vec3 : Cross
	{
		p2Vec3 crossResult = p2Vec3::Cross(v3_1, v3_2); 
		std::cout << "Cross product : " << crossResult.x << "; " << crossResult.y << "; " << crossResult.z << ";\n";
		p2Vec3 result = p2Vec3(-3.0f, -6.0f, -3.0f);
		printResult(result == crossResult);
	}
	// p2Vec3 : Lerp
	{
		float lerp = 0.3f;
		p2Vec3 lerpResult = p2Vec3::Lerp(v3_1, v3_2, lerp);
		std::cout << "Lerp product : " << lerpResult.x << "; " << lerpResult.y << "; " << lerpResult.z << ";\n";
		std::cout << "Should be : 1.9; 2.9; 3.9\n\n";
		
		//p2Vec3 result = p2Vec3(1.9f, 2.9f, 3.9f);
		//printResult(result == lerpResult);
	}
	// p2Vec3 : Proj
	{
		p2Vec3 projResult = p2Vec3::Proj(v3_1, v3_2);
		std::cout << "Cross product : " << projResult.x << "; " << projResult.y << "; " << projResult.z << ";\n";
		std::cout << "Should be : 14.586953786; 18.233692233; 21.88043068 \n\n";
	}
	// p2Vec3 : Refl
	{
		p2Vec3 reflResult = p2Vec3::Refl(v3_1, v3_2);
		std::cout << "Refl : " << reflResult.x << " ; " << reflResult.y << "; " << reflResult.z << ";\n";
		std::cout << "Should be : -2.32468 ; -2.15584; -1.98701.\n\n";
	}
	// p2Vec3 : AngleBetween
	{
		float angle = p2Vec3::AngleBetween(v3_1, v3_2);
		std::cout << "AngleBetween : " << angle << "\n";
		std::cout << "Should be around : 0.225726\n\n";
	}

	// p2Vec3 : Magnitude
	{
		std::cout << "magnitude : " << v3_1.GetMagnitude() << ";\n";
		float result = sqrt(14.0f);
		printResult(result == v3_1.GetMagnitude());
	}
	
	// p2Vec3 : Normalized
	{
		v3_3 = v3_1.Normalized();
		std::cout << "Normalized : " << v3_3.x << "; " << v3_3.y << "; " << v3_3.z << ";\n";
		std::cout << "Should be : 0.2672612; 0.53452248; 0.8017837";
	}

	std::cout << "\n\n";

	std::cout << "end!\n";

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
