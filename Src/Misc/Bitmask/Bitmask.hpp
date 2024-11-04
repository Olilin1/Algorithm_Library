/*
AUTHOR: Oliver Lindgren
*/

#ifndef BITMASK_HPP
#define BITMASK_HPP

class Bitmask{
    unsigned long long int mask;


    public:
    Bitmask(unsigned long long int x = 0){
        mask = x;
    }

    void set_bit(int x){
        mask |= (1 << x);
    }

    void clear_bit(int x){
        mask &= ~(1 << x);
    }

    void flip_bit(int x){
        mask ^= (1<<x);
    }

    bool is_set(int x){
        return mask & (1 << x);
    }

    unsigned long long int get_mask(){
        return mask;
    }
};

#endif