/*
AUTHOR: Oliver Lindgren
*/

#include "solver.hpp"
//avoid silly precision errors
bool is_double_zero(double x){
    if(x < 0) x = -x;
    return x < 0.000000001;
}

std::vector<double> equation_solver(const std::vector<std::vector<double>>& a, const std::vector<double>& b){
    std::vector<std::vector<double>> m = a;
    std::vector<double> ans;

    for(int row = 0; row < a.size(); row++){
        m[row].push_back(b[row]);
    }

    int rowStart = 0;

    //Triangulering
    for(int col = 0; col < m.size(); col++){
        int index = col;

        
        for(int row = rowStart; row < m.size(); row++){
            if(std::abs(m[row][col]) > std::abs(m[index][col])) index = row;
        }

        if(is_double_zero(m[index][col])){
            continue;
        }

        
        m[rowStart].swap(m[index]);

        for(int col2 = m[0].size()-1; col2 >= col; col2--){
            m[rowStart][col2] /= m[rowStart][col];
        }

        for(int row = rowStart+1; row < m.size(); row++){
            if(is_double_zero(m[rowStart][col])) continue;
            double mult = m[row][col]/m[rowStart][col];

            for(int col2 = col; col2 < m[row].size(); col2++){
                m[row][col2] -= m[rowStart][col2] * mult;
            }
        }

        rowStart++;
    }


    //Bakåtsubstitution
    for(int row1 = m.size()-1; row1 > 0; row1--){
        int col=-1;
        for(int column = 0; column < m.size(); column++){
            if(m[row1][column] == 1){ 
                col = column;
                break;
            }
        }
        if(col == -1) continue;

        for(int row2 = row1-1; row2 >= 0; row2--){
            if(is_double_zero(m[row1][col])) continue;
            double mult = m[row2][col]/m[row1][col];

            for(int col = 0; col <= m.size(); col++){
                m[row2][col] -= m[row1][col]*mult;
            }
            
        }
    }

    //Check for inconsistency
    for(int row = 0; row < m.size(); row++){
        bool allZero = true;

        for(int col = 0; col < m.size(); col++){
            if(!is_double_zero(m[row][col])) allZero = false;
        }
        
        if(allZero && !is_double_zero(m[row][m.size()])) return {};
    }
    
    //Construct solution
    rowStart = 0;
    for(int col = 0; col < m.size(); col++){
        if(is_double_zero(m[rowStart][col])){
            ans.push_back(std::nan(""));
            continue;
        }

        bool allZero = true;

        for(int col2 = col+1; col2 < m.size(); col2++){
            if(!is_double_zero(m[rowStart][col2])) allZero = false;
        }

        if(allZero == false) ans.push_back(std::nan(""));
        else ans.push_back(m[rowStart][m.size()]);

        rowStart++;
    }
    assert(ans.size() == b.size());
    return ans;
    
}