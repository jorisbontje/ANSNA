#include "Truth.h"

double and(double a, double b)
{        
    return a*b;
}

double or(double a, double b) 
{
    return 1 - ((1 - a) * (1 - b));
}

double w2c(double w)
{
    return w / (w + EVIDENTAL_HORIZON);
}

double c2w(double c)
{
    return EVIDENTAL_HORIZON * c / (1 - c);
}

Truth Truth_Revision(Truth v1, Truth v2)
{
    double f1 = v1.frequency;
    double f2 = v2.frequency;
    double w1 = c2w(v1.confidence);
    double w2 = c2w(v2.confidence);
    double w = w1 + w2;
    double f = (w1 * f1 + w2 * f2) / w;
    double c = w2c(w);
    return (Truth) {.frequency = f, .confidence = c};
}

Truth Truth_Deduction(Truth v1, Truth v2)
{
    double f1 = v1.frequency;
    double f2 = v2.frequency;
    double c1 = v1.confidence;
    double c2 = v2.confidence;
    double f = and(f1, f2);
    double c = and(and(c1, c2), f);
    return (Truth) {.frequency = f, .confidence = c};
}

Truth Truth_Induction(Truth v1, Truth v2)
{
    return Truth_Abduction(v2, v1);
}

Truth Truth_Abduction(Truth v1, Truth v2)
{
    double f1 = v1.frequency;
    double f2 = v2.frequency;
    double c1 = v1.confidence;
    double c2 = v2.confidence;
    double w = and(f2, and(c1, c2));
    double c = w2c(w);
    return (Truth) {.frequency = f1, .confidence = c};;
}

Truth Truth_Intersection(Truth v1, Truth v2)
{
    double f1 = v1.frequency;
    double f2 = v2.frequency;
    double c1 = v1.confidence;
    double c2 = v2.confidence;
    double f = and(f1, f2);
    double c = and(c1, c2);
    return (Truth) {.frequency = f, .confidence = c};
}