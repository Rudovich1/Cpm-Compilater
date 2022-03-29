#pragma once

#include <string>

class virtual_mixed;
class int_mixed;
class float_mixed;
class string_mixed;
class mixed;

class virtual_mixed {

public:
	virtual virtual_mixed* operator+ () const = 0;
	virtual virtual_mixed* operator+ (const virtual_mixed* right_mixed) const = 0;
	virtual virtual_mixed* operator+ (const int_mixed& right_mixed) const = 0;
	virtual virtual_mixed* operator+ (const float_mixed& right_mixed) const = 0;
	virtual virtual_mixed* operator+ (const string_mixed& right_mixed) const = 0;

	virtual virtual_mixed* operator- () const = 0;
	virtual virtual_mixed* operator- (const virtual_mixed* right_mixed) const = 0;
	virtual virtual_mixed* operator- (const int_mixed& right_mixed) const = 0;
	virtual virtual_mixed* operator- (const float_mixed& right_mixed) const = 0;
	virtual virtual_mixed* operator- (const string_mixed& right_mixed) const = 0;

	virtual virtual_mixed* copy() = 0;

};

class int_mixed : public virtual_mixed {
protected:
	long long data;

public:
	int_mixed(long long data) : data(data) {}

	int_mixed* operator+ () const override;
	virtual_mixed* operator+ (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator+ (const int_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const float_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const string_mixed& right_mixed) const override;

	int_mixed* operator- () const override;
	virtual_mixed* operator- (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator- (const int_mixed& right_mixed) const override;
	virtual_mixed* operator- (const float_mixed& right_mixed) const override;
	virtual_mixed* operator- (const string_mixed& right_mixed) const override;

	long long get_data() const;

	virtual_mixed* copy();

};

class float_mixed : public virtual_mixed {
protected:
	double data;

public:
	float_mixed(double data) : data(data) {}

	float_mixed* operator+ () const override;
	virtual_mixed* operator+ (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator+ (const int_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const float_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const string_mixed& right_mixed) const override;

	float_mixed* operator- () const override;
	virtual_mixed* operator- (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator- (const int_mixed& right_mixed) const override;
	virtual_mixed* operator- (const float_mixed& right_mixed) const override;
	virtual_mixed* operator- (const string_mixed& right_mixed) const override;

	double get_data() const;

	virtual_mixed* copy();

};

class string_mixed : public virtual_mixed {
protected:
	std::string data;

public:
	string_mixed(const std::string& data) : data(data) {}

	string_mixed* operator+ () const override;
	virtual_mixed* operator+ (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator+ (const int_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const float_mixed& right_mixed) const override;
	virtual_mixed* operator+ (const string_mixed& right_mixed) const override;

	float_mixed* operator- () const override;
	virtual_mixed* operator- (const virtual_mixed* right_mixed) const override;
	virtual_mixed* operator- (const int_mixed& right_mixed) const override;
	virtual_mixed* operator- (const float_mixed& right_mixed) const override;
	virtual_mixed* operator- (const string_mixed& right_mixed) const override;

	std::string get_data() const;

	virtual_mixed* copy();
};

class mixed {

	virtual_mixed* data;

	~mixed();

public:
	mixed(long long data);
	mixed(double data);
	mixed(const std::string& data);
	mixed(virtual_mixed* data) : data(data) {}

	mixed copy();

	mixed operator+ () const;
	mixed operator+ (const mixed& right_mixed) const;

	mixed operator- () const;
	mixed operator- (const mixed& right_mixed) const;

	void operator= (const mixed& right_mixed);

};