

# include <bits/stdc++.h>

using namespace std;

// MOHIT KUMAR 
// 18114049

/*
    i will be using map stl structure to implement the polynomials 
    with key value being the power and its value being the coefficient corresponding to that power
*/


 map<int,int> addPoly(map<int,int> p1 , map<int,int> p2 , map<int,int> toreturn){
    
   
    //copy map 2 into this new map
    toreturn.insert(p2.begin(),p2.end());
    //if first map is empty return new map
    if (p1.empty()) {
        printf("the first polynomial is empty returning copy of second");
        return toreturn ;
    }
        
    //if 2nd map is empty return new map after copying 1st mp into it
    else if (p2.empty()){
        toreturn.insert(p1.begin(), p1.end());
        printf("the second polynomial is empty returning copy of first");
        return toreturn;
    }   

    //now we will add both maps
    //since 2nd is already in the mp
    //we will check for elements of map 1
    map<int,int>::iterator it = p1.begin();

    while (it!=p1.end()){

        // //if this power is there in the new map (ie toreturn)
        // if ( toreturn.find( it->first ) != toreturn.end() ){
        //     toreturn[it->first] +=it->second;
        // }
        // //now the power is not there in the new map
        // else {
        //     toreturn.insert(it->first , it->second);
        // }
        toreturn[it->first] +=it->second;
        //if it->first doesnot exist it will be given zero by default

        it++;
    } 
    // it = toreturn.begin();
    // while (it!=toreturn.end()){
    //             printf("%d       %d \n",it->second,it->first);
    //             it++;
    // }

    return toreturn ;

}






 map<int,int> multiplyPoly(map<int,int> p1 , map<int,int> p2 , map<int,int> toreturn){

    
    //if first map is empty return new map
    if (p1.empty()) {
        toreturn.insert(p2.begin(),p2.end());
        printf("the first polynomial is empty returninng copy of second");
        return toreturn;
    }
        
    //if 2nd map is empty return new map after copying 1st mp into it
    else if (p2.empty()){
        toreturn.insert(p1.begin(), p1.end());
        printf("the second polynomial is empty returninng copy of first");
        return toreturn ;
    }   



    // now we will multiply the elements 
    //to return has already the map2 init
    //thus we need to mulyiply just map 1 with it
    map<int,int>::iterator it_p1 = p1.begin();
    map<int,int>::iterator it_p2 = p2.begin();

    while (it_p1 != p1.end()){

        it_p2 = p2.begin();

        while (it_p2 != p2.end()){
            toreturn[ it_p1->first + it_p2->first ] += it_p2->second * it_p1->second ;
            it_p2++;
        }

        it_p1++;

    }
    // it_p1 = toreturn.begin();
    // while (it_p1!=toreturn.end()){
    //             printf("%d       %d \n",it_p1->second,it_p1->first);
    //             it_p1++;
    // }
    return toreturn;

}




int main (){
    printf("Welcome into the programm\n");
    printf("\nEnter the number of terms in first polynomial\n");
    
    int size;
    scanf("%d",&size);

    printf("Please enter coefficients and powers \n");
    int coeff , power;

    map<int,int> p1;
    
    printf("Coefficient  ||     Power\n");

    while (size--){
        scanf("%d",&coeff);
        scanf("%d",&power);
        p1.insert({power,coeff});

    }

    map<int,int>::iterator it = p1.begin();
    while (it!=p1.end()){
                printf("%d       %d \n",it->second,it->first);
                it++;
    }

    printf("\n");
    printf("\n");
    printf("\nEnter the number of terms in second polynomial\n");
    scanf("%d",&size);

    printf("Please enter coefficients and powers \n");
    map<int,int> p2;
    
    printf("Coefficient  ||     Power\n");

    while (size--){
        scanf("%d",&coeff);
        scanf("%d",&power);
        p2.insert({power,coeff});

    }
    it = p2.begin();
    while (it!=p2.end()){
                printf("%d       %d \n",it->second,it->first);
                it++;
    }

    map<int,int> addres,mulres;
    addres = addPoly(p1,p2,addres);
    mulres = multiplyPoly(p1,p2,mulres);


    printf("Enter 1 for addition result ,2 for multiplication result  , 3 to quit\n");
    scanf("%d",&size);

    while (size==1 || size==2){
        if (size==1){
            it = addres.end();
            it--;
            while (it!=addres.begin()){
                printf("%d       %d \n",it->second,it->first);
                it--;
            }
            printf("%d       %d \n",it->second,it->first);
        }else {
            it = mulres.end();
            it--;
            while (it!=mulres.begin()){
                printf("%d       %d \n",it->second,it->first);
                it--;
            }
            printf("%d       %d \n",it->second,it->first);
        }//else 
        printf("Enter 1 for addition result ,2 for multiplication result  , 3 to quit\n");
        scanf("%d",&size);
    }//while loop
    
}