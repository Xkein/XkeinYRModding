#pragma once

#include "resources/parser_core.h"


class BasicParser :
	public Parser<bool>,
	public Parser<char>,
	public Parser<signed char>,
	public Parser<short>,
	public Parser<int>,
	public Parser<long>,
	public Parser<long long>,
	public Parser<unsigned char>,
	public Parser<unsigned short>,
	public Parser<unsigned int>,
	public Parser<unsigned long>,
	public Parser<unsigned long long>,
	public Parser<float>,
	public Parser<double>,
	public Parser<long double>,
	public Parser<std::string>
{
public:
	virtual bool Parse(std::string_view str, bool& buffer) override;
	virtual bool Parse(std::string_view str, char& buffer) override;
    virtual bool Parse(std::string_view str, signed char& buffer) override;
	virtual bool Parse(std::string_view str, short& buffer) override;
	virtual bool Parse(std::string_view str, int& buffer) override;
	virtual bool Parse(std::string_view str, long& buffer) override;
	virtual bool Parse(std::string_view str, long long& buffer) override;
	virtual bool Parse(std::string_view str, unsigned char& buffer) override;
	virtual bool Parse(std::string_view str, unsigned short& buffer) override;
	virtual bool Parse(std::string_view str, unsigned int& buffer) override;
	virtual bool Parse(std::string_view str, unsigned long& buffer) override;
	virtual bool Parse(std::string_view str, unsigned long long& buffer) override;
	virtual bool Parse(std::string_view str, float& buffer) override;
	virtual bool Parse(std::string_view str, double& buffer) override;
	virtual bool Parse(std::string_view str, long double& buffer) override;
	virtual bool Parse(std::string_view str, std::string& buffer) override;
};
