
/*
Group members, Yan Zhen Lin, Cameron Rivera, Gabriella Voll, Sidney Thelusma, Vladislav Mayzlin
Assignment 5
File: Wallop.h
*/


#ifndef WHALLOP_HPP
#define WHALLOP_HPP
#include <vector>
using namespace std;

/* Names are whatever I wanted them to be just because I could. */
template <typename whap>
class Wallop{
   public:

	Wallop(); // Default constructor
	void putItOn(const whap & gasp); // What is commonly referred to as a push function
	whap popItOff(); // What is commonly referred to as a pop function
	bool geh(); // Tells whether the stack is empty
    	whap peep();
	bool existence(whap & searchItem);

   private:

	int gah; // Number of elements in the stack
	vector <whap> bap; // The stack
};

template <typename whap>
Wallop <whap> :: Wallop():gah(0){
}

template <typename whap>
bool Wallop <whap> :: geh(){
	return (gah == 0);
}

template <typename whap>
whap Wallop <whap> :: peep(){
	return bap.back();
}

template <typename whap>
bool Wallop<whap>::existence(whap & searchItem){
    for(int i = 0; i < gah; i++){
        if(bap[i] == searchItem)
            return true;
        if(i == gah-1 && bap[i] != searchItem)
            return false;
    }
}

template <typename whap>
void Wallop <whap> :: putItOn(const whap & gasp){
	//Change "In stack boolean to true". Perhaps could be done elsewhere
	gah = gah + 1;
	bap.push_back(gasp);
}

template <typename whap>
whap Wallop <whap> :: popItOff()
{
	whap ouch = bap.back();
	// Change "In stack boolean to true". Perhaps could be done elsewhere
	bap.pop_back();
	gah = gah - 1;
	return ouch;
}

#endif

