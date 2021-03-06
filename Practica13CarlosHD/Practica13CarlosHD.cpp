// Practica13CarlosHD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include <iostream>

using namespace std;

int main()
{
	String test("Test");
	String test_copy = test;
	String test2("Test Two");
	String test_add = test + test2;
	String test_add_c = test + 'C';

	cout << "test: " << test.ToCString() << endl;
	cout << "test_copy: " << test_copy.ToCString() << endl;
	cout << "test_copy == test: " << (test_copy == test) << endl;
	cout << "test_copy != test: " << (test_copy != test) << endl;
	cout << "test2 < test: " << (test2 < test) << endl;
	cout << "test2 > test: " << (test2 > test) << endl;
	cout << "test_add: " << test_add.ToCString() << endl;
	cout << "test_add_c: " << test_add_c.ToCString() << endl;

	String test_copy2 = test_copy;
	test_copy += test;
	test_copy2 += 'x';
	cout << "test_copy += test: " << test_copy.ToCString() << endl;
	cout << "test_copy += x: " << test_copy2.ToCString() << endl;
	cout << "test[2]: " << test[2] << endl;
	cout << "test.Length(): " << test.Length() << endl;

	String from_int = String::FromInt(235);
	cout << "FromInt(235): " << from_int.ToCString() << endl;
	cout << "ToInt: " << from_int.ToInt() << endl;
	String hex_from_int = String::HexFromInt(235);
	cout << "HexFromInt(235): " << hex_from_int.ToCString() << endl;
	String from_float = String::FromFloat(235.987f);
	cout << "FromFloat(235.987f): " << from_float.ToCString() << endl;
	cout << "ToFloat: " << from_float.ToFloat() << endl;


	cout << "test Left(2): " << test.Left(2).ToCString() << endl;
	cout << "test Left(3): " << test.Left(3).ToCString() << endl;
	cout << "test Right(2): " << test.Right(2).ToCString() << endl;
	cout << "test Right(3): " << test.Right(3).ToCString() << endl;
	cout << "test Mid(1, 2): " << test.Mid(1, 2).ToCString() << endl;
	cout << "test Mid(0, 2): " << test.Mid(0, 2).ToCString() << endl;

	String find("es");
	cout << "replace test_add 'es' -> 'RO': " << test_add.Replace(find, String("RO")).ToCString() << endl;
	cout << "replace test_add 'es' -> '2345': " << test_add.Replace(find, String("2345")).ToCString() << endl;
	
	cout << "find test_add 'es' ofs 0: " << test_add.Find(find, 0) << endl;
	cout << "find test_add 'es' ofs 2: " << test_add.Find(find, 2) << endl;
	cout << "find test_add 'es' ofs 9: " << test_add.Find(find, 9) << endl;

	cout << "test ToUpper: " << test.ToUpper().ToCString() << endl;
	cout << "test ToLower: " << test.ToLower().ToCString() << endl;

	String spaces("   |Test|          ");
	cout << "spaces: *" << spaces.ToCString() << "*" << endl;
	cout << "spaces LTrim: *" << spaces.LTrim().ToCString() << "*" << endl;
	cout << "spaces RTrim: *" << spaces.RTrim().ToCString() << "*" << endl;
	cout << "spaces Trim: *" << spaces.Trim().ToCString() << "*" << endl;

	cout << "test LSet(8, 'x'): " << test.LSet(8, 'x').ToCString() << endl;
	cout << "test RSet(8, 'x'): " << test.RSet(8, 'x').ToCString() << endl;


	String file_path("C:\\Utad\\C++\\Projects\\Code.cpp");
	cout << "file_path: " << file_path.ToCString() << endl;
	cout << "file_path StripExt: " << file_path.StripExt().ToCString() << endl;
	cout << "file_path StripDir: " << file_path.StripDir().ToCString() << endl;
	cout << "file_path ExtractExt: " << file_path.ExtractExt().ToCString() << endl;
	cout << "file_path ExtractDir: " << file_path.ExtractDir().ToCString() << endl;

	String file_content = String::Read("test.txt");
	cout << "file_content: " << file_content.ToCString() << endl;

	cout << endl << endl;

	test.Write("test_write.txt", false);
	file_content = String::Read("test_write.txt");
	cout << "file_content from test: " << file_content.ToCString() << endl;
	test2.Write("test_write.txt", false);
	file_content = String::Read("test_write.txt");
	cout << "file_content from test2 overwrite: " << file_content.ToCString() << endl;
	test.Write("test_write.txt");
	file_content = String::Read("test_write.txt");
	cout << "file_content from test2 append test: " << file_content.ToCString() << endl;

	getchar();

    return 0;
}

