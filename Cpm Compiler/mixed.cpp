#include "mixed.h"

mixed::mixed(long long data)
{
	this->data = new int_mixed(data);
}

mixed::mixed(double data)
{
	this->data = new float_mixed(data);
}

mixed::mixed(const std::string& data)
{
	try {
		this->data = new int_mixed(std::stoll(data));
	}
	catch(std::exception) {
		try {
			this->data = new float_mixed(std::stod(data));
		}
		catch (std::exception) {}
	}
	this->data = new string_mixed(data);
}

mixed mixed::copy() const
{
	return mixed(data->copy());
}

mixed mixed::operator+() const
{
	return mixed(data->operator+()->copy());
}

mixed mixed::operator+(const mixed& right_mixed) const
{
	return mixed(*(data->operator+()) + right_mixed.data->operator+());
}

mixed mixed::operator-() const
{
	return mixed(data->operator-()->copy());
}

mixed mixed::operator-(const mixed& right_mixed) const
{
	return mixed(*(data->operator+()) - right_mixed.data->operator+());
}

void mixed::operator=(const mixed& right_mixed)
{
	delete(data);
	data = right_mixed.data->copy();
}

std::ostream& mixed::operator<<(std::ostream& out) const
{
	return this->data->operator<<(out);
}

void mixed::operator>>(std::istream& in)
{
	delete(data);
	std::string temp_string;
	in >> temp_string;
	try {
		this->data = new int_mixed(std::stoll(temp_string));
	}
	catch (std::exception) {
		try {
			this->data = new float_mixed(std::stod(temp_string));
		}
		catch (std::exception) {

		}
	}
	this->data = new string_mixed(temp_string);
}

mixed::~mixed(){
	delete(data);
}

int_mixed* int_mixed::operator+() const
{
	return new int_mixed(this->get_data());
}

virtual_mixed* int_mixed::operator+(const virtual_mixed* right_mixed) const
{
	return *this + right_mixed->operator+();
}

virtual_mixed* int_mixed::operator+(const int_mixed& right_mixed) const
{
	return new int_mixed(this->get_data() + right_mixed.get_data());
}

virtual_mixed* int_mixed::operator+(const float_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() + right_mixed.get_data());
}

virtual_mixed* int_mixed::operator+(const string_mixed& right_mixed) const
{
	return new string_mixed(std::to_string(this->get_data()) + right_mixed.get_data());
}

int_mixed* int_mixed::operator-() const
{
	return new int_mixed(-this->get_data());
}

virtual_mixed* int_mixed::operator-(const virtual_mixed* right_mixed) const
{
	return *(this) + right_mixed->operator-();
}

virtual_mixed* int_mixed::operator-(const int_mixed& right_mixed) const
{
	return new int_mixed(this->get_data() - right_mixed.get_data());
}

virtual_mixed* int_mixed::operator-(const float_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() - right_mixed.get_data());
}

virtual_mixed* int_mixed::operator-(const string_mixed& right_mixed) const
{
	try {
		return new int_mixed(this->get_data() - std::stoll(right_mixed.get_data()));
	}
	catch (std::exception) {
		try {
			return new int_mixed(this->get_data() - std::stod(right_mixed.get_data()));
		}
		catch(std::exception) {
		}
	}
	return new int_mixed(this->get_data());
}

std::ostream& int_mixed::operator<<(std::ostream& out) const
{
	out << this->get_data();
	return out;
}

long long int_mixed::get_data() const
{
	return data;
}

virtual_mixed* int_mixed::copy() const
{
	return new int_mixed(this->get_data());
}


float_mixed* float_mixed::operator+() const
{
	return new float_mixed(this->get_data());
}

virtual_mixed* float_mixed::operator+(const virtual_mixed* right_mixed) const
{
	return *(this) + right_mixed->operator+();
}

virtual_mixed* float_mixed::operator+(const int_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() + right_mixed.get_data());
}

virtual_mixed* float_mixed::operator+(const float_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() + right_mixed.get_data());
}

virtual_mixed* float_mixed::operator+(const string_mixed& right_mixed) const
{
	return new string_mixed(std::to_string(this->get_data()) + right_mixed.get_data());
}

float_mixed* float_mixed::operator-() const
{
	return new float_mixed(-this->get_data());
}

virtual_mixed* float_mixed::operator-(const virtual_mixed* right_mixed) const
{
	return *(this) + right_mixed->operator-();
}

virtual_mixed* float_mixed::operator-(const int_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() - right_mixed.get_data());
}

virtual_mixed* float_mixed::operator-(const float_mixed& right_mixed) const
{
	return new float_mixed(this->get_data() - right_mixed.get_data());
}

virtual_mixed* float_mixed::operator-(const string_mixed& right_mixed) const
{
	try {
		return new float_mixed(this->get_data() - std::stoll(right_mixed.get_data()));
	}
	catch (std::exception) {
		try {
			return new float_mixed(this->get_data() - std::stod(right_mixed.get_data()));
		}
		catch (std::exception) {
		}
	}
	return new int_mixed(this->get_data());
}

std::ostream& float_mixed::operator<<(std::ostream& out) const
{
	out << this->get_data();
	return out;
}

double float_mixed::get_data() const
{
	return data;
}

virtual_mixed* float_mixed::copy() const
{
	return new float_mixed(this->get_data());
}

string_mixed* string_mixed::operator+() const
{
	return new string_mixed(this->get_data());
}

virtual_mixed* string_mixed::operator+(const virtual_mixed* right_mixed) const
{
	return *(this) + right_mixed->operator+();
}

virtual_mixed* string_mixed::operator+(const int_mixed& right_mixed) const
{
	return new string_mixed(this->get_data() + std::to_string(right_mixed.get_data()));
}

virtual_mixed* string_mixed::operator+(const float_mixed& right_mixed) const
{
	return new string_mixed(this->get_data() + std::to_string(right_mixed.get_data()));
}

virtual_mixed* string_mixed::operator+(const string_mixed& right_mixed) const
{
	return new string_mixed(this->get_data() + right_mixed.get_data());
}

float_mixed* string_mixed::operator-() const
{
	try {
		return new float_mixed(-std::stod(this->get_data()));
	}
	catch (std::exception) {
	}
	return new float_mixed(0.0);
}

virtual_mixed* string_mixed::operator-(const virtual_mixed* right_mixed) const
{
	return *(this) + right_mixed->operator-();
}

virtual_mixed* string_mixed::operator-(const int_mixed& right_mixed) const
{
	try {
		return new int_mixed(std::stoll(this->get_data()) - right_mixed.get_data());
	}
	catch (std::exception) {
		try {
			return new float_mixed(std::stod(this->get_data()) - right_mixed.get_data());
		}
		catch (std::exception) {
		}
	}
	return new int_mixed(-right_mixed.get_data());
}

virtual_mixed* string_mixed::operator-(const float_mixed& right_mixed) const
{
	try {
		return new float_mixed(std::stoll(this->get_data()) - right_mixed.get_data());
	}
	catch (std::exception) {
		try {
			return new float_mixed(std::stod(this->get_data()) - right_mixed.get_data());
		}
		catch (std::exception) {
		}
	}
	return new float_mixed(-right_mixed.get_data());
}

virtual_mixed* string_mixed::operator-(const string_mixed& right_mixed) const
{
	try {
		return new int_mixed(std::stoll(this->get_data()) - std::stoll(right_mixed.get_data()));
	}
	catch (std::exception) {
		try {
			return new float_mixed(std::stoll(this->get_data()) - std::stod(right_mixed.get_data()));
		}
		catch (std::exception) {
			try {
				return new float_mixed(std::stod(this->get_data()) - std::stoll (right_mixed.get_data()));
			}
			catch (std::exception) {
				try {
					return new float_mixed(std::stod(this->get_data()) - std::stod(right_mixed.get_data()));
				}
				catch (std::exception) {
				}
			}
		}
	}
	return new int_mixed(0);
}

std::ostream& string_mixed::operator<<(std::ostream& out) const
{
	out << this->get_data();
	return out;
}


std::string string_mixed::get_data() const
{
	return data;
}

virtual_mixed* string_mixed::copy() const
{
	return new string_mixed(this->get_data());
}

std::ostream& operator<<(std::ostream& out, const mixed& mix)
{
	mix.operator<<(out);
	return out;
}

std::istream& operator>>(std::istream& in, mixed& mix)
{
	mix.operator>>(in);
	return in;
}
