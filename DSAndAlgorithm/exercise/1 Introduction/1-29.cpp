template <typename T> struct Hailstone
{
    virtual void operator() (T& e)
    {
        int step = 0;
        while (e != 1)
        {
            if (e & 1 == 0)
            {
                e /= 2;
            }
            else
            {
                e = 3*e + 1;
            }
            step++;
        }
        e = step;
    }
};