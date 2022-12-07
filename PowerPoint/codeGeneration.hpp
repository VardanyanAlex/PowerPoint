
#ifndef CODEGENERATION_HPP
#define CODEGENERATION_HPP

#include <cassert>
#include <ostream>
#include <map>
#include <stack>
#include <vector>

#include "functionParse.hpp"
#include "getConsoleArguments.hpp"
#include "interpreterRequirments.hpp"
#include "SymbolTable.hpp"
#include "tree.hpp"
#include "typecheckers.hpp"

/*
* brief: returns output program created from parse tree
*/
void CodeGenerator(FunctionsData&, VariablesData&, SCode&, std::ostream& OutputStream, SymbolTable&);

class CRegisterAllocator
{
private:
    std::vector<SToken*> mRegisters;
    size_t mMaxRegisters;    // Max regsiters can't be more than 16
    size_t mFreeRegister;
    size_t mLastBusy;


public:
    CRegisterAllocator(size_t uNumberOfRegisters = 8)
    {
        if(uNumberOfRegisters > 16)
        {
            this->mMaxRegisters = 8;
        }
        else
        {
            this->mMaxRegisters = uNumberOfRegisters;
        }
        mFreeRegister = 0;
        mLastBusy = -1;
        
    }
    

    bool IsFirstRegBusy()
    {
        return (mFreeRegister != 0) ? true : false;
    }
    

    bool HaveFreeRegister()
    {
        return (mRegisters.size() < mMaxRegisters || mFreeRegister < 8 ) ? true : false;
    }

    /*
    * brief: return index of free register or 0 if there is no free register
    */
    size_t GiveRegister()
    {
        
            /*if (stackFrame.size() > 0)
            {
                stackFrame.push_back(*mRegisters[mFreeRegister]);
            }*/
            //mRegisters.push_back(&Token);
            mLastBusy = mFreeRegister++;


            return mLastBusy;
    }

    void PutInRegister(SToken& sToken, int uReg = -1 )
    {
        if (uReg == -1) {
            uReg = mLastBusy;
        }

        if (uReg < mRegisters.size())
        {
            mRegisters[uReg] = &sToken;
        }
        else
        {
            mRegisters.push_back(&sToken);
        }
        
    }

    void SetInitialState()
    {
        mFreeRegister = 0;
        mLastBusy = -1;
    }
    
    void PrepareForPushStack()
    {
        ++mFreeRegister;
        ++mLastBusy;
    }

    size_t GetReleasedReg()
    {
        mLastBusy - 1;
    }

    SToken GetFirstReg()
    {
        return *mRegisters[0];
    }

    SToken GetSecondReg()
    {
        return *mRegisters[1];
    }

    int LastUsedRegister()
    {
        if(mRegisters.empty())
        {
            std::cout << "there is no busy register" << std::endl;
            exit(0);
        }
       

        return mLastBusy;
    }

    bool IsBusy(int uRegister)
    {
        return (mRegisters[uRegister] != nullptr) ? true : false;
    }

    void UnloadRegister()
    {
        mRegisters[mLastBusy] = nullptr;
        if (mLastBusy == 0 && (mRegisters[mRegisters.size() - 1]) != nullptr)
        {
            mLastBusy = mRegisters.size() - 1;
        }
        else 
        {
            mFreeRegister = mLastBusy;
            --mLastBusy;
            //mRegisters.pop_back();
        }

        /*if(!mRegisters.empty())
        {
            mRegisters.pop_back();
            --mFreeRegister;
        }
        else 
        {
            std::cout << "there is no busy register\n";
        }*/
    }

    void SetToNull(size_t i)
    {
        //mRegisters[i] = nullptr;
    }

    SToken operator[](size_t i) 
    { 
        assert(i < mRegisters.size());
        return *mRegisters[i];
    }

};

#endif // CODEGENERATION_HPP
