#include "stdafx.h"
#include "String.h"
#include <cmath>
#include <vector>

#define m_str static_cast<char *>(m_p)
const int MAX_INT_STR_SIZE = 12;
const int MAX_INT_HEX_STR_SIZE = 8;
const int MAX_FLOAT_STR_SIZE = 100;
const int FLOAT_PRECISION = 10000;
#define FLOAT_PRINTF "%d.%05d"

	// Constructors

	String::String(const char* str) : m_p(nullptr), m_length(0)
	{
		if (str)  {
			CopyContent(str, strlen(str));
		}
	}

	String::String(const String& str) : String(str.ToCString())
	{
	}


	// Destructor

	String::~String()
	{
		if (m_p)
		{
			delete []m_p;
		}
	}


	// Public

	bool String::operator==(const String& other) const
	{
		return !strcmp(const_cast<const char *>(m_str), other.ToCString());
	}

	bool String::operator!=(const String& other) const
	{
		return !(*this == other);
	}

	bool String::operator<(const String& other) const
	{
		return (m_length < other.Length());
	}

	bool String::operator>(const String& other) const
	{
		return (m_length > other.Length());
	}

	String String::operator+(const String& other) const
	{
		int other_length = other.Length();
		const char * other_str = other.ToCString();
		char * content = new char[m_length + other_length + 1];
		ConcatStringToBuffer(other_str, other_length, content);
		String concatenated(content);
		delete content;
		return concatenated;
	}

	String String::operator+(char c) const
	{
		char * content = new char[m_length + 2];
		ConcatStringToBuffer(&c, 1, content);
		String concatenated(content);
		delete content;
		return concatenated;
	}

	String& String::operator=(const String& other)
	{
		CopyContent(other.ToCString(), other.Length());
		return (*this);
	}

	String& String::operator=(char c)
	{
		CopyContent(&c, 1);
		return (*this);
	}

	String& String::operator+=(const String& other)
	{
		int other_length = other.Length();
		const char * other_str = other.ToCString();
		char * content = new char[m_length + other_length + 1];
		ConcatStringToBuffer(other_str, other_length, content);
		SetContent(content, m_length + other_length);

		return *this;
	}

	String& String::operator+=(char c)
	{
		char * content = new char[m_length + 2];
		ConcatStringToBuffer(&c, 1, content);
		SetContent(content, m_length + 1);

		return *this;
	}

	char& String::operator[](unsigned int pos)
	{
		return m_str[pos];
	}

	const char& String::operator[](unsigned int pos) const
	{
		return m_str[pos];
	}

	int String::Length() const
	{
		return m_length;
	}

	String String::FromInt(int val)
	{
		char buf[MAX_INT_STR_SIZE + 1];
		sprintf_s(buf, MAX_INT_STR_SIZE + 1, "%d", val);
		buf[MAX_INT_STR_SIZE] = '\0';
		return String(buf);
	}

	String String::HexFromInt(int val)
	{
		char buf[MAX_INT_HEX_STR_SIZE + 1];
		sprintf_s(buf, MAX_INT_HEX_STR_SIZE + 1, "%08X", val);
		buf[MAX_INT_HEX_STR_SIZE] = '\0';
		return String(buf);
	}

	String String::FromFloat(float val)
	{
		char buf[100];
		int int_val = static_cast<int>(val);
		int frac_val = static_cast<int>(trunc((val - int_val) * FLOAT_PRECISION));

		sprintf_s(buf, 100, FLOAT_PRINTF, int_val, frac_val);
		buf[100] = '\0';
		return String(buf);
	}

	int String::ToInt() const
	{
		if (!m_p)
			return 0;

		return atoi(m_str);
	}

	float String::ToFloat() const
	{
		if (!m_p)
			return 0;

		return strtof(m_str, nullptr);
	}

	const char* String::ToCString() const
	{
		return m_str;
	}

	String String::Left(int n) const
	{
		if (m_length < n)
			return String();

		char * substring = new char[n + 1];
		strncpy_s(substring, n + 1, m_str, n);
		substring[n] = '\0';
		return String(substring);
	}

	String String::Right(int n) const
	{
		if (m_length < n)
			return String();

		char * substring = new char[n + 1];
		strncpy_s(substring, n + 1, m_str + (m_length - n), n);
		substring[n] = '\0';
		return String(substring);
	}

	String String::Mid(int ofs, int n)
	{
		if (m_length <= ofs)
			return String();
		if (m_length < (ofs + n))
			return String();

		char * substring = new char[n + 1];
		strncpy_s(substring, n + 1, m_str + ofs, n);
		substring[n] = '\0';
		return String(substring);
	}

	String String::Replace(const String& find, const String& rep) const
	{
		const char * find_str = find.ToCString();
		int find_length = find.Length();

		std::vector<int> positions;
		int x = 0;
		for(int i = 0; i < m_length; ++i) {
			if (m_str[i] == find_str[x])
				++x;
			else
				x = 0;

			if (x == find_length)
				positions.push_back(i - find_length + 1);
			else if (x > find_length)
				x = 0;
		}

		if (!positions.size())
			return *this;

		const char * rep_str = rep.ToCString();
		int rep_length = rep.Length();

		int characters_to_subtract = (find_length - rep_length) * positions.size();
		char * new_str = new char[m_length - characters_to_subtract + 1];
		auto rep_position = positions.begin();
		x = 0;
		for(int i = 0; i < m_length; ) {
			if (rep_position != positions.end() && *rep_position == i)
			{
				rep_position = positions.erase(rep_position);
				strncpy_s(new_str + x, rep_length + 1, rep_str, rep_length);
				x += rep_length;
				i += find_length;
			} 
			else
			{
				new_str[x] = m_str[i];
				++x;
				++i;
			}
		}
		new_str[m_length - characters_to_subtract] = '\0';

		String replaced(new_str);
		delete new_str;

		return replaced;
	}

	int String::Find(const String& str, int ofs) const
	{
		int str_length = str.Length();
		if (!str_length || (m_length - ofs + 1) < str_length)
			return 0;

		if (strstr(m_str + ofs, str.ToCString()))
			return 1;
		else
			return 0;
	}

	String String::ToUpper() const
	{
		char * upper_str = new char[m_length + 1];
		for(int i = 0; i < m_length; ++i)
			upper_str[i] = static_cast<char>(toupper(m_str[i]));

		upper_str[m_length] = '\0';

		String upper_string(upper_str);
		delete upper_str;

		return upper_string;
	}

	String String::ToLower() const
	{
		char * lower_str = new char[m_length + 1];
		for(int i = 0; i < m_length; ++i)
			lower_str[i] = static_cast<char>(tolower(m_str[i]));

		lower_str[m_length] = '\0';

		String lower_string(lower_str);
		delete lower_str;

		return lower_string;
	}

	String String::LTrim() const
	{
		int ofs = 0;
		for(int i = 0; i < m_length; ++i)
		{
			if (m_str[i] == ' ')
				++ofs;
			else
				break;
		}

		if (0 == ofs)
			return *this;

		return Right(m_length - ofs);
	}

	String String::RTrim() const
	{
		int ofs = m_length;
		for(int i = m_length - 1; i >= 0; --i)
		{
			if (m_str[i] == ' ')
				--ofs;
			else
				break;
		}

		if (m_length == ofs)
			return *this;

		return Left(ofs);
	}

	String String::Trim() const 
	{
		return LTrim().RTrim();
	}

	// Rellena por la izquierda con el caracter "c" hasta completar el tamaño pasado "len":
	// 	String("12345").LSet(10, 'x') --> "xxxxx12345"
	String String::LSet(int len, char c) const
	{
		if (m_length >= len)
			return *this;

		int num = len - m_length;
		char * str = new char[len + 1];
		for(int i = 0; i < num; ++i)
			str[i] = c;

		for(int i = 0; i < m_length; ++i)
			str[i + num] = m_str[i];

		str[len] = '\0';

		String l_padded(str);
		delete str;

		return l_padded;
	}

	String String::RSet(int len, char c) const
	{
		if (m_length >= len)
			return *this;

		char * str = new char[len + 1];
		for(int i = 0; i < m_length; ++i)
			str[i] = m_str[i];

		for(int i = m_length; i < len; ++i)
			str[i] = c;

		str[len] = '\0';

		String r_padded(str);
		delete str;

		return r_padded;
	}

	String String::StripExt() const
	{
		int ofs = m_length - 1;
		for(int i = m_length - 1; i >= 0; --i)
		{
			if (m_str[i] != '.')
				--ofs;
			else 
				break;
		}

		if (0 >= ofs)
			return *this;

		return Left(ofs);
	}

	String String::StripDir() const
	{
		int ofs = m_length;
		for(int i = m_length - 1; i >= 0; --i)
		{
			if (m_str[i] != '/' && m_str[i] != '\\')
				--ofs;
			else 
				break;
		}

		if (m_length == ofs)
			return *this;

		return Right(m_length - ofs);
	}


	String String::ExtractExt() const
	{
		int ofs = m_length - 1;
		for(int i = m_length - 1; i >= 0; --i)
		{
			if (m_str[i] != '.')
				--ofs;
			else 
				break;
		}

		if (0 >= ofs)
			return *this;

		return Right(m_length - ofs);
	}

	String String::ExtractDir() const
	{
		int ofs = m_length;
		for(int i = m_length - 1; i >= 0; --i)
		{
			if (m_str[i] != '/' && m_str[i] != '\\')
				--ofs;
			else 
				break;
		}

		if (m_length == ofs)
			return *this;

		return Left(ofs);
	}

	String String::RealPath() const
	{
		// TODO 
		return *this;
	}

	String String::Read(const String& filename)
	{
		if (!filename.Length())
			return String();

		FILE * file;
		errno_t err = fopen_s(&file, filename.ToCString(), "rb");
		if (err)
			return String();

		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
		char * file_content = new char[size + 1];
		fread_s(file_content, size, 1, size, file);
		fclose(file);

		file_content[size] = '\0';

		String str_file(file_content);
		delete file_content;

		return str_file;
	}

	void String::Write(const String& filename, bool append) const
	{
		if (!filename.Length())
			return;

		FILE * file;
		errno_t err;
		
		if (append)
			err = fopen_s(&file, filename.ToCString(), "ab");
		else
			err = fopen_s(&file, filename.ToCString(), "wb");

		if (err)
			return;

		fwrite(m_str, 1, m_length, file);

		fclose(file);
	}


	// Private

	// Makes a copy of the parameter buffer and sets it to the String internal buffer
	void String::CopyContent(const char * str, int str_size)
	{
		if (m_p) {
			delete m_p;
		}
		if (str) 
		{
			m_length = str_size;
			m_p = new char[m_length + 1];
			strcpy_s(m_str, m_length + 1, str);
			m_str[m_length] = '\0';
		}
	}

	// Replaces the String internal buffer with the new one without making a copy of it
	void String::SetContent(char * str, int str_size)
	{
		if (m_p) {
			delete m_p;
		}
		m_length = str_size;
		m_p = str;
	}

	void String::ConcatStringToBuffer(const char * str, int str_size, char * out) const
	{
		strcpy_s(out, m_length + 1, m_str);
		strcat_s(out, m_length + str_size + 1, str);
		out[m_length + str_size] = '\0';
	}