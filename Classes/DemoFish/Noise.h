#ifndef __NOISE_H__
#define __NOISE_H__
#include "cocos2d.h"

NS_CC_BEGIN 

//‘Î“Ù¿‡
class Noise
{
public:
	Noise(){}
	virtual ~Noise(){}
	// between -1 and 1
	virtual double generateNoise1D(double x) = 0;
	// between -1 and 1
	virtual double generateNoise2D(double x, double y) = 0;
};

//∞ÿ¡÷‘Î“Ù¿‡
class PerlinNoise : public Noise
{
public:
	PerlinNoise(double mimValue = 0.0, double maxValue = 1.0, double frequency = 1.0, int seed = 0);
	virtual ~PerlinNoise(){}
	// between -1 and 1, frequency is 1
	virtual double generateNoise1D(double x);
	// between -1 and 1, frequency is 1
	virtual double generateNoise2D(double x, double y);

protected:
	double  interpolate(double x, double y, double s);
	double	m_Frequency;
	int		m_Seed;
	double	m_FactorScale;
	double	m_FactorAdd;
};
NS_CC_END
#endif