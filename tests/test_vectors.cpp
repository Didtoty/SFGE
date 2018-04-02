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
#include <iostream>

#include <engine/engine.h>
#include <engine/log.h>


int main()
{

	p2Vec2 v1 = p2Vec2(1.0f, 2.0f);
	p2Vec2 v2 = p2Vec2(3.0, 4.0f);
	p2Vec2 v3;

	float multiplier = 2.0f;

	std::cout << "--------------------------------------------------------\n";
	std::cout << "--------------- TEST DES VECTEURS 2 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";

	v1 += v2;
	std::cout << "addition += : " << v1.x << ", " << v1.y << ";\n";
	v1 -= v2;
	std::cout << "backtoNormal -= : " << v1.x << ", " << v1.y << ";\n";

	std::cout << "\n\n";

	v3 = v1 + v2;
	std::cout << "addition + : " << v3.x << ", " << v3.y << ";\n";
	v3 = v1 - v2;
	std::cout << "soustraction - : " << v3.x << ", " << v3.y << ";\n";

	std::cout << "\n\n";

	v3 = v1 * multiplier;
	std::cout << "multiplier * : " << v3.x << ", " << v3.y << ";\n";
	v3 = v1 / multiplier;
	std::cout << "division / : " << v3.x << ", " << v3.y << ";\n";

	std::cout << "\n\n";

	std::cout << "dot product : " << p2Vec2::Dot(v1, v2) << ";\n";
	std::cout << "magnitude : " << v1.GetMagnitude() << ";\n";
	v3 = v1.Normalized();
	std::cout << "Normalized : " << v3.x << ", " << v3.y << ";\n";

	std::cout << "\n\n";

	p2Vec3 v4 = v1.to3();
	p2Vec3 v5 = v2.to3();

	std::cout << "Dot v3 : " << p2Vec3::Dot(v4, v5) << ";\n";

	p2Vec3 v6 = p2Vec3::Cross(v4, v5);
	std::cout << "Cross v3 : " << v6.x << ", " << v6.y << ", " << v6.z << ";\n";

	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "--------------- TEST DES VECTEURS 3 --------------------\n";
	std::cout << "--------------------------------------------------------\n\n";

	p2Vec3 v3_1 = p2Vec3(1.0f, 2.0f, 3.0f);
	p2Vec3 v3_2 = p2Vec3(4.0f, 5.0f, 6.0f);
	p2Vec3 v3_3;
	v3_1 += v3_2;
	std::cout << "addition += : " << v3_1.x << ", " << v3_1.y << ", " << v3_1.z << ";\n";
	v3_1 -= v3_2;
	std::cout << "backtoNormal -= : " << v3_1.x << ", " << v3_1.y << ", " << v3_1.z << ";\n";

	std::cout << "\n\n";

	v3_3 = v3_1 + v3_2;
	std::cout << "addition + : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
	v3_3 = v3_1 - v3_2;
	std::cout << "soustraction - : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";

	std::cout << "\n\n";

	v3_3 = v3_1 * multiplier;
	std::cout << "multiplier * : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";
	v3_3 = v3_1 / multiplier;
	std::cout << "division / : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";

	std::cout << "\n\n";

	std::cout << "dot product : " << p2Vec3::Dot(v3_1, v3_2) << ";\n";
	std::cout << "magnitude : " << v3_1.GetMagnitude() << ";\n";
	v3_3 = v3_1.Normalized();
	std::cout << "Normalized : " << v3_3.x << ", " << v3_3.y << ", " << v3_3.z << ";\n";

	std::cout << "\n\n";




	std::cout << "end!\n";

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
