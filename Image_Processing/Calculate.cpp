#include"stdafx.h"
#include "Calculate.h"

ComplexNum FSAdd(ComplexNum a, ComplexNum b)
{
	a.re = a.re + b.re;
	a.im = a.im + b.im;
	return a;
}
ComplexNum FSSub(ComplexNum a, ComplexNum b)
{
	a.re = a.re - b.re;
	a.im = a.im - b.im;
	return a;
}
ComplexNum FSMul(ComplexNum a, ComplexNum b)
{
	ComplexNum c;
	c.re = a.re*b.re - a.im*b.im;
	c.im = a.im*b.re + a.re*b.im;
	return c;
}